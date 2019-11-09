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
QuitCmd::QuitCmd(Monitor* mon) : Command(mon)
{
}

/////////////////////////////////////////////////////////////////////////////
QuitCmd::~QuitCmd()
{
}

/////////////////////////////////////////////////////////////////////////////
void QuitCmd::exec(const stringvec& v)
{
    CPU::instance().setShutdown(true);
    
    Monitor* mon = getMonitor();
    mon->setExit(true);
}
