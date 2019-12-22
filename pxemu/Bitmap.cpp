#include "StdAfx.h"
#include "Bitmap.h"
#include "Palette.h"
#include "Canvas.h"

/////////////////////////////////////////////////////////////////////////////
Bitmap::Bitmap() : m_pBits(nullptr), m_bmi(nullptr)
{
    create();
}

/////////////////////////////////////////////////////////////////////////////
void Bitmap::create()
{
    m_dc.CreateCompatibleDC(nullptr);

    const auto sz = sizeof(BITMAPINFOHEADER) +
        sizeof(RGBQUAD) * Palette::NUM_COLORS;

    m_bmi.reset(reinterpret_cast<LPBITMAPINFO>(std::malloc(sz)));

    m_bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    m_bmi->bmiHeader.biWidth = CANVAS_CX_SIZE;
    m_bmi->bmiHeader.biHeight = -CANVAS_CY_SIZE; // top-down
    m_bmi->bmiHeader.biPlanes = 1;
    m_bmi->bmiHeader.biBitCount = 8; // 256 colors
    m_bmi->bmiHeader.biCompression = BI_RGB;
    m_bmi->bmiHeader.biClrUsed = Palette::NUM_COLORS;

    for (auto i = 0; i < Palette::NUM_COLORS; ++i) {
        m_bmi->bmiColors[i] = Palette::Color(i);
    }

    m_bm.CreateDIBSection(m_dc, m_bmi.get(), DIB_RGB_COLORS,
                          reinterpret_cast<void**>(&m_pBits), nullptr, 0);
}

/////////////////////////////////////////////////////////////////////////////
void Bitmap::render(CDC& dc, CRect&& rc) const
{
    dc.SetDIBitsToDevice(
        rc.left,                // x-coordinate of upper left of dest. rectangle
        rc.top,                 // y-coordinate of upper left of dest. rectangle
        rc.Width(),             // width of the image
        rc.Height(),            // height of the image
        rc.left,                // x-coordinate of the upper left of image
        rc.top,                 // y-coordinate of the upper left of image
        rc.top,                 // starting scan line of image
        rc.top + rc.Height(),   // number of scan lines contained in the array
        m_pBits,                // pointer to color data
        m_bmi.get(),            // pointer to BITMAPINFO structure
        DIB_RGB_COLORS
    );
}

LPBYTE Bitmap::bits() const
{
    return m_pBits;
}

LONG Bitmap::pitch() const
{
    return m_bmi->bmiHeader.biWidth;
}
