///////////////////////////////////////////////////////////////////////////////
//
// HANDLER.H : Handler interface
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __HANDLER_H__
#define __HANDLER_H__

/////////////////////////////////////////////////////////////////////////////
class Handler
{
    // Construction / Destruction
public:
    Handler() = default;

    virtual ~Handler() = default;

    // Interface
    virtual void handle() = 0;
};

using LPHANDLER = Handler*;

/////////////////////////////////////////////////////////////////////////////

#endif  // __HANDLER_H__
