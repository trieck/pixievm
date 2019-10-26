/////////////////////////////////////////////////////////////////////////////
//
// PROGRAM.CPP : expression machine program
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Program.h"
#include "Machine.h"
#include "Exception.h"

/////////////////////////////////////////////////////////////////////////////
Program::Program() : m_pmem(m_memory)
{
    memset(m_memory, 0, sizeof(Datum) * NPROG);
}

/////////////////////////////////////////////////////////////////////////////
Program::~Program()
{
}

/////////////////////////////////////////////////////////////////////////////
void Program::init()
{
    m_pmem = m_memory;
}

/////////////////////////////////////////////////////////////////////////////
void Program::pushop(uint32_t opcode)
{
    Instruction i;

    if ((i = Machine::lookup(opcode)) == NULL){
        throw Exception("unrecognized opcode %d.", opcode);
    }

    push(i);
}

/////////////////////////////////////////////////////////////////////////////
void Program::push(word w)
{
    Datum d;
    d.type = DT_CONST;
    d.value = w;
    push(d);
}

/////////////////////////////////////////////////////////////////////////////
void Program::push(Instruction i)
{
    Datum d;
    d.type = DT_INSTR;
    d.instr = i;
    push(d);
}

/////////////////////////////////////////////////////////////////////////////
void Program::push(LPSYMBOL s)
{
    Datum d;
    d.type = DT_SYM;
    d.sym = s;
    push(d);
}

/////////////////////////////////////////////////////////////////////////////
void Program::push(const Datum& d)
{
    if (m_pmem >= &m_memory[NPROG])
        throw Exception("memory overflow.");

    *m_pmem++ = d;
}
