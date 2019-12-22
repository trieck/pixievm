#include "StdAfx.h"
#include "RasterHandler.h"
#include "PixieVM.h"

constexpr auto IO_REG_BKGND_COLOR = (IO_REGISTER_BASE + 0);
constexpr auto IO_REG_BORDER_COLOR = (IO_REGISTER_BASE + 1);

////////////////////////////////////////////////////////////////////////////
RasterHandler::RasterHandler(Canvas* canvas) : m_pCanvas(canvas)
{
    m_pBits = canvas->bits();
    m_pitch = canvas->pitch();
}

////////////////////////////////////////////////////////////////////////////
void RasterHandler::handle()
{
    auto& memory = Memory::instance();

    const auto bkgndColor = memory.fetch(IO_REG_BKGND_COLOR);
    const auto borderColor = memory.fetch(IO_REG_BORDER_COLOR);

    // handle 4-pixels at a time
    for (auto i = 0; i < 4; ++i) {
        // are we on a border?
        if (m_scanLine < CANVAS_CY_BORDER ||
            m_scanLine >= CANVAS_CY_SIZE - CANVAS_CY_BORDER ||
            m_offset < CANVAS_CX_BORDER ||
            m_offset >= CANVAS_CX_SIZE - CANVAS_CY_BORDER) {
            m_pBits[m_scanLine * m_pitch + m_offset] = borderColor;
        } else {
            const uint16_t scanLine = m_scanLine - CANVAS_CY_BORDER;
            const uint16_t offset = m_offset - CANVAS_CX_BORDER;
            const uint16_t row = scanLine / 8;
            const uint16_t vid_ptr = VIDEORAM_BASE + (row * 80) + (offset / 8);
            const uint16_t color_ptr = COLORRAM_BASE + (row * 80) + (offset / 8);

            // fetch the character pointer from video ram
            const auto ch_ptr = memory.fetch(vid_ptr);
            const uint8_t chrow = scanLine % 8;

            // fetch the character row from character generator rom
            const auto ch = memory.fetch(CHARGEN_BASE + (ch_ptr * 8) + chrow);

            // fetch the color from color ram
            const auto color = memory.fetch(color_ptr);

            const uint8_t start = 7 - (offset % 8);
            if (ch & 1 << start) {
                m_pBits[m_scanLine * m_pitch + m_offset] = color;
            } else {
                m_pBits[m_scanLine * m_pitch + m_offset] = bkgndColor;
            }
        }

        m_offset = (m_offset + 1) % CANVAS_CX_SIZE;
    }

    if (m_offset == 0 && (m_scanLine > 0
        && ((m_scanLine % 8) == 0) || m_scanLine == CANVAS_CY_SIZE - 1)) {
        m_pCanvas->Refresh({ 0, m_scanLine - 8, CANVAS_CX_SIZE, m_scanLine });
    }

    if (m_offset == 0) {
        // beginning of scan line
        m_scanLine = (m_scanLine + 1) % CANVAS_CY_SIZE;
    }

    if (m_scanLine == 0) {
        ui.handle(); // dispatch ui events
    }
}
