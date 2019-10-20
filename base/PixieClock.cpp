/////////////////////////////////////////////////////////////////////////////
//
//	PIXIECLOCK.CPP : 1,022,730 cycles per second clock
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "PixieClock.h"

/////////////////////////////////////////////////////////////////////////////
PixieClock::PixieClock() : ticksPerSecond(0)
{
	LARGE_INTEGER li;
	if (QueryPerformanceFrequency(&li)) {
		ticksPerSecond = LI2INT64(&li);
	}

	reset();
}

/////////////////////////////////////////////////////////////////////////////
PixieClock::~PixieClock()
{
}

/////////////////////////////////////////////////////////////////////////////
uint64_t PixieClock::LI2INT64(PLARGE_INTEGER li) const
{
	return (((uint64_t)(*li).HighPart) << 32) + (*li).LowPart;
}

/////////////////////////////////////////////////////////////////////////////
void PixieClock::reset()
{
	QueryPerformanceCounter(&start);
}

/////////////////////////////////////////////////////////////////////////////
uint64_t PixieClock::clock() const
{
	LARGE_INTEGER end;
	QueryPerformanceCounter(&end);

	uint64_t ndiff = 0;

	if (ticksPerSecond) {
		uint64_t tstart = LI2INT64((PLARGE_INTEGER)&start);
		uint64_t tend = LI2INT64(&end);
		ndiff = (tend - tstart) / (ticksPerSecond / 1022730);	
	}

	return ndiff;
}

