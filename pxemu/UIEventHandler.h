/////////////////////////////////////////////////////////////////////////////
//
// UIEVENTHANDLER.H : UI event handling
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __UI_EVENT_HANDLER_H__
#define __UI_EVENT_HANDLER_H__

#include "Handler.h"

/////////////////////////////////////////////////////////////////////////////
class UIEventHandler : public Handler 
{
	// Construction / Destruction
public:
	UIEventHandler();
	~UIEventHandler();

	// Interface
	virtual void handle(); // handler

	// Implementation
private:
};

#endif // __UI_EVENT_HANDLER_H__