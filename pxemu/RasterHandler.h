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

/////////////////////////////////////////////////////////////////////////////
class RasterHandler : public Handler
{
    // Construction / Destruction
public:
    RasterHandler();

    // Interface
    void handle() override; // handler

    // Implementation
private:
    UIEventHandler ui;
    uint16_t m_scanLine;
    uint16_t m_offset;
};

#endif // __RASTER_HANDLER_H__
