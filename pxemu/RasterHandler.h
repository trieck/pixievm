/////////////////////////////////////////////////////////////////////////////
//
// RASTERHANDLER.H : raster handling
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __RASTER_HANDLER_H__
#define __RASTER_HANDLER_H__

#include "Handler.h"
#include "UIEventHandler.h"
#include "Memory.h"
#include "Canvas.h"

/////////////////////////////////////////////////////////////////////////////
class RasterHandler : public Handler
{
    // Construction / Destruction
public:
    RasterHandler();
    ~RasterHandler();

    // Interface
    void handle() override; // handler

    // Implementation
private:
    UIEventHandler ui;
    uint16_t m_scanLine;
    uint16_t m_offset;
    Memory* m_memory;
    Canvas* m_canvas;
};

#endif // __RASTER_HANDLER_H__
