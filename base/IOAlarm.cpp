/////////////////////////////////////////////////////////////////////////////
//
// IOALARM.CPP : I/O alarm
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "IOAlarm.h"
#include "PixieIO.h"

/////////////////////////////////////////////////////////////////////////////
IOAlarm::IOAlarm()
{
    m_LastClock = m_clock.clock();
}

/////////////////////////////////////////////////////////////////////////////
IOAlarm::~IOAlarm()
{
}

/////////////////////////////////////////////////////////////////////////////
void IOAlarm::handle()
{
    const auto clock = m_clock.clock();

    const auto diff = clock - m_LastClock;
    if (diff != 0) {
        PixieIO::instance().clockTrigger();
    }

    m_LastClock = clock;
}
