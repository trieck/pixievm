#include "stdafx.h"
#include "Bitmap.h"
#include "Palette.h"
#include "Canvas.h"

/////////////////////////////////////////////////////////////////////////////
Bitmap::Bitmap() : m_pBits(NULL), m_bmi(NULL)
{
    CreateBitmap();
}

/////////////////////////////////////////////////////////////////////////////
Bitmap::~Bitmap()
{
    GlobalFree(m_bmi);
}

/////////////////////////////////////////////////////////////////////////////
void Bitmap::SetPixel(uint16_t x, uint16_t y, uint8_t color)
{
    m_pBits[y * m_bmi->bmiHeader.biWidth + x] = color;
}

/////////////////////////////////////////////////////////////////////////////
void Bitmap::CreateBitmap()
{
    m_dc.CreateCompatibleDC(NULL);

    UINT sz = sizeof(BITMAPINFOHEADER) +
        sizeof(RGBQUAD) * Palette::NUM_COLORS;

    m_bmi = (BITMAPINFO*)GlobalAlloc(GPTR, sz);
    m_bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    m_bmi->bmiHeader.biWidth = Canvas::CX_SIZE;
    m_bmi->bmiHeader.biHeight = -Canvas::CY_SIZE; // top-down
    m_bmi->bmiHeader.biPlanes = 1;
    m_bmi->bmiHeader.biBitCount = 8; // 256 colors
    m_bmi->bmiHeader.biCompression = BI_RGB;
    m_bmi->bmiHeader.biClrUsed = Palette::NUM_COLORS;

    for (UINT i = 0; i < Palette::NUM_COLORS; ++i){
        m_bmi->bmiColors[i] = Palette::Color(i);
    }

    m_bm.CreateDIBSection(m_dc, m_bmi, DIB_RGB_COLORS,
                          (LPVOID*)&m_pBits, NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////
void Bitmap::Render(CPaintDC& dc)
{
    CRect rc(dc.m_ps.rcPaint);

    dc.SetDIBitsToDevice(
        rc.left, // x-coordinate of upper left of dest. rectangle
        rc.top, // y-coordinate of upper left of dest. rectangle
        rc.Width(), // width of the image
        rc.Height(), // height of the image 
        rc.left, // x-coordinate of the upper left of image
        rc.top, // y-coordinate of the upper left of image
        rc.top, // starting scan line of image
        rc.top + rc.Height(), // number of scan lines contained in the array
        m_pBits, // pointer to color data
        m_bmi, // pointer to BITMAPINFO structure
        DIB_RGB_COLORS
    );
}
