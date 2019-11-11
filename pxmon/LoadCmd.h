/////////////////////////////////////////////////////////////////////////////
//
// LOADCMD.H : Monitor load command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __LOADCMD_H__
#define __LOADCMD_H__

#include "monitor.h"

/////////////////////////////////////////////////////////////////////////////
class LoadCmd : public Command
{
public:
    void exec(const stringvec& v) override;
};

#endif // __LOADCMD_H__
