/////////////////////////////////////////////////////////////////////////////
//
// KEYBOARDMATRIX.H : keyboard matrix
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __KEYBOARD_MATRIX_H__
#define __KEYBOARD_MATRIX_H__

/////////////////////////////////////////////////////////////////////////////
class KeyboardMatrix
{
    // Construction / Destruction
public:
    KeyboardMatrix();
    ~KeyboardMatrix();

    // Interface
    static int translate(WPARAM virtkey, LPARAM keydata);

    // Implementation
private:
};

#endif // __KEYBOARD_MATRIX_H__
