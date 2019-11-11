/////////////////////////////////////////////////////////////////////////////
//
// SAVECMD.H : Monitor save command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __SAVECMD_H__
#define __SAVECMD_H__

#include "monitor.h"

/////////////////////////////////////////////////////////////////////////////
class SaveCmd : public Command
{
public:
    void exec(const stringvec& v) override;
};

#endif // __SAVECMD_H__
