#include "StdAfx.h"
#include "Canvas.h"
#include "Alarm.h"
#include "RasterHandler.h"

/////////////////////////////////////////////////////////////////////////////
CSize Canvas::GetDimensions()
{
    return { CANVAS_CX_SIZE, CANVAS_CY_SIZE };
}

/////////////////////////////////////////////////////////////////////////////
CRect Canvas::GetBoundingRect()
{
    CRect rc;

    const auto sz = GetDimensions();
    rc.right = sz.cx;
    rc.bottom = sz.cy;

    return rc;
}

/////////////////////////////////////////////////////////////////////////////
void Canvas::Refresh(CRect&& rc) const
{
    CClientDC dc(m_hWnd);
    m_bitmap.Render(dc, rc);
}

/////////////////////////////////////////////////////////////////////////////
LRESULT Canvas::OnCreate(HWND hWnd, UINT /*uMsg*/, WPARAM /*wParam*/, 
    LPARAM /*lParam*/)
{
    ASSERT(IsWindow(hWnd));
    m_hWnd = hWnd;

    Alarms::instance().addAlarm<RasterHandler>(this);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////
LRESULT Canvas::OnPaint(WPARAM wParam, LPARAM lParam)
{
    CPaintDC dc(m_hWnd);
    m_bitmap.Render(dc, dc.m_ps.rcPaint);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////
LRESULT Canvas::OnDestroy(WPARAM wParam, LPARAM lParam)
{
    m_surface.Release();
    m_dev.Release();

    return 0;
}

/////////////////////////////////////////////////////////////////////////////
void Canvas::SetPixel(uint16_t x, uint16_t y, uint8_t color) const
{
    m_bitmap.SetPixel(x, y, color);
}
