#include "stdafx.h"
#include "KeyboadMatrix.h"

/*	
 * Keyboard matrix:
 *	
 *	 Bit 7   6   5   4   3   2   1   0
 * 0     F1  F3  F5  F7 SPC DEL ESC HOM
 * 1    TAB LSH RSH CTR CRU CRD CRL CRR
 * 2     -  +/= BSP  [   ]   \  ENT  ; 
 * 3     '   ,   .   /   Q   W   E   R
 * 4     T   Y   U   I   O   P   A   S 
 * 5     D   F   G   H   J   K   L   Z
 * 6     X   C   V   B   N   M   0   1
 * 7     2   3   4   5   6   7   8   9
 */

#define MATRIX(a,b) (((a) << 3) | (b))

/////////////////////////////////////////////////////////////////////////////
KeyboardMatrix::KeyboardMatrix()
{
}

/////////////////////////////////////////////////////////////////////////////
KeyboardMatrix::~KeyboardMatrix()
{
}

/////////////////////////////////////////////////////////////////////////////
uint8_t KeyboardMatrix::translate(WPARAM virtkey, LPARAM keydata)
{
	int sc = (keydata & 0x00FF0000) >> 16;

	uint8_t result = -1;
	switch (virtkey) {
	case VK_F1: return MATRIX(0,7);
	case VK_F2: return MATRIX(0,7) | 0x80;
	case VK_F3: return MATRIX(0,6);
	case VK_F4: return MATRIX(0,6) | 0x80;
	case VK_F5: return MATRIX(0,5);
	case VK_F6: return MATRIX(0,5) | 0x80;
	case VK_F7: return MATRIX(0,4);
	case VK_F8: return MATRIX(0,4) | 0x80;
	case VK_SPACE: return MATRIX(0,3);
	case VK_DELETE: return MATRIX(0,2);
	case VK_ESCAPE: return MATRIX(0, 1);
	case VK_HOME: return MATRIX(0,0);
	default:
		break;
	};
	return result;
}
