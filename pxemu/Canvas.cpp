#include "StdAfx.h"
#include "Canvas.h"

/////////////////////////////////////////////////////////////////////////////
Canvas::Canvas() : m_hWnd(nullptr)
{
}

void Canvas::Invalidate(CRect&& rc) const
{
    InvalidateRect(m_hWnd, rc, FALSE);
}

/////////////////////////////////////////////////////////////////////////////
void Canvas::SetPixel(uint16_t x, uint16_t y, uint8_t color) const
{
    m_bitmap.SetPixel(x, y, color);
}

/////////////////////////////////////////////////////////////////////////////
void Canvas::Render(CPaintDC& dc) const
{
    m_bitmap.Render(dc);
}
