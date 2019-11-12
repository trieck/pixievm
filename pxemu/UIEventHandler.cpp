/////////////////////////////////////////////////////////////////////////////
//
// UIEVENTHANDLER.CPP : UI event handling
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "StdAfx.h"
#include "UIEventHandler.h"
#include "CPU.H"

/////////////////////////////////////////////////////////////////////////////
void UIEventHandler::handle()
{
    auto pLoop = _Module.GetMessageLoop();

    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE)) {
        if (!GetMessage(&msg, nullptr, 0, 0)) {
            CPU::instance().setShutdown(true, static_cast<int>(msg.wParam));
            return;
        }

        if (!PreTranslateMessage(&msg)) {
            TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }

        if (IsIdleMessage(&msg)) {
            pLoop->OnIdle(0);
        }
    }
}
