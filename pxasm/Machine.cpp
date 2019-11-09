/////////////////////////////////////////////////////////////////////////////
//
// MACHINE.CPP : simple runtime machine
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "machine.h"
#include "SymbolTable.h"
#include "Parser.hpp"
#include "program.h"
#include "code.h"
#include "exception.h"

extern Code code;

/////////////////////////////////////////////////////////////////////////////
Machine::Machine() : m_pc(nullptr)
{
    m_instr[PLUS] = &Machine::plus;
    m_instr[MINUS] = &Machine::minus;
    m_instr[MULT] = &Machine::mult;
    m_instr[DIV] = &Machine::div;
    m_instr[LO_BYTE] = &Machine::lobyte;
    m_instr[HI_BYTE] = &Machine::hibyte;
}

/////////////////////////////////////////////////////////////////////////////
Machine::~Machine()
{
}

/////////////////////////////////////////////////////////////////////////////
Instruction Machine::lookup(uint32_t opcode)
{
    auto& machine = Machine::instance();

    InstrMap::const_iterator it = machine.m_instr.find(opcode);
    if (it == machine.m_instr.end())
        return nullptr;

    return (*it).second;
}

/////////////////////////////////////////////////////////////////////////////
void Machine::exec(const Program& program)
{
    m_pc = program;

    while (m_pc->type != DT_UNDEF){
        eval();
    }
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::eval()
{
    Datum d;
    switch (m_pc->type){
    case DT_UNDEF:
        return d;
    case DT_SYM:
        return evalsym(m_pc++->sym);
    case DT_INSTR:
        return (this->*m_pc++->instr)();
    default:
        return *m_pc++;
    };
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::evalsym(LPSYMBOL s)
{
    Datum d;
    Instruction i;

    switch (s->type){
    case SymbolType::ST_UNDEF:
        throw Exception("identifier \"%s\" was undefined near line %d.",
                        s->name.c_str(), s->lineno);
    case SymbolType::ST_OP:
        if ((i = lookup(s->opcode)) == NULL){
            throw Exception("unrecognized opcode %d.", s->opcode);
        }
        return (this->*i)();
    default:
        d.type = DT_CONST;
        d.value = s->val16;
        return d;
    };
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::plus()
{
    const auto d1 = eval();
    const auto d2 = eval();

    Datum result;
    result.type = DT_CONST;
    result.value = d1.value + d2.value;

    return result;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::minus()
{
    const auto d1 = eval();
    const auto d2 = eval();

    Datum result;
    result.type = DT_CONST;
    result.value = d1.value - d2.value;

    return result;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::mult()
{
    const auto d1 = eval();
    const auto d2 = eval();

    Datum result;
    result.type = DT_CONST;
    result.value = d1.value * d2.value;

    return result;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::div()
{
    const auto d1 = eval();
    const auto d2 = eval();

    Datum result;
    result.type = DT_CONST;
    result.value = d1.value / d2.value;

    return result;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::hibyte()
{
    const auto arg = eval();

    Datum result;
    result.type = DT_CONST;
    result.value = HIBYTE(arg.value);

    return result;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::lobyte()
{
    const auto arg = eval();

    Datum result;
    result.type = DT_CONST;
    result.value = LOBYTE(arg.value);

    return result;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::fixup()
{
    const auto ctxt = eval();
    const auto loc = eval();
    const auto target = eval();

    if (ctxt.value == IM8){
        // relative branch fix-up
        const int16_t diff = target.value - (loc.value + 1);

        if (diff < int8_t(0x80)){
            // backward branch
            throw Exception("backward branch out of range.");
        } else if (diff > 0x7F){
            // forward branch
            throw Exception("forward branch out of range.");
        }
        code.putByteAt(loc.value, byte(diff));
    } else{
        // forward reference
        code.putWordAt(loc.value, target.value);
    }

    return target;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::memstore()
{
    const auto ctxt = eval();
    const auto loc = eval();
    const auto value = eval();

    if (ctxt.value == IM16){
        code.putWordAt(loc.value, value.value);
    } else{
        code.putByteAt(loc.value, byte(value.value));
    }

    return value;
}
