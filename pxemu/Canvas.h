#pragma once

#include "StdAfx.h"
#include "Bitmap.h"
#include "Alarm.h"
#include "RasterHandler.h"

/////////////////////////////////////////////////////////////////////////////
template <typename T>
class Canvas
{
    // Construction / Destruction
public:
    Canvas() = default;
    ~Canvas() = default;

BEGIN_MSG_MAP(Canvas)
        MESSAGE_HANDLER_WND(WM_CREATE, OnCreate)
        MESSAGE_HANDLER_WND(WM_PAINT, OnPaint)
    END_MSG_MAP()

    // Interface
    static CSize GetDimensions()
    {
        return { CANVAS_CX_SIZE, CANVAS_CY_SIZE };
    }

    static CRect GetBoundingRect()
    {
        CRect rc;

        const auto sz = GetDimensions();
        rc.right = sz.cx;
        rc.bottom = sz.cy;

        return rc;
    }

    void Invalidate(CRect&& rc) const
    {
        InvalidateRect(m_hWnd, rc, FALSE);
    }

    LRESULT OnCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        ASSERT(IsWindow(hWnd));
        m_hWnd = hWnd;

        Alarms::instance().addAlarm<RasterHandler<T>>(this);

        return 0;
    }

    LRESULT OnPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        CPaintDC dc(hWnd);
        m_bitmap.Render(dc);
        bHandled = TRUE;
        return 0;
    }

    void SetPixel(uint16_t x, uint16_t y, uint8_t color) const
    {
        m_bitmap.SetPixel(x, y, color);
    }
    
    // Implementation
private:
    Bitmap m_bitmap;
    HWND m_hWnd = nullptr;
};
