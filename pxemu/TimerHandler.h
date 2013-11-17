/////////////////////////////////////////////////////////////////////////////
//
// TIMERHANDLER.H : timer handling
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __TIMER_HANDLER_H__
#define __TIMER_HANDLER_H__

#include "Handler.h"
#include "Memory.h"
#include "HiresTimer.h"

/////////////////////////////////////////////////////////////////////////////
class TimerHandler : public Handler
{
	// Construction / Destruction
public:
	TimerHandler();
	~TimerHandler();

	// Interface
	virtual void handle(); // handler

	// Implementation
private:
	void reset ();
	HiresTimer m_timer;
	Memory* m_memory;
	uint64_t m_LastClock;
};

#endif // __TIMER_HANDLER_H__