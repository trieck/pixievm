/////////////////////////////////////////////////////////////////////////////
//
// RASTERHANDLER.CPP : raster handling
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#include "StdAfx.h"
#include "RasterHandler.h"
#include "memory.h"
#include "PixieVM.h"

constexpr auto IO_REG_BKGND_COLOR = (IO_REGISTER_BASE + 0);
constexpr auto IO_REG_BORDER_COLOR = (IO_REGISTER_BASE + 1);

/////////////////////////////////////////////////////////////////////////////
RasterHandler::RasterHandler() : m_scanLine(0), m_offset(0)
{
    m_memory = Memory::getInstance();
    m_canvas = Canvas::getInstance();
}

/////////////////////////////////////////////////////////////////////////////
RasterHandler::~RasterHandler()
{
}

/////////////////////////////////////////////////////////////////////////////
void RasterHandler::handle()
{
    const auto bkgndColor = m_memory->fetch(IO_REG_BKGND_COLOR);
    const auto borderColor = m_memory->fetch(IO_REG_BORDER_COLOR);

    // handle 4-pixels at a time
    for (int i = 0; i < 4; ++i){
        // are we on a border?
        if (m_scanLine < Canvas::CY_BORDER ||
            m_scanLine >= Canvas::CY_SIZE - Canvas::CY_BORDER ||
            m_offset < Canvas::CX_BORDER ||
            m_offset >= Canvas::CX_SIZE - Canvas::CY_BORDER){
          m_canvas->SetPixel(m_offset, m_scanLine, borderColor);
        } else{
            const uint16_t scanLine = m_scanLine - Canvas::CY_BORDER;
            const uint16_t offset = m_offset - Canvas::CX_BORDER;
            const uint16_t row = scanLine / 8;
            const uint16_t vid_ptr = VIDEORAM_BASE + (row * 80) + (offset / 8);
            const uint16_t color_ptr = COLORRAM_BASE + (row * 80) + (offset / 8);

            // fetch the character pointer from video ram
            const auto ch_ptr = m_memory->fetch(vid_ptr);
            const uint8_t chrow = scanLine % 8;

            // fetch the character row from character generator rom
            const auto ch = m_memory->fetch(CHARGEN_BASE + (ch_ptr * 8) + chrow);

            // fetch the color from color ram
            const auto color = m_memory->fetch(color_ptr);

            const uint8_t start = 7 - (offset % 8);
            if (ch & 1 << start){
                m_canvas->SetPixel(m_offset, m_scanLine, color);
            } else{
              m_canvas->SetPixel(m_offset, m_scanLine, bkgndColor);
            }
        }

        m_offset = (m_offset + 1) % Canvas::CX_SIZE;
    }

    if (m_offset == 0 && (m_scanLine > 0
        && ((m_scanLine % 8) == 0) || m_scanLine == Canvas::CY_SIZE - 1)){
        CRect rc(0, m_scanLine - 8, Canvas::CX_SIZE, m_scanLine);
        m_canvas->Invalidate(rc);
    }

    if (m_offset == 0){
        // beginning of scan line
        ui.handle(); // dispatch ui events
        m_scanLine = (m_scanLine + 1) % Canvas::CY_SIZE;
    }
}
