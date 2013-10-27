
#pragma once

/////////////////////////////////////////////////////////////////////////////
class Canvas
{
public:
	enum { CX_SIZE = 640 };
	enum { CY_SIZE = 400 };

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

