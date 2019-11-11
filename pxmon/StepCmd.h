/////////////////////////////////////////////////////////////////////////////
//
// STEPCMD.H : Monitor step command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __STEPCMD_H__
#define __STEPCMD_H__

#include "monitor.h"

class StepCmd : public Command
{
public:
    void exec(const stringvec& v) override;
};

#endif // __STEPCMD_H__
