/////////////////////////////////////////////////////////////////////////////
//
// INTERRUPT.CPP : Implementation of interrupts
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "interrupt.h"

// global interrupt
Interrupt g_interrupt;

/////////////////////////////////////////////////////////////////////////////
void Interrupt::handleTrap()
{
    if (m_trapHandler != nullptr) {
        m_trapHandler->trap(m_trapData);
    }
}

/////////////////////////////////////////////////////////////////////////////
void Interrupt::setTrap(LPTRAPHANDLER handler, void* data)
{
    m_pending |= IK_TRAP;
    m_trapHandler = handler;
    m_trapData = data;
}

/////////////////////////////////////////////////////////////////////////////
void Interrupt::setMonitor(LPHANDLER handler)
{
    m_pending |= IK_MONITOR;
    m_monHandler = handler;
}

/////////////////////////////////////////////////////////////////////////////
void Interrupt::setMonitorBreak(LPTRAPHANDLER handler)
{
    m_pending |= IK_MONBREAK;
    m_trapHandler = handler;
}

/////////////////////////////////////////////////////////////////////////////
void Interrupt::handleMonitor()
{
    if (m_monHandler != nullptr) {
        m_monHandler->handle();
    }
}

/////////////////////////////////////////////////////////////////////////////
LPTRAPHANDLER Interrupt::getTrapHandler() const
{
    return m_trapHandler;
}
