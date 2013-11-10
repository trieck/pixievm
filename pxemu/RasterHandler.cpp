/////////////////////////////////////////////////////////////////////////////
//
// RASTERHANDLER.CPP : raster handling
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "RasterHandler.h"
#include "Canvas.h"
#include "Memory.h"
#include "PixieVM.h"

extern HWND hwndClient;

#define BORDER_COLOR			120
#define BACKGROUND_COLOR	124

/////////////////////////////////////////////////////////////////////////////
RasterHandler::RasterHandler() : m_scanLine(0), m_offset(0)
{
	m_memory = Memory::getInstance();
	m_bitmap = Bitmap::getInstance();
}

/////////////////////////////////////////////////////////////////////////////
RasterHandler::~RasterHandler()
{
}

/////////////////////////////////////////////////////////////////////////////
void RasterHandler::handle()
{
	// handle 4-pixels at a time
	for (int i = 0; i < 4; ++i) {

		// are we on a border?
		if (m_scanLine < Canvas::CY_BORDER ||
			m_scanLine >= Canvas::CY_SIZE-Canvas::CY_BORDER ||
			m_offset < Canvas::CX_BORDER || 
			m_offset >= Canvas::CX_SIZE-Canvas::CY_BORDER) {
			
			m_bitmap->SetPixel(m_offset, m_scanLine, BORDER_COLOR);
		} else {
			uint16_t scanLine = m_scanLine - Canvas::CY_BORDER;
			uint16_t offset = m_offset - Canvas::CX_BORDER;
			uint16_t row = scanLine / 8;
			uint16_t vid_ptr = VIDEORAM_BASE + (row * 80) + (offset / 8);
			uint16_t color_ptr = COLORRAM_BASE + (row * 80) + (offset / 8);

			// fetch the character pointer from video ram
			uint8_t ch_ptr = m_memory->fetch(vid_ptr);
			uint8_t chrow = scanLine % 8;
		
			// fetch the character row from character generator rom
			uint8_t ch = m_memory->fetch(CHARGEN_BASE + (ch_ptr * 8) + chrow);

			// fetch the color from color ram
			uint8_t color = m_memory->fetch(color_ptr);

			uint8_t start = 7 - (offset % 8);
			if (ch & 1 << start) {
				m_bitmap->SetPixel(m_offset, m_scanLine, color);
			} else {
				m_bitmap->SetPixel(m_offset, m_scanLine, BACKGROUND_COLOR);
			}
		}

		m_offset = (m_offset + 1) % Canvas::CX_SIZE;
	}

	if (m_offset == 0 && (m_scanLine > 0 
		&& ((m_scanLine % 8) == 0) || m_scanLine == Canvas::CY_SIZE-1)) {
		CRect rc(0, m_scanLine - 8, Canvas::CX_SIZE, m_scanLine);
		InvalidateRect(hwndClient, rc, FALSE);
	}

	if (m_offset == 0) { // beginning of scan line
		ui.handle();	// dispatch ui events
		m_scanLine = (m_scanLine + 1) % Canvas::CY_SIZE;
	}	
}
