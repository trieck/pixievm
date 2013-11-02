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
	void addHandler(Handler* pHandler);
	void process();

	// Implementation
private:
	typedef vector<Handler*> HandlerVec;
	HandlerVec handlers;
};

// global alarm dispatcher
extern Alarms g_alarms;

/////////////////////////////////////////////////////////////////////////////
#endif // __ALARM_H__
