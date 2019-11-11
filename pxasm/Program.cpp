/////////////////////////////////////////////////////////////////////////////
//
// PROGRAM.CPP : expression machine program
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Machine.h"
#include "Program.h"
#include <boost/format.hpp>

using boost::format;

/////////////////////////////////////////////////////////////////////////////
Program::Program() : m_pmem(m_memory)
{
    memset(m_memory, 0, sizeof(Datum) * NPROG);
}

/////////////////////////////////////////////////////////////////////////////
void Program::init()
{
    m_pmem = &m_memory[0];
}

/////////////////////////////////////////////////////////////////////////////
void Program::pushop(uint32_t opcode)
{
    Instruction i;

    if ((i = Machine::lookup(opcode)) == NULL) {
        std::exception((format("unrecognized opcode %d.") % opcode).str().c_str());
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
        throw std::exception("memory overflow.");

    *m_pmem++ = d;
}
