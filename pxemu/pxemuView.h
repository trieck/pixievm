// pxemuView.h : interface of the CPxEmuView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <atlapp.h>
#include <atlwinx.h>

#include "Canvas.h"
#include "KeyboardHandler.h"

class CPxEmuView : public CWindowImpl<CPxEmuView>
{
public:
    DECLARE_WND_CLASS(NULL)

    BOOL PreTranslateMessage(MSG* /*pMsg*/)
    {
        return FALSE;
    }

BEGIN_MSG_MAP(CPxemuView)
    CHAIN_MSG_MAP_MEMBER(m_keyHandler)
    CHAIN_MSG_MAP_MEMBER(m_canvas)
END_MSG_MAP()

private:
    Canvas m_canvas;
    KeyboardHandler m_keyHandler;
};
