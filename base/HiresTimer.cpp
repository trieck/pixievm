/////////////////////////////////////////////////////////////////////////////
//
//	HIRESTIMER.CPP : High resolution timer
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "HiresTimer.h"

/////////////////////////////////////////////////////////////////////////////
HiresTimer::HiresTimer() : ticksPerSecond(0)
{
	LARGE_INTEGER li;
	if (QueryPerformanceFrequency(&li)) {
		ticksPerSecond = LI2INT64(&li);
	}

	reset();
}

/////////////////////////////////////////////////////////////////////////////
HiresTimer::~HiresTimer()
{
}

/////////////////////////////////////////////////////////////////////////////
INT64 HiresTimer::LI2INT64(PLARGE_INTEGER li) const
{
	return (((INT64)(*li).HighPart) << 32) + (*li).LowPart;
}

/////////////////////////////////////////////////////////////////////////////
void HiresTimer::reset()
{
	QueryPerformanceCounter(&start);
}

/////////////////////////////////////////////////////////////////////////////
uint64_t HiresTimer::jiffies() const
{
	LARGE_INTEGER end;
	QueryPerformanceCounter(&end);

	uint64_t nmillis = 0;

	if (ticksPerSecond) {
		uint64_t tstart = LI2INT64((PLARGE_INTEGER)&start);
		uint64_t tend = LI2INT64(&end);
		nmillis = (tend - tstart) / (ticksPerSecond / 60);	
	}

	return nmillis;
}

