/////////////////////////////////////////////////////////////////////////////
//
// DISASSEMCMD.H : Monitor assembler command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __DISASSEMCMD_H__
#define __DISASSEMCMD_H__

#include "monitor.h"
#include "MiniDisassembler.h"

class DisassemCmd : public Command
{
public:
    void exec(const stringvec& v) override;
    void disassemble(word address);

private:
    MiniDisassembler disassembler;
};

#endif // __DISASSEMCMD_H__
