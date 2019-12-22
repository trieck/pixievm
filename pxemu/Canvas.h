#pragma once

#include "StdAfx.h"
#include "Bitmap.h"

constexpr auto CANVAS_CX_BORDER = 20;
constexpr auto CANVAS_CY_BORDER = 20;

constexpr auto CANVAS_CX_SIZE = 80 * 8 + (CANVAS_CX_BORDER * 2);
constexpr auto CANVAS_CY_SIZE = 50 * 8 + (CANVAS_CY_BORDER * 2);

/////////////////////////////////////////////////////////////////////////////
class Canvas
{
    // Construction / Destruction
public:
    Canvas() = default;
    ~Canvas() = default;

BEGIN_MSG_MAP(Canvas)
    MESSAGE_HANDLER_WND(WM_CREATE, OnCreate)
    MESSAGE_HANDLER_EX2(WM_PAINT, OnPaint)
    MESSAGE_HANDLER_EX2(WM_DESTROY, OnDestroy)
END_MSG_MAP()

    // Interface
    static CSize GetDimensions();
    static CRect GetBoundingRect();

    LPBYTE bits() const;
    LONG pitch() const;

    void Refresh(CRect&& rc) const;

    // Message handlers
    LRESULT OnCreate(HWND hWnd, UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/);
    LRESULT OnPaint(WPARAM wParam, LPARAM lParam);
    LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
    
    // Implementation
private:
    IDirect3DDevice9Ptr m_dev;
    IDirect3DSurface9Ptr m_surface;
    D3DPRESENT_PARAMETERS m_pp{};
    Bitmap m_bitmap;
    HWND m_hWnd = nullptr;
};
