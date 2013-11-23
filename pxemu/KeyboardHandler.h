/////////////////////////////////////////////////////////////////////////////
//
// KEYBOARDHANDLER.H : keyboard handling
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __KEYBOARD_HANDLER_H__
#define __KEYBOARD_HANDLER_H__

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
	END_MSG_MAP()

	// Implementation
private:
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}

};

#endif // __KEYBOARD_HANDLER_H__