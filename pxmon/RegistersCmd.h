/////////////////////////////////////////////////////////////////////////////
//
// REGISTERSCMD.H : Monitor registers command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __REGISTERSCMD_H__
#define __REGISTERSCMD_H__

#include "monitor.h"

/////////////////////////////////////////////////////////////////////////////
class RegistersCmd : public Command
{
public:
    void exec(const stringvec& v) override;
};

#endif // __REGISTERSCMD_H__
