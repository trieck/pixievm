/////////////////////////////////////////////////////////////////////////////
//
// STEPUNTILCMD.H : Step until return command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __STEPUNTILCMD_H__
#define __STEPUNTILCMD_H__

#include "Monitor.h"

/////////////////////////////////////////////////////////////////////////////
class StepUntilCmd : public Command, public TrapHandler
{
public:
    void exec(const stringvec& v) override;
    void trap(void* data) override;
};

#endif // __STEPUNTILCMD_H__
