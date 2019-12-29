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
    memset(m_drawBuffer.get(), 0, CANVAS_CX_SIZE * CANVAS_CY_SIZE);
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
            update(m_offset, m_scanLine, borderColor);
        } else {
            const uint16_t scanLine = m_scanLine - CANVAS_CY_BORDER;
            const uint16_t offset = m_offset - CANVAS_CX_BORDER;
            const uint16_t row = scanLine / 8;
            const uint16_t vidp = VIDEORAM_BASE + (row * 80) + (offset / 8);
            const uint16_t colorp = COLORRAM_BASE + (row * 80) + (offset / 8);

            // fetch the character pointer from video ram
            const auto chp = memory.fetch(vidp);
            const uint8_t chrow = scanLine % 8;

            // fetch the character row from character generator rom
            const auto ch = memory.fetch(CHARGEN_BASE + (chp * 8) + chrow);

            // fetch the color from color ram
            const auto color = memory.fetch(colorp);

            const uint8_t start = 7 - (offset % 8);

            if (ch & 1 << start) {
                update(m_offset, m_scanLine, color);
            } else {
                update(m_offset, m_scanLine, bkgndColor);
            }
        }

        m_offset = (m_offset + 1) % CANVAS_CX_SIZE;
        if (m_offset == 0) {
            m_scanLine = (m_scanLine + 1) % CANVAS_CY_SIZE;
        }
    }

    if (m_scanLine == 0 && m_offset == 0 && !m_update.IsRectEmpty()) {
        auto* pbits = &m_drawBuffer[m_update.top * CANVAS_CX_SIZE + m_update.left];
        m_pCanvas->render(m_update, pbits);
        m_update.SetRectEmpty();
        m_empty = false;
    }

    if (m_scanLine == 0) {
        ui.handle(); // dispatch ui events
        // TODO: we need vsync clock with sleep...
    }
}

////////////////////////////////////////////////////////////////////////////
void RasterHandler::update(int x, int y, byte color)
{
    auto& current = m_drawBuffer[y * CANVAS_CX_SIZE + x];
    if (current != color || m_empty) {
        current = color;

        if (m_update.IsRectEmpty()) {
            m_update.left = x;
            m_update.top = y;
        } else {
            m_update.left = min(m_update.left, x);
            m_update.top = min(m_update.top, y);
        }

        m_update.right = min(CANVAS_CX_SIZE, max(m_update.right, x + 1));
        m_update.bottom = min(CANVAS_CY_SIZE, max(m_update.bottom, y + 1));
    }
}
