// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once

#include "common.h"

#include <atlbase.h>
#include <atltypes.h>
#include <atlapp.h>
#include <atlwin.h>
#include <atlcrack.h>

#define MESSAGE_HANDLER_WND(msg, func) \
    if (uMsg == msg) { \
        bHandled = TRUE; \
        lResult = func(hWnd, uMsg, wParam, lParam, bHandled); \
        if (bHandled) \
            return TRUE; \
    }

extern CAppModule _Module;
