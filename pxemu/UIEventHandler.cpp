/////////////////////////////////////////////////////////////////////////////
//
// UIEVENTHANDLER.CPP : UI event handling
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "StdAfx.h"
#include "UIEventHandler.h"
#include "CPU.H"
#include "PxEmuApp.h"

extern PxEmuApp _Module;

/////////////////////////////////////////////////////////////////////////////
void UIEventHandler::handle()
{
    auto pLoop = _Module.GetMessageLoop();

    while (PeekMessage(&m_msg, nullptr, 0, 0, PM_NOREMOVE)) {
        if (!GetMessage(&m_msg, nullptr, 0, 0)) {
            CPU::instance().setShutdown(true, static_cast<int>(m_msg.wParam));
            return;
        }

        if (!PreTranslateMessage(&m_msg)) {
            TranslateMessage(&m_msg);
            ::DispatchMessage(&m_msg);
        }

        if (IsIdleMessage(&m_msg)) {
            pLoop->OnIdle(0);
        }
    }
}
