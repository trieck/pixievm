/////////////////////////////////////////////////////////////////////////////
//
// UIEVENTHANDLER.H : UI event handling
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __UI_EVENT_HANDLER_H__
#define __UI_EVENT_HANDLER_H__

#include "Handler.h"

/////////////////////////////////////////////////////////////////////////////
class UIEventHandler : public Handler, CMessageLoop
{
public:
    // Interface
    void handle() override; // handler
};

#endif // __UI_EVENT_HANDLER_H__
