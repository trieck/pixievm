// pxemuView.h : interface of the CPxEmuView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <atlapp.h>
#include <atlwinx.h>

#include "Canvas.h"
#include "KeyboardHandler.h"

class CPxEmuView : public CWindowImpl<CPxEmuView>,
    public KeyboardHandler<CPxEmuView>,
    public Canvas<CPxEmuView>
{
    using KeyboardHandlerBase = KeyboardHandler<CPxEmuView>;
    using CanvasBase = Canvas<CPxEmuView>;

public:
    DECLARE_WND_CLASS(NULL)

    BOOL PreTranslateMessage(MSG* /*pMsg*/)
    {
        return FALSE;
    }

BEGIN_MSG_MAP(CPxemuView)
        MSG_WM_DESTROY(OnDestroy)
        CHAIN_MSG_MAP(KeyboardHandlerBase)
        CHAIN_MSG_MAP(CanvasBase)
    END_MSG_MAP()

    void OnDestroy()
    {
    }
};
