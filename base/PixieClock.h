/////////////////////////////////////////////////////////////////////////////
//
//	PIXIECLOCK.H : 1,022,730 cycles per second clock
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __PIXIE_CLOCK_H__
#define __PIXIE_CLOCK_H__

/////////////////////////////////////////////////////////////////////////////
class PixieClock
{
public:
    PixieClock();
    ~PixieClock();

    void reset();
    uint64_t clock() const;
private:
    uint64_t LI2INT64(PLARGE_INTEGER li) const;

    LARGE_INTEGER start{};
    uint64_t ticksPerSecond;
};

#endif // __PIXIE_CLOCK_H__
