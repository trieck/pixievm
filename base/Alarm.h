/////////////////////////////////////////////////////////////////////////////
//
// ALARM.H : Alarm handling
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __ALARM_H__
#define __ALARM_H__

#include "Handler.h"

/////////////////////////////////////////////////////////////////////////////
class Alarms 
{
	// Construction / Destruction
public:
	Alarms();
	~Alarms();
	
	// Interface
	template<class T> 
	void addAlarm() {
		alarms.push_back(new T());
	}

	void process();

	// Implementation
private:
	typedef vector<Handler*> HandlerVec;
	HandlerVec alarms;
};

// global alarm dispatcher
extern Alarms g_alarms;

/////////////////////////////////////////////////////////////////////////////
#endif // __ALARM_H__
