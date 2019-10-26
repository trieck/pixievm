/////////////////////////////////////////////////////////////////////////////
//
// ALARM.CPP : Alarm handling
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Alarm.h"
#include "IOAlarm.h"

AlarmsPtr Alarms::instance(getInstance());

/////////////////////////////////////////////////////////////////////////////
Alarms::Alarms()
{
    // built-in alarms
    addAlarm<IOAlarm>();
}

/////////////////////////////////////////////////////////////////////////////
Alarms::~Alarms()
{
    HandlerVec::const_iterator it = alarms.begin();
    for (; it != alarms.end(); ++it){
        delete *it;
    }
}

/////////////////////////////////////////////////////////////////////////////
Alarms* Alarms::getInstance()
{
    if (instance.get() == nullptr){
        instance = AlarmsPtr(new Alarms);
    }

    return instance.get();
}

/////////////////////////////////////////////////////////////////////////////
void Alarms::process()
{
    HandlerVec::const_iterator it = alarms.begin();
    for (; it != alarms.end(); ++it){
        (*it)->handle();
    }
}
