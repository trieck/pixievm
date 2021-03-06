/////////////////////////////////////////////////////////////////////////////
//
// PROGRAM.H : expression machine program
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "SymbolTable.h"

enum DatumType
{
    DT_UNDEF,
    DT_CONST,
    DT_SYM,
    DT_INSTR,
};

class Machine;
struct Datum;

typedef Datum (Machine::*Instruction)(void);

/////////////////////////////////////////////////////////////////////////////
struct Datum
{
    Datum() : type(DT_UNDEF), instr(nullptr)
    {
    }

    DatumType type;

    union
    {
        word value;
        LPSYMBOL sym;
        Instruction instr;
    };
};

/////////////////////////////////////////////////////////////////////////////
class Program
{
public:
    Program();
    ~Program() = default;

    void init();
    void pushop(uint32_t opcode);
    void push(word w);
    void push(Instruction i);
    void push(LPSYMBOL s);
    void push(const Datum& d);

    operator const Datum*() const;
private:
    enum { NPROG = 65536 };

    Datum m_memory[NPROG];
    Datum* m_pmem;
};

/////////////////////////////////////////////////////////////////////////////
inline Program::operator const Datum*() const
{
    return &m_memory[0];
}

#endif // __PROGRAM_H__
