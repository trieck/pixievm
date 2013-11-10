/////////////////////////////////////////////////////////////////////////////
//
// RASTERHANDLER.H : raster handling
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __RASTER_HANDLER_H__
#define __RASTER_HANDLER_H__

#include "Handler.h"
#include "UIEventHandler.h"
#include "Memory.h"
#include "Bitmap.h"

/////////////////////////////////////////////////////////////////////////////
class RasterHandler : public Handler
{
	// Construction / Destruction
public:
	RasterHandler();
	~RasterHandler();

	// Interface
	virtual void handle(); // handler

	// Implementation
private:
	UIEventHandler ui;
	uint16_t m_scanLine;
	uint16_t m_offset;
	Memory* m_memory;
	Bitmap* m_bitmap;
};

#endif // __RASTER_HANDLER_H__