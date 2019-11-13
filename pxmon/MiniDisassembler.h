/////////////////////////////////////////////////////////////////////////////
//
// MINIDISASSEMBLER.H : Mini Disassembler
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MINIDISASSEMBLER_H__
#define __MINIDISASSEMBLER_H__

#include "PxDisassembler.h"

/////////////////////////////////////////////////////////////////////////////
class MiniDisassembler : public PxDisassembler
{
    // Construction / Destruction
public:
    MiniDisassembler();

    // Interface
    void disassemble(word* start, word* end);

    // Implementation
protected:
    byte fetch() override;
private:
    enum { NLINES = 16 };

    bool init; // have we been entered ?
};

/////////////////////////////////////////////////////////////////////////////

#endif // __MINIDISASSEMBLER_H__
