
#pragma once

/////////////////////////////////////////////////////////////////////////////
class Bitmap
{
public:
	// Construction / Destruction
	Bitmap();
	~Bitmap();

	// Interface
	LPBITMAPINFO info() const { return m_bmi; }

	// Implementation
private:
	void CreateBitmap();
	CBitmap m_bm;
	CDC m_dc;
	CPalette m_palette;
	LPVOID m_pBits;
	LPBITMAPINFO m_bmi;
};

