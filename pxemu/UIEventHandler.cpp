/////////////////////////////////////////////////////////////////////////////
//
// UIEVENTHANDLER.CPP : UI event handling
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "UIEventHandler.h"
#include "CPU.H"

/////////////////////////////////////////////////////////////////////////////
UIEventHandler::UIEventHandler()
{
}

/////////////////////////////////////////////////////////////////////////////
UIEventHandler::~UIEventHandler()
{
}

/////////////////////////////////////////////////////////////////////////////
void UIEventHandler::handle()
{
    auto pLoop = _Module.GetMessageLoop();

    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE)){
        if (!GetMessage(&msg, nullptr, 0, 0)){
            CPU::getInstance()->setShutdown(true, static_cast<int>(msg.wParam));
            return;
        }

        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);

        if (WTL::CMessageLoop::IsIdleMessage(&msg)){
            pLoop->OnIdle(0);
        }
    }
}
