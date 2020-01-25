/////////////////////////////////////////////////////////////////////////////
//
// CPU.H : Pixie VM CPU
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __CPU_H__
#define __CPU_H__

#include "Singleton.h"
#include "memory.h"
#include "Alarm.h"

constexpr auto RESET_VECTOR = 0xFFFC;
constexpr auto IRQ_VECTOR = 0xFFFE;

/////////////////////////////////////////////////////////////////////////////
class CPU : public Singleton<CPU>
{
    // Construction / Destruction
    CPU();
    friend class Singleton<CPU>;

public:
    ~CPU();

    void clear();
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
    bool getCarry() const;
    bool getZero() const;
    bool getIntDisable() const;
    bool getBreak() const;
    bool getOverflow() const;
    bool getNeg() const;

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
    Memory& m_memory;   // memory
    Alarms& m_alarms;   // alarms
    word regs[NREGS];   // registers
    bool m_shutdown;    // shut down flag
    int m_exitCode;     // exit code
};

/////////////////////////////////////////////////////////////////////////////

#endif  // __CPU_H__
