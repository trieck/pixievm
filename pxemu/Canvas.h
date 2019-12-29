#pragma once

#include "StdAfx.h"
#include "Palette.h"

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
    MESSAGE_HANDLER_EX2(WM_DESTROY, OnDestroy)
    MESSAGE_HANDLER_EX2(WM_PAINT, OnPaint)
    MESSAGE_HANDLER_EX2(WM_SIZE, OnSize)
END_MSG_MAP()

    // Interface
    static CSize dims();
    static CRect boundingRect();
    void render(const CRect& rc, const byte* bits);

    // Message handlers
    LRESULT OnCreate(HWND hWnd, UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/);
    LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
    LRESULT OnPaint(WPARAM wParam, LPARAM lParam);
    LRESULT OnSize(WPARAM wParam, LPARAM lParam);
    
    // Implementation
private:
    static void bitBlt(D3DLOCKED_RECT& dest, const byte* src, const CRect& rc);
    static COLORREF xrgbColor(UINT index);

    void createDevice();
    void prepare();
    void reset();
    void render(const CRect &rc);

    IDirect3DDevice9Ptr m_dev;
    IDirect3DSurface9Ptr m_surface;
    D3DPRESENT_PARAMETERS m_pp{};
    HWND m_hWnd = nullptr;
};
