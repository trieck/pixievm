/////////////////////////////////////////////////////////////////////////////
//
// INTERRUPT.H : Implementation of interrupts
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "trap.h"
#include "Handler.h"

/////////////////////////////////////////////////////////////////////////////
// Types of interrupt lines
enum cpu_int
{
    IK_NONE = 0,
    IK_NMI = 1 << 0,
    IK_IRQ = 1 << 1,
    IK_RESET = 1 << 2,
    IK_TRAP = 1 << 3,
    IK_MONITOR = 1 << 4,
    IK_MONBREAK = 1 << 5
};

/////////////////////////////////////////////////////////////////////////////
class Interrupt
{
public:
    Interrupt() = default;
    virtual ~Interrupt() = default;

    int getPending() const
    {
        return m_pending;
    }

    void setPending(int p)
    {
        m_pending |= p;
    }

    void clearPending(int p)
    {
        m_pending &= ~p;
    }

    LPTRAPHANDLER getTrapHandler() const;
    void setTrap(LPTRAPHANDLER handler, void* data = nullptr);
    void handleTrap();

    void setMonitor(LPHANDLER handler);
    void setMonitorBreak(LPTRAPHANDLER handler);
    void handleMonitor();

private:
    // pending interrupt
    int m_pending = 0;

    // trap handler
    LPTRAPHANDLER m_trapHandler = nullptr;

    // monitor handler
    LPHANDLER m_monHandler = nullptr;

    // trap data
    void* m_trapData = nullptr;
};

// global interrupt declaration
extern Interrupt g_interrupt;

/////////////////////////////////////////////////////////////////////////////
#endif // __INTERRUPT_H__
