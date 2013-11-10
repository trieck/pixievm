
#pragma once

/////////////////////////////////////////////////////////////////////////////
class Canvas
{
public:
	enum { CX_BORDER = 10 };
	enum { CY_BORDER = 10 };
	enum { CX_SIZE = 80*8 + (CX_BORDER*2) };
	enum { CY_SIZE = 50*8 + (CY_BORDER*2) };

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
};

