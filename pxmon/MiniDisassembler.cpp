/////////////////////////////////////////////////////////////////////////////
//
// MINIDISASSEMBLER.CPP : Mini Disassembler
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "memory.h"
#include "MiniDisassembler.h"
#include "CPU.H"

/////////////////////////////////////////////////////////////////////////////
MiniDisassembler::MiniDisassembler() : init(false)
{
}

/////////////////////////////////////////////////////////////////////////////
byte MiniDisassembler::fetch()
{
    return Memory::instance().fetch(ip++);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::disassemble(word* start, word* end)
{
    word lastip = 0;
    if (start){
        /* start address supplied */
        ip = *start;
        init = true;
    } else if (!init){
        /* not entered */
        ip = CPU::instance().getIP();
        init = true;
    }

    for (int i = 0; ip >= lastip && (end ? ip <= *end : i < NLINES); i++){
        printip();
        lastip = ip;
        byte b = fetch();
        PxDisassembler::disassemble(b);
    }
}
