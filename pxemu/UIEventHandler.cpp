/////////////////////////////////////////////////////////////////////////////
//
// UIEVENTHANDLER.CPP : UI event handling
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
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
	CMessageLoop* pLoop = _Module.GetMessageLoop();

	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
		if (!GetMessage(&msg, NULL, 0, 0)) {
			CPU::getInstance()->setShutdown(true, (int)msg.wParam);
			return;
		}

		::TranslateMessage(&msg);
		::DispatchMessage(&msg);

		if (pLoop->IsIdleMessage(&msg)) {
			pLoop->OnIdle(0);
		}
	}
}
