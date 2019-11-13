/////////////////////////////////////////////////////////////////////////////
//
// CPU.H : Pixie VM CPU
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __CPU_H__
#define __CPU_H__

#include "Singleton.h"

#define NEG_FLAG (0x80)
#define OVERFLOW_FLAG (0x40)
#define BRK_FLAG (0x08)
#define INT_DISABLE_FLAG (0x04)
#define ZERO_FLAG (0x02)
#define CARRY_FLAG (0x01)

/////////////////////////////////////////////////////////////////////////////
class CPU : public Singleton<CPU>
{
    // Construction / Destruction
    CPU();
    friend class Singleton<CPU>;

public:
    ~CPU();

    int run();
    void reset();

    word getA() const;
    word getB() const;
    word getC() const;
    word getD() const;
    word getX() const;
    word getSP() const;
    word getIP() const;
    word getFL() const;

    byte getAL() const;
    byte getAH() const;
    byte getBL() const;
    byte getBH() const;
    byte getCL() const;
    byte getCH() const;
    byte getDL() const;
    byte getDH() const;

    void setA(word w);
    void setB(word w);
    void setC(word w);
    void setD(word w);
    void setX(word w);
    void setSP(word w);
    void setIP(word w);
    void setFL(word w);

    void setAL(byte b);
    void setAH(byte b);
    void setBL(byte b);
    void setBH(byte b);
    void setCL(byte b);
    void setCH(byte b);
    void setDL(byte b);
    void setDH(byte b);

    void push16(word w);
    word pop16();

    void setShutdown(bool f, int exitCode = 0);

    enum { NREGS = 8 }; // number of registers

    // Implementation
private:
    word regs[NREGS]; // registers
    bool m_shutdown; // shut down flag
    int m_exitCode; // exit code
};

/////////////////////////////////////////////////////////////////////////////

#endif  // __CPU_H__
