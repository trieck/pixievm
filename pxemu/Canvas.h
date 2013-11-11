
#pragma once

#include "Bitmap.h"

class Canvas;
typedef auto_ptr<Canvas> CanvasPtr;

/////////////////////////////////////////////////////////////////////////////
class Canvas
{
		// Construction / Destruction
private:
	Canvas();
public:
	~Canvas();

	// Interface
public:
	static Canvas*getInstance();

	static CSize GetDimensions() {
		return CSize(CX_SIZE, CY_SIZE);
	}

	static CRect GetBoundingRect() {
		CRect rc;

		CSize sz = GetDimensions();
		rc.right = sz.cx;
		rc.bottom = sz.cy;

		return rc;
	}

	void Invalidate(CRect& rc);
	void SetWnd(HWND hWnd) { m_hWnd = hWnd; }
	void Render(CPaintDC& dc);
	void SetPixel(uint16_t x, uint16_t y, uint8_t color);

	enum { CX_BORDER = 20 };
	enum { CY_BORDER = 20 };
	enum { CX_SIZE = 80*8 + (CX_BORDER*2) };
	enum { CY_SIZE = 50*8 + (CY_BORDER*2) };

	// Implementation
private:
	static CanvasPtr instance;	// singleton instance
	Bitmap m_bitmap;
	HWND m_hWnd;
};

