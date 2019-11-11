/////////////////////////////////////////////////////////////////////////////
//
// QUITCMD.CPP : Monitor quit command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "QuitCmd.h"
#include "CPU.H"

/////////////////////////////////////////////////////////////////////////////
void QuitCmd::exec(const stringvec& v)
{
    CPU::instance().setShutdown(true);
    Monitor::instance().setExit(true);
}
