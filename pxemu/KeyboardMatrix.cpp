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
int KeyboardMatrix::translate(WPARAM virtkey, LPARAM keydata)
{
    int sc = (keydata & 0x00FF0000) >> 16;

    int result = -1;
    switch (virtkey){
    case VK_F1: return MATRIX(0, 7);
    case VK_F2: return MATRIX(0, 7) | 0x80;
    case VK_F3: return MATRIX(0, 6);
    case VK_F4: return MATRIX(0, 6) | 0x80;
    case VK_F5: return MATRIX(0, 5);
    case VK_F6: return MATRIX(0, 5) | 0x80;
    case VK_F7: return MATRIX(0, 4);
    case VK_F8: return MATRIX(0, 4) | 0x80;
    case VK_SPACE: return MATRIX(0, 3);
    case VK_DELETE: return MATRIX(0, 2);
    case VK_ESCAPE: return MATRIX(0, 1);
    case VK_HOME: return MATRIX(0, 0);
    case VK_TAB: return MATRIX(1, 7);
    case VK_SHIFT: return sc == 0x36 ? /*R*/ MATRIX(1, 5) : MATRIX(1, 6);
    case VK_CONTROL: return MATRIX(1, 4);
    case VK_UP: return MATRIX(1, 3);
    case VK_DOWN: return MATRIX(1, 2);
    case VK_LEFT: return MATRIX(1, 1);
    case VK_RIGHT: return MATRIX(1, 0);
    case VK_OEM_MINUS: return MATRIX(2, 7);
    case VK_OEM_PLUS: return MATRIX(2, 6);
    case VK_BACK: return MATRIX(2, 5);
    case VK_OEM_4: return MATRIX(2, 4); /* [ */
    case VK_OEM_6: return MATRIX(2, 3); /* ] */
    case VK_OEM_5: return MATRIX(2, 2); /* \ */
    case VK_RETURN: return MATRIX(2, 1);
    case VK_OEM_1: return MATRIX(2, 0); /* ; */
    case VK_OEM_7: return MATRIX(3, 7); /* ' */
    case VK_OEM_COMMA: return MATRIX(3, 6);
    case VK_OEM_PERIOD: return MATRIX(3, 5);
    case VK_OEM_2: return MATRIX(3, 4); /* / */
    case '0': return MATRIX(6, 1);
    case '1': return MATRIX(6, 0);
    case '2': return MATRIX(7, 7);
    case '3': return MATRIX(7, 6);
    case '4': return MATRIX(7, 5);
    case '5': return MATRIX(7, 4);
    case '6': return MATRIX(7, 3);
    case '7': return MATRIX(7, 2);
    case '8': return MATRIX(7, 1);
    case '9': return MATRIX(7, 0);

    case 'Q': result = MATRIX(3, 3);
        break;
    case 'W': result = MATRIX(3, 2);
        break;
    case 'E': result = MATRIX(3, 1);
        break;
    case 'R': result = MATRIX(3, 0);
        break;
    case 'T': result = MATRIX(4, 7);
        break;
    case 'Y': result = MATRIX(4, 6);
        break;
    case 'U': result = MATRIX(4, 5);
        break;
    case 'I': result = MATRIX(4, 4);
        break;
    case 'O': result = MATRIX(4, 3);
        break;
    case 'P': result = MATRIX(4, 2);
        break;
    case 'A': result = MATRIX(4, 1);
        break;
    case 'S': result = MATRIX(4, 0);
        break;
    case 'D': result = MATRIX(5, 7);
        break;
    case 'F': result = MATRIX(5, 6);
        break;
    case 'G': result = MATRIX(5, 5);
        break;
    case 'H': result = MATRIX(5, 4);
        break;
    case 'J': result = MATRIX(5, 3);
        break;
    case 'K': result = MATRIX(5, 2);
        break;
    case 'L': result = MATRIX(5, 1);
        break;
    case 'Z': result = MATRIX(5, 0);
        break;
    case 'X': result = MATRIX(6, 7);
        break;
    case 'C': result = MATRIX(6, 6);
        break;
    case 'V': result = MATRIX(6, 5);
        break;
    case 'B': result = MATRIX(6, 4);
        break;
    case 'N': result = MATRIX(6, 3);
        break;
    case 'M': result = MATRIX(6, 2);
        break;
    };

    if (result != -1 && GetKeyState(VK_CAPITAL))
        result |= 0x80;

    return result;
}
