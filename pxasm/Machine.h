/////////////////////////////////////////////////////////////////////////////
//
// MACHINE.H : simple runtime machine
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MACHINE_H__
#define __MACHINE_H__

#include "program.h"
#include "Singleton.h"

/////////////////////////////////////////////////////////////////////////////
class Machine : public Singleton<Machine>
{
    // Construction / destruction
    Machine();
    friend class Singleton<Machine>;

public:
    ~Machine() = default;

    // Interface
    void exec(const Program& program);
    static Instruction lookup(uint32_t opcode);

    // instructions
    Datum plus();
    Datum minus();
    Datum mult();
    Datum div();
    Datum hibyte();
    Datum lobyte();
    Datum fixup();
    Datum memstore();

    // Implementation
private:
    Datum eval();
    Datum evalsym(LPSYMBOL s);

    typedef unordered_map<uint32_t, Instruction> InstrMap;

    InstrMap m_instr;   // instruction map
    const Datum* m_pc;  // program counter
};

#endif // __MACHINE_H__
