/////////////////////////////////////////////////////////////////////////////
//
// KEYBOARDHANDLER.H : keyboard handling
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __KEYBOARD_HANDLER_H__
#define __KEYBOARD_HANDLER_H__

#include "KeyboadMatrix.h"
#include "PixieIO.h"

/////////////////////////////////////////////////////////////////////////////
class KeyboardHandler
{
    // Construction / Destruction
public:
    KeyboardHandler() = default;
    ~KeyboardHandler() = default;

    // Interface
BEGIN_MSG_MAP(KeyboardHandler)
    MESSAGE_HANDLER_EX2(WM_KEYDOWN, OnKeyDown)
    MESSAGE_HANDLER_EX2(WM_KEYUP, OnKeyUp)
END_MSG_MAP()

    // Implementation
private:
    LRESULT OnKeyDown(WPARAM wParam, LPARAM lParam)
    {
        const auto keyCode = KeyboardMatrix::translate(wParam, lParam);
        if (keyCode < 0 || keyCode >= 256)
            return 0;

        PixieIO::instance().keyOn(keyCode);

        return 0;
    }

    LRESULT OnKeyUp(WPARAM wParam, LPARAM lParam)
    {
        const auto key_code = KeyboardMatrix::translate(wParam, lParam);
        if (key_code < 0 || key_code >= 256)
            return 0;

        PixieIO::instance().keyOff(key_code);

        return 0;
    }
};

#endif // __KEYBOARD_HANDLER_H__
