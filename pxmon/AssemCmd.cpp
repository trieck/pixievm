/////////////////////////////////////////////////////////////////////////////
//
// ASSEMCMD.CPP : Monitor assembler command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "AssemCmd.h"

/////////////////////////////////////////////////////////////////////////////
AssemCmd::AssemCmd(Monitor* mon) : Command(mon)
{
}

/////////////////////////////////////////////////////////////////////////////
AssemCmd::~AssemCmd()
{
}

/////////////////////////////////////////////////////////////////////////////
void AssemCmd::exec(const stringvec& v)
{
    word address;
    if (v.size()){
        const auto n = sscanf(v[0].c_str(), "%hx", &address);
        if (n != 1){
            cerr << "? a [address]" << endl;
            return;
        }
        assembler.assemble(&address);
    } else{
        assembler.assemble(nullptr);
    }
}

/////////////////////////////////////////////////////////////////////////////
bool AssemCmd::assemble(word address, const string& str)
{
    return assembler.assemble(&address, str.c_str());
}
