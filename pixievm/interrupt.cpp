/////////////////////////////////////////////////////////////////////////////
//
// INTERRUPT.CPP : Implementation of interrupts
//
// Copyright (c) 2006, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Trap.h"
#include "Interrupt.h"

/* global interrupt */
interrupt_st g_interrupt;

/////////////////////////////////////////////////////////////////////////////
interrupt_st::interrupt_st()
{
	memset(this, 0, sizeof(interrupt_st));
}


/////////////////////////////////////////////////////////////////////////////
interrupt_st::~interrupt_st()
{
}

/////////////////////////////////////////////////////////////////////////////
void interrupt_st::handleTrap()
{
	if (trap) {
		trap->trap(trap_data);
	}
}

/////////////////////////////////////////////////////////////////////////////
void interrupt_st::setTrap(LPTRAPHANDLER handler, void *data)
{
	pending |= IK_TRAP;
	trap = handler;
	trap_data = data;
}