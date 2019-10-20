/////////////////////////////////////////////////////////////////////////////
//
// ALARM.H : Alarm handling
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __ALARM_H__
#define __ALARM_H__

#include "Handler.h"

class Alarms;
typedef auto_ptr<Alarms> AlarmsPtr;

/////////////////////////////////////////////////////////////////////////////
class Alarms 
{
	// Construction / Destruction
// Construction / Destruction
private:
	Alarms();
public:
	~Alarms();
	
	// Interface
	static Alarms* getInstance();

	template<class T> 
	void addAlarm() {
		alarms.push_back(new T());
	}

	void process();

	// Implementation
private:
	static AlarmsPtr instance;		// singleton instance

	typedef vector<Handler*> HandlerVec;
	HandlerVec alarms;
};

/////////////////////////////////////////////////////////////////////////////
#endif // __ALARM_H__
