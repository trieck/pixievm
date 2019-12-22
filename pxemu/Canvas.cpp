#include "StdAfx.h"
#include "Canvas.h"
#include "Alarm.h"
#include "RasterHandler.h"
#include "PxEmuApp.h"

extern PxEmuApp _Module;

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
LPBYTE Canvas::bits() const
{
    return m_bitmap.bits();
}

/////////////////////////////////////////////////////////////////////////////
LONG Canvas::pitch() const
{
    return m_bitmap.pitch();
}

/////////////////////////////////////////////////////////////////////////////
void Canvas::refresh(CRect&& rc) const
{
    CClientDC dc(m_hWnd);
    m_bitmap.render(dc, std::forward<CRect>(rc));
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
    m_bitmap.render(dc, dc.m_ps.rcPaint);

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
LRESULT Canvas::OnSize(WPARAM wParam, LPARAM lParam)
{
    const auto size = CSize(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

    if (size.cx != 0 && size.cy != 0 && !m_dev) {
        createDevice();
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////
void Canvas::createDevice()
{
    CRect rc;
    GetClientRect(m_hWnd, &rc);

    m_pp.BackBufferFormat = D3DFMT_X8R8G8B8;
    m_pp.BackBufferCount = 1;
    m_pp.BackBufferWidth = rc.Width();
    m_pp.BackBufferHeight = rc.Height();
    m_pp.Windowed = TRUE;
    m_pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    m_pp.hDeviceWindow = m_hWnd;

    auto d3d = _Module.direct3d();
    const auto hr = d3d->CreateDevice(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        m_hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &m_pp,
        &m_dev);
    ATL_CHECK_HR(hr)

   reset();
}

/////////////////////////////////////////////////////////////////////////////
void Canvas::prepare()
{
    const auto hr = m_dev->TestCooperativeLevel();
    if (hr == D3DERR_DEVICENOTRESET) {
        reset();
    }
}

/////////////////////////////////////////////////////////////////////////////
void Canvas::reset()
{
    CRect rc;
    GetClientRect(m_hWnd, &rc);

    m_surface.Release();

    auto hr = m_dev->Reset(&m_pp);
    ATL_CHECK_HR(hr)

    hr = m_dev->CreateOffscreenPlainSurface(rc.Width(), rc.Height(), 
        D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, 
        &m_surface, nullptr);
    ATL_CHECK_HR(hr)
}

