/////////////////////////////////////////////////////////////////////////////
//
// ALARM.CPP : Alarm handling
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Alarm.h"
#include "IOAlarm.h"

/////////////////////////////////////////////////////////////////////////////
Alarms::Alarms()
{
    // built-in alarms
    addAlarm<IOAlarm>();
}

/////////////////////////////////////////////////////////////////////////////
void Alarms::process()
{
    HandlerVec::const_iterator it = alarms.begin();
    for (; it != alarms.end(); ++it) {
        (*it)->handle();
    }
}
