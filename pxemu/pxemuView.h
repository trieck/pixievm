// pxemuView.h : interface of the CPxemuView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <atlwinx.h>

#include "Canvas.h"
#include "KeyboardHandler.h"

class CPxemuView : public CWindowImpl<CPxemuView>,
    public KeyboardHandler<CPxemuView>
{
    typedef KeyboardHandler<CPxemuView> KeyboardHandlerBase;

public:
    DECLARE_WND_CLASS(NULL)

    BOOL PreTranslateMessage(MSG* pMsg)
    {
        pMsg;
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
        m_canvas.SetWnd(m_hWnd);
        return 0;
    }

    void OnDestroy()
    {
    }

    void OnPaint(CDCHandle /*hDC*/)
    {
        CPaintDC dc(*this);
        m_canvas.Render(dc);
    }

private:
    Canvas m_canvas;
};
