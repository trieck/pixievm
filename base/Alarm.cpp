/////////////////////////////////////////////////////////////////////////////
//
// ALARM.CPP : Alarm handling
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Alarm.h"

// global alaram dispatcher
Alarms g_alarms;

/////////////////////////////////////////////////////////////////////////////
Alarms::Alarms()
{
}

/////////////////////////////////////////////////////////////////////////////
Alarms::~Alarms()
{
	HandlerVec::const_iterator it = handlers.begin();
	for ( ; it != handlers.end(); ++it) {
		delete *it;
	}
}

/////////////////////////////////////////////////////////////////////////////
void Alarms::addHandler(Handler* pHandler)
{
	handlers.push_back(pHandler);
}

/////////////////////////////////////////////////////////////////////////////
void Alarms::process()
{
	HandlerVec::const_iterator it = handlers.begin();
	for ( ; it != handlers.end(); ++it) {
		(*it)->handle();
	}
}