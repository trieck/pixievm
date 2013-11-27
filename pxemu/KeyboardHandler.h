/////////////////////////////////////////////////////////////////////////////
//
// KEYBOARDHANDLER.H : keyboard handling
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __KEYBOARD_HANDLER_H__
#define __KEYBOARD_HANDLER_H__

#include "KeyboadMatrix.h"

/////////////////////////////////////////////////////////////////////////////
template <class T>
class KeyboardHandler
{
	// Construction / Destruction
public:
	KeyboardHandler() {}
	~KeyboardHandler() {}

	// Interface
	BEGIN_MSG_MAP(KeyboardHandler)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
	END_MSG_MAP()

	// Implementation
private:
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		uint8_t result = KeyboardMatrix::translate(wParam, lParam);

		return 0;
	}

	LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		uint8_t result = KeyboardMatrix::translate(wParam, lParam);

		return 0;
	}
};

#endif // __KEYBOARD_HANDLER_H__