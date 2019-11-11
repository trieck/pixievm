/////////////////////////////////////////////////////////////////////////////
//
// DUMPCMD.H : Monitor dump command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __DUMPCMD_H__
#define __DUMPCMD_H__

#include "monitor.h"

/////////////////////////////////////////////////////////////////////////////
class DumpCmd : public Command
{
public:
    void exec(const stringvec& v) override;
private:
    enum { LINESIZE = 16 }; // number of bytes per line to dump
    enum { DEFLINES = 9 };  // default number of lines

    bool init = false;  // have we been initialized
    word ip = 0;    // instruction pointer used during dump
};

#endif // __DUMPCMD_H__
