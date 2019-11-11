/////////////////////////////////////////////////////////////////////////////
//
// QUITCMD.H: Monitor quit command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __QUITCMD_H__
#define __QUITCMD_H__

#include "monitor.h"

/////////////////////////////////////////////////////////////////////////////
class QuitCmd : public Command
{
public:
    void exec(const stringvec& v) override;
};

#endif // __QUITCMD_H__
