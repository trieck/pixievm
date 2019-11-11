/////////////////////////////////////////////////////////////////////////////
//
//	PIXIECLOCK.CPP : 1,022,730 cycles per second clock
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "PixieClock.h"

/////////////////////////////////////////////////////////////////////////////
PixieClock::PixieClock() : ticksPerSecond(0)
{
    LARGE_INTEGER li;
    if (QueryPerformanceFrequency(&li)){
        ticksPerSecond = LI2INT64(&li);
    }

    reset();
}

/////////////////////////////////////////////////////////////////////////////
uint64_t PixieClock::LI2INT64(PLARGE_INTEGER li) const
{
    return (static_cast<uint64_t>((*li).HighPart) << 32) + (*li).LowPart;
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

    if (ticksPerSecond){
        const auto tstart = LI2INT64(const_cast<PLARGE_INTEGER>(&start));
        const auto tend = LI2INT64(&end);
        ndiff = (tend - tstart) / (ticksPerSecond / 1022730);
    }

    return ndiff;
}
