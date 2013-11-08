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
void Bitmap::CreateBitmap()
{
	ATLASSERT(NULL != m_dc.CreateCompatibleDC(NULL));

	UINT sz = sizeof(BITMAPINFOHEADER) +  
		sizeof(RGBQUAD) * Palette::NUM_COLORS;

	m_bmi = (BITMAPINFO*)GlobalAlloc(GPTR, sz);
	m_bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_bmi->bmiHeader.biWidth = Canvas::CX_SIZE;
	m_bmi->bmiHeader.biHeight = -Canvas::CY_SIZE; // top-down
	m_bmi->bmiHeader.biPlanes = 1;
	m_bmi->bmiHeader.biBitCount = 8;	// 256 colors
	m_bmi->bmiHeader.biCompression = BI_RGB;
	m_bmi->bmiHeader.biClrUsed = Palette::NUM_COLORS;

	for (UINT i = 0; i < Palette::NUM_COLORS; ++i) {
		m_bmi->bmiColors[i] = Palette::Color(i);
	}

	ATLASSERT(NULL != m_bm.CreateDIBSection(m_dc, m_bmi, DIB_RGB_COLORS, &m_pBits, NULL, NULL));

	m_dc.SelectBitmap(m_bm);

	ATLASSERT(Palette::NUM_COLORS == m_dc.SetDIBColorTable(0, Palette::NUM_COLORS, m_bmi->bmiColors));
}