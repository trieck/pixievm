/////////////////////////////////////////////////////////////////////////////
//
// TIMERHANDLER.CPP : timer handling
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "TimerHandler.h"
#include "Memory.h"
#include "PixieVM.h"
#include "interrupt.h"

/////////////////////////////////////////////////////////////////////////////
TimerHandler::TimerHandler()
{
	m_memory = Memory::getInstance();
	m_LastClock = m_timer.jiffies();
}

/////////////////////////////////////////////////////////////////////////////
TimerHandler::~TimerHandler()
{
}

/////////////////////////////////////////////////////////////////////////////
void TimerHandler::reset()
{
	m_timer.reset();
}

/////////////////////////////////////////////////////////////////////////////
void TimerHandler::handle()
{
	// generates interrupts every 1/60th of a second
	uint64_t clock = m_timer.jiffies();

	uint64_t diff = clock - m_LastClock;
	if (diff != 0) 
		g_interrupt.setPending(IK_IRQ);

	m_LastClock = clock;
}
