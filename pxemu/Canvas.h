#pragma once

#include "Bitmap.h"

constexpr auto WM_CANVAS_SET_PIXEL = WM_USER + 1;

/////////////////////////////////////////////////////////////////////////////
class Canvas
{
    // Construction / Destruction
public:
    Canvas();

    // Interface
public:
    static CSize GetDimensions()
    {
        return {CX_SIZE, CY_SIZE};
    }

    static CRect GetBoundingRect()
    {
        CRect rc;

        const auto sz = GetDimensions();
        rc.right = sz.cx;
        rc.bottom = sz.cy;

        return rc;
    }

    void Invalidate(CRect& rc) const;

    void SetWnd(HWND hWnd)
    {
        m_hWnd = hWnd;
    }

    void Render(CPaintDC& dc);
    void SetPixel(uint16_t x, uint16_t y, uint8_t color) const;

    enum { CX_BORDER = 20 };

    enum { CY_BORDER = 20 };

    enum { CX_SIZE = 80 * 8 + (CX_BORDER * 2) };

    enum { CY_SIZE = 50 * 8 + (CY_BORDER * 2) };

    // Implementation
private:
    Bitmap m_bitmap;
    HWND m_hWnd;
};
