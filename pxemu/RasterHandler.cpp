#include "StdAfx.h"
#include "RasterHandler.h"
#include "PixieVM.h"
#include "Memory.h"

constexpr auto IO_REG_BKGND_COLOR = (IO_REGISTER_BASE + 0);
constexpr auto IO_REG_BORDER_COLOR = (IO_REGISTER_BASE + 1);

////////////////////////////////////////////////////////////////////////////
RasterHandler::RasterHandler(Canvas* canvas)
    : m_pCanvas(canvas)
{
    m_drawBuffer = make_byte_ptr(CANVAS_CX_SIZE * CANVAS_CY_SIZE);
}

////////////////////////////////////////////////////////////////////////////
void RasterHandler::handle()
{
    auto& memory = Memory::instance();

    const auto bkgndColor = memory.fetch(IO_REG_BKGND_COLOR);
    const auto borderColor = memory.fetch(IO_REG_BORDER_COLOR);

    // handle scan line  at a time
    for (auto i = 0; i < CANVAS_CX_SIZE; ++i) {

        // are we on a border?
        if (m_scanLine < CANVAS_CY_BORDER ||
            m_scanLine >= CANVAS_CY_SIZE - CANVAS_CY_BORDER ||
            i < CANVAS_CX_BORDER ||
            i >= CANVAS_CX_SIZE - CANVAS_CY_BORDER) {
            m_drawBuffer[m_scanLine * CANVAS_CX_SIZE + i] = borderColor;
        } else {
            const uint16_t scanLine = m_scanLine - CANVAS_CY_BORDER;
            const uint16_t offset = i - CANVAS_CX_BORDER;
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
                m_drawBuffer[m_scanLine * CANVAS_CX_SIZE + i] = color;
            } else {
                m_drawBuffer[m_scanLine * CANVAS_CX_SIZE + i] = bkgndColor;
            }
        }

    }

    if (m_scanLine == CANVAS_CY_SIZE - 1) {
        m_pCanvas->render({ 0, 0, CANVAS_CX_SIZE, m_scanLine }, m_drawBuffer.get());
    }

    
    m_scanLine = (m_scanLine + 1) % CANVAS_CY_SIZE;

    if (m_scanLine == 0) {
        ui.handle(); // dispatch ui events
        // TODO: we need vsync clock with sleep...
    }
}
