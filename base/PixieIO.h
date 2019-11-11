/////////////////////////////////////////////////////////////////////////////
//
// PixieIO.H : Pixie VM I/O handling
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __PIXIE_IO_H__
#define __PIXIE_IO_H__

#include "Singleton.h"

/////////////////////////////////////////////////////////////////////////////
class PixieIO : public Singleton<PixieIO>
{
    // Construction / Destruction
    PixieIO();
    friend class Singleton<PixieIO>;
public:
    ~PixieIO();

    // Interface
    void reset();
    uint8_t readRegister(uint16_t address);
    void writeRegister(uint16_t address, uint8_t b);
    void keyOn(uint8_t key_code);
    void keyOff(uint8_t key_code);
    void clockTrigger();

    // Implementation
private:
    enum { NREGS = 16 };    // number of registers
    byte regs[NREGS];       // registers
    byte key_matrix[8];     // keyboard matrix
};

/////////////////////////////////////////////////////////////////////////////

#endif // __PIXIE_IO_H__
