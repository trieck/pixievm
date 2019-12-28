#include "StdAfx.h"
#include "Canvas.h"
#include "Alarm.h"
#include "RasterHandler.h"
#include "PxEmuApp.h"

extern PxEmuApp _Module;

#define XRGB(r,g,b) \
    ((COLORREF)(((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)))

/////////////////////////////////////////////////////////////////////////////
COLORREF Canvas::xrgbColor(UINT index)
{
    const auto color = Palette::Color(index);

    return XRGB(color.rgbRed, color.rgbGreen, color.rgbBlue);
}

/////////////////////////////////////////////////////////////////////////////
CSize Canvas::dims()
{
    return { CANVAS_CX_SIZE, CANVAS_CY_SIZE };
}

/////////////////////////////////////////////////////////////////////////////
CRect Canvas::boundingRect()
{
    const auto sz = dims();
    return { 0, 0, sz.cx, sz.cy };
}

/////////////////////////////////////////////////////////////////////////////
void Canvas::render(CRect&& rc, const byte* bits)
{
    prepare();

    D3DRECT rc3d;
    rc3d.x1 = rc.left;
    rc3d.y1 = rc.top;
    rc3d.x2 = rc.right;
    rc3d.y2 = rc.bottom;

    auto hr = m_dev->Clear(1, &rc3d, D3DCLEAR_TARGET, 0, 0, 0);
    ATL_CHECK_HR(hr);

    hr = m_dev->BeginScene();
    ATL_CHECK_HR(hr);

    IDirect3DSurface9Ptr buffer;
    hr = m_dev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &buffer);
    ATL_CHECK_HR(hr);

    D3DLOCKED_RECT rcLocked;
    hr = m_surface->LockRect(&rcLocked, rc, 0);
    ATL_CHECK_HR(hr);

    bitBlt(rcLocked, bits, rc);

    hr = m_surface->UnlockRect();
    ATL_CHECK_HR(hr);

    hr = m_dev->StretchRect(m_surface, &rc, buffer, nullptr, D3DTEXF_NONE);
    ATL_CHECK_HR(hr);

    buffer.Release();

    hr = m_dev->EndScene();
    ATL_CHECK_HR(hr);

    hr = m_dev->Present(nullptr, nullptr, nullptr, nullptr);
    ATL_CHECK_HR(hr);
}

/////////////////////////////////////////////////////////////////////////////
void Canvas::bitBlt(D3DLOCKED_RECT& dest, const byte* src, const CRect& rc)
{
    auto* pdest = static_cast<DWORD*>(dest.pBits);
    const auto pitch = dest.Pitch / sizeof(DWORD);
    const auto cx = rc.Width();
    const auto cy = rc.Height();

    for (auto y = 0; y < cy; ++y) {
        for (auto x = 0; x < cx; ++x) {
            pdest[y * pitch + x] = xrgbColor(*src++);
        }
    }
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
LRESULT Canvas::OnDestroy(WPARAM /*wParam*/, LPARAM /*lParam*/)
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
    const auto rc = boundingRect();

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

    ATL_CHECK_HR(hr);

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
    m_surface.Release();

    auto hr = m_dev->Reset(&m_pp);
    ATL_CHECK_HR(hr);

    const auto rc = boundingRect();

    hr = m_dev->CreateOffscreenPlainSurface(rc.Width(), rc.Height(),
                                            D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT,
                                            &m_surface, nullptr);
    ATL_CHECK_HR(hr);
}
