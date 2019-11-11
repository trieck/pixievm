/////////////////////////////////////////////////////////////////////////////
//
// DISASSEMCMD.CPP : Monitor assembler command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "DisassemCmd.h"

/////////////////////////////////////////////////////////////////////////////
void DisassemCmd::disassemble(word address)
{
    disassembler.disassemble(&address, &address);
}

/////////////////////////////////////////////////////////////////////////////
void DisassemCmd::exec(const stringvec& v)
{
    word start, end;
    if (v.size() == 0) {
        disassembler.disassemble(nullptr, nullptr);
    } else if (v.size() == 1) {
        int n = sscanf(v[0].c_str(), "%hx", &start);
        if (n != 1) {
            cerr << "? d [range]" << endl;
            return;
        }
        disassembler.disassemble(&start, nullptr);
    } else if (v.size() > 1) {
        int n = sscanf(v[0].c_str(), "%hx", &start);
        if (n != 1) {
            cerr << "? d [range]" << endl;
            return;
        }
        n = sscanf(v[1].c_str(), "%hx", &end);
        if (n != 1) {
            cerr << "? d [range]" << endl;
            return;
        }
        disassembler.disassemble(&start, &end);
    }
}
