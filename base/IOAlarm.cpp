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
    uint64_t clock = m_clock.clock();

    const uint64_t diff = clock - m_LastClock;
    if (diff != 0){
        PixieIO::getInstance()->clockTrigger();
    }

    m_LastClock = clock;
}
