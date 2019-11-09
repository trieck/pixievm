/////////////////////////////////////////////////////////////////////////////
//
// ALARM.H : Alarm handling
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __ALARM_H__
#define __ALARM_H__

#include "Handler.h"
#include "Singleton.h"

/////////////////////////////////////////////////////////////////////////////
class Alarms : public Singleton<Alarms>
{
    // Construction / Destruction
    Alarms();

public:
    ~Alarms() = default;

    template <class T, typename std::enable_if<std::is_base_of<Handler, T>::value>::type* = nullptr>
    void addAlarm()
    {
        alarms.push_back(std::make_unique<T>());
    }

    void process();

    // Implementation
private:
    typedef vector<std::unique_ptr<Handler>> HandlerVec;
    HandlerVec alarms;

    friend class Singleton<Alarms>;
};

/////////////////////////////////////////////////////////////////////////////
#endif // __ALARM_H__
