/////////////////////////////////////////////////////////////////////////////
//
// ALARM.H : Alarm handling
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
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

    template <class T>
    using isHandler = std::enable_if<std::is_base_of<Handler, T>::value>;

    template <class T, class... _Types, typename isHandler<T>::type* = nullptr>
    void addAlarm(_Types&&... _Args)
    {
        alarms.push_back(std::make_unique<T>(std::forward<_Types>(_Args)...));
    }

    void process();

    // Implementation
private:
    using HandlerVec = vector<std::unique_ptr<Handler>>;
    HandlerVec alarms;

    friend class Singleton<Alarms>;
};

/////////////////////////////////////////////////////////////////////////////
#endif // __ALARM_H__
