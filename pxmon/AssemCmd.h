/////////////////////////////////////////////////////////////////////////////
//
// ASSEMCMD.H : Monitor assembler command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __ASSEMCMD_H__
#define __ASSEMCMD_H__

#include "monitor.h"
#include "MiniAssembler.h"

class AssemCmd : public Command
{
public:
    void exec(const stringvec& v) override;
    bool assemble(word address, const string& str);

private:
    MiniAssembler assembler;
};

#endif // __ASSEMCMD_H__
