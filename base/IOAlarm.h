/////////////////////////////////////////////////////////////////////////////
//
// IOALARM.H : I/O alarm
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __IO_ALARM_H__
#define __IO_ALARM_H__

#include "Handler.h"
#include "PixieClock.h"

/////////////////////////////////////////////////////////////////////////////
class IOAlarm : public Handler
{
    // Construction / Destruction
public:
    IOAlarm();
    ~IOAlarm();

    // Interface
    void handle() override; // handler

    // Implementation
private:
    PixieClock m_clock;
    uint64_t m_LastClock;
};

#endif // __IO_ALARM_H__
