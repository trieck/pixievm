
#ifndef __PALETTE_H__
#define __PALETTE_H__

/////////////////////////////////////////////////////////////////////////////
class Palette
{
	// Interface
public:
	static RGBQUAD Color(UINT index);

	enum { NUM_COLORS = 256 };

	// Implementation
private:
	static COLORREF m_palette[NUM_COLORS];
};

#endif // __PALETTE_H__
