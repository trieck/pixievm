
#pragma once

class Bitmap;
typedef auto_ptr<Bitmap> BitmapPtr;

/////////////////////////////////////////////////////////////////////////////
class Bitmap
{
	// Construction / Destruction
private:
	Bitmap();
public:
	~Bitmap();

	// Interface
	static Bitmap* getInstance();
	void Render(CPaintDC& dc);
	void SetPixel(uint16_t x, uint16_t y, uint8_t color);

	// Implementation
private:
	void CreateBitmap();
	static BitmapPtr instance;	// singleton instance
	CBitmap m_bm;
	CDC m_dc;
	LPBYTE m_pBits;
	LPBITMAPINFO m_bmi;
};

