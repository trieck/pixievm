/////////////////////////////////////////////////////////////////////////////
//
// SYMBOLTABLE.CPP : Symbol table
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "SymbolTable.h"
#include "Parser.hpp"
#include "PixieVM.h"
#include "Instructions.h"

/////////////////////////////////////////////////////////////////////////////
SymbolTable::SymbolTable()
{
    /* Group #1 instructions */
    iinsert("ADC", I1, &INS_ADC);
    iinsert("AND", I1, &INS_AND);
    iinsert("BIT", I1, &INS_BIT);
    iinsert("CMP", I1, &INS_CMP);
    iinsert("MOV", I1, &INS_MOV);
    iinsert("OR", I1, &INS_OR);
    iinsert("SBB", I1, &INS_SBB);
    iinsert("XOR", I1, &INS_XOR);

    /* Group #2 instructions */
    iinsert("DEC", I2, &INS_DEC);
    iinsert("INC", I2, &INS_INC);
    iinsert("ROL", I2, &INS_ROL);
    iinsert("ROR", I2, &INS_ROR);
    iinsert("SHL", I2, &INS_SHL);
    iinsert("SHR", I2, &INS_SHR);

    /* Group #3 instructions */
    iinsert("BRK", I3, &INS_BRK);
    iinsert("CLC", I3, &INS_CLC);
    iinsert("CLI", I3, &INS_CLI);
    iinsert("DEX", I3, &INS_DEX);
    iinsert("INX", I3, &INS_INX);
    iinsert("NOP", I3, &INS_NOP);
    iinsert("RET", I3, &INS_RET);
    iinsert("RETI", I3, &INS_RETI);
    iinsert("SEC", I3, &INS_SEC);
    iinsert("SEI", I3, &INS_SEI);
    iinsert("POPF", I3, &INS_POPF);
    iinsert("PUSHF", I3, &INS_PUSHF);

    /* Group #4 instructions */
    iinsert("CALL", I4, &INS_CALL);
    iinsert("JMP", I4, &INS_JMP);

    /* Group #5 instructions */
    iinsert("JCC", I5, &INS_JCC);
    iinsert("JCS", I5, &INS_JCS);
    iinsert("JMI", I5, &INS_JMI);
    iinsert("JNZ", I5, &INS_JNZ);
    iinsert("JPL", I5, &INS_JPL);
    iinsert("JVC", I5, &INS_JVC);
    iinsert("JVS", I5, &INS_JVS);
    iinsert("JZ", I5, &INS_JZ);

    /* Group #6 instructions */
    iinsert("POP", I6, &INS_POP);

    /* Group #7 instructions */
    iinsert("PUSH", I7, &INS_PUSH);

    /* 8-bit registers */
    rinsert("AL", R8, REG8_AL);
    rinsert("AH", R8, REG8_AH);
    rinsert("BL", R8, REG8_BL);
    rinsert("BH", R8, REG8_BH);
    rinsert("CL", R8, REG8_CL);
    rinsert("CH", R8, REG8_CH);
    rinsert("DL", R8, REG8_DL);
    rinsert("DH", R8, REG8_DH);

    /* 16-bit registers */
    rinsert("A", R16, REG16_A);
    rinsert("B", R16, REG16_B);
    rinsert("C", R16, REG16_C);
    rinsert("D", R16, REG16_D);
    rinsert("X", R16, REG16_X);
    rinsert("SP", R16, REG16_SP);

    /* Identifiers */
    idinsert("BYTE", BYTE_PTR);
    idinsert("WORD", WORD_PTR);
}

/////////////////////////////////////////////////////////////////////////////
void SymbolTable::iinsert(const string& s, int t, const Instr* i)
{
    auto sym = std::make_shared<Symbol>();

    sym->name = s;
    sym->type = ST_INSTRUCTION;
    sym->sub = t;
    sym->instr = i;
    table[s] = sym;
}

/////////////////////////////////////////////////////////////////////////////
void SymbolTable::rinsert(const string& s, int t, byte r)
{
    auto sym = std::make_shared<Symbol>();
    sym->name = s;
    sym->type = ST_REG;
    sym->sub = t;
    sym->val8 = r;
    table[s] = sym;
}

/////////////////////////////////////////////////////////////////////////////
void SymbolTable::idinsert(const string& s, int id)
{
    auto sym = std::make_shared<Symbol>();
    sym->name = s;
    sym->type = ST_ID;
    sym->sub = id;
    table[s] = sym;
}

/////////////////////////////////////////////////////////////////////////////
Symbol* SymbolTable::installw(const string& s, int type, int sub, word w)
{
    auto* sym = lookup(s);
    if (sym == nullptr) {
        auto symPtr = std::make_shared<Symbol>();
        symPtr->name = s;
        symPtr->type = type | ST_TEMP;
        symPtr->sub = sub;
        symPtr->val16 = w;
        table[s] = symPtr;
        sym = symPtr.get();
    }
    return sym;
}

/////////////////////////////////////////////////////////////////////////////
Symbol* SymbolTable::installb(const string& s, int type, int sub, byte b)
{
    auto* sym = lookup(s);
    if (sym == nullptr) {
        auto symPtr = std::make_shared<Symbol>();
        symPtr->name = s;
        symPtr->type = type | ST_TEMP;
        symPtr->sub = sub;
        symPtr->val8 = b;
        table[s] = symPtr;
        sym = symPtr.get();
    }

    return sym;
}

/////////////////////////////////////////////////////////////////////////////
Symbol* SymbolTable::lookup(const string& s) const
{
    const auto it = table.find(s);
    if (it == table.end())
        return nullptr;

    return (*it).second.get();
}

/////////////////////////////////////////////////////////////////////////////
// flush temporary symbols
void SymbolTable::flushtmp()
{
    auto it = table.begin();
    for (; it != table.end(); ++it) {
        if ((*it).second->type & ST_TEMP) {
            table.erase(it);
            it = table.begin();
        }
    }
}
