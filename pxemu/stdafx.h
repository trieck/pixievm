#pragma once

#include "common.h"
#include <atlbase.h>
#include <atltypes.h>
#include <atlapp.h>
#include <atlwin.h>
#include <atlcrack.h>
#include <d3d9.h>

#define MESSAGE_HANDLER_WND(msg, func) \
    if (uMsg == (msg)) { \
        lResult = func(hWnd, uMsg, wParam, lParam); \
        return TRUE; \
    }

#define MESSAGE_HANDLER_EX2(msg, func) \
    if (uMsg == (msg)) { \
        lResult = func(wParam, lParam); \
        return TRUE; \
    }

#define USING_COMPTR(i) \
    using i##Ptr = CComPtr<i>

USING_COMPTR(IDirect3D9);
USING_COMPTR(IDirect3DDevice9);
USING_COMPTR(IDirect3DSurface9);

#define ATL_CHECK_HR(hr) \
    do { \
        if (FAILED((hr))) { \
            ATLTRACE(atlTraceException, 0, _T("ATL_CHECK_HR: hr = 0x%x\n"), hr); \
            ATLASSERT(FALSE); \
        } \
    } while(0)

