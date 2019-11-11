/////////////////////////////////////////////////////////////////////////////
//
// HELPCMD.H : Monitor help command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __HELPCMD_H__
#define __HELPCMD_H__

#include "monitor.h"

/////////////////////////////////////////////////////////////////////////////
class HelpCmd : public Command
{
public:
    void exec(const stringvec& v) override;
};

#endif // __HELPCMD_H__
