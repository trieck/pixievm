// pxemuView.h : interface of the CPxemuView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <atlapp.h>
#include <atlwinx.h>

#include "Canvas.h"
#include "KeyboardHandler.h"

class CPxemuView : public CWindowImpl<CPxemuView>, public KeyboardHandler<CPxemuView>
{
    using KeyboardHandlerBase = KeyboardHandler<CPxemuView>;

public:
    DECLARE_WND_CLASS(NULL)

    BOOL PreTranslateMessage(MSG* /*pMsg*/)
    {
        return FALSE;
    }

BEGIN_MSG_MAP(CPxemuView)
        MSG_WM_PAINT(OnPaint)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_DESTROY(OnDestroy)
        CHAIN_MSG_MAP(KeyboardHandlerBase)
    END_MSG_MAP()

    // Handler prototypes (uncomment arguments if needed):
    //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    //	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    //	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

    LRESULT OnCreate(LPCREATESTRUCT cs)
    {
        Canvas::instance().SetWnd(m_hWnd);
        return 0;
    }

    void OnDestroy()
    {
    }

    void OnPaint(CDCHandle /*hDC*/)
    {
        CPaintDC dc(*this);
        Canvas::instance().Render(dc);
    }
};
