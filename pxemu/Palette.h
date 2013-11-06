
#ifndef __PALETTE_H__
#define __PALETTE_H__

/////////////////////////////////////////////////////////////////////////////
class Palette
{
	// Construction / Destruction
public:
	Palette();
	~Palette();

	// Interface

	// Implementation
private:
	enum { NUM_COLORS = 256 };
	static COLORREF palette[NUM_COLORS];
};

#endif // __PALETTE_H__
