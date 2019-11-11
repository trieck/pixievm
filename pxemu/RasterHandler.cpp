/////////////////////////////////////////////////////////////////////////////
//
// RASTERHANDLER.CPP : raster handling
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "StdAfx.h"
#include "RasterHandler.h"
#include "memory.h"
#include "PixieVM.h"
#include "Canvas.h"

constexpr auto IO_REG_BKGND_COLOR = (IO_REGISTER_BASE + 0);
constexpr auto IO_REG_BORDER_COLOR = (IO_REGISTER_BASE + 1);

/////////////////////////////////////////////////////////////////////////////
RasterHandler::RasterHandler() : m_scanLine(0), m_offset(0)
{
}

/////////////////////////////////////////////////////////////////////////////
void RasterHandler::handle()
{
    auto& memory = Memory::instance();
    auto& canvas = Canvas::instance();

    const auto bkgndColor = memory.fetch(IO_REG_BKGND_COLOR);
    const auto borderColor = memory.fetch(IO_REG_BORDER_COLOR);

    // handle 4-pixels at a time
    for (auto i = 0; i < 4; ++i) {
        // are we on a border?
        if (m_scanLine < Canvas::CY_BORDER ||
            m_scanLine >= Canvas::CY_SIZE - Canvas::CY_BORDER ||
            m_offset < Canvas::CX_BORDER ||
            m_offset >= Canvas::CX_SIZE - Canvas::CY_BORDER) {
            canvas.SetPixel(m_offset, m_scanLine, borderColor);
        } else {
            const uint16_t scanLine = m_scanLine - Canvas::CY_BORDER;
            const uint16_t offset = m_offset - Canvas::CX_BORDER;
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
                canvas.SetPixel(m_offset, m_scanLine, color);
            } else {
                canvas.SetPixel(m_offset, m_scanLine, bkgndColor);
            }
        }

        m_offset = (m_offset + 1) % Canvas::CX_SIZE;
    }

    if (m_offset == 0 && (m_scanLine > 0
        && ((m_scanLine % 8) == 0) || m_scanLine == Canvas::CY_SIZE - 1)) {
        canvas.Invalidate({ 0, m_scanLine - 8, Canvas::CX_SIZE, m_scanLine });
    }

    if (m_offset == 0) {
        // beginning of scan line
        ui.handle(); // dispatch ui events
        m_scanLine = (m_scanLine + 1) % Canvas::CY_SIZE;
    }
}
