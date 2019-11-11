/////////////////////////////////////////////////////////////////////////////
//
// SYMBOLTABLE.CPP : Symbol table
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "SymbolTable.h"
#include "PixieVM.h"
#include "Parser.hpp"
#include "exception.h"
#include <boost/format.hpp>

#define ISLIST(s) ((s)->type == SymbolType::ST_LIST)

extern int yylineno;

using boost::format;

/////////////////////////////////////////////////////////////////////////////
SymbolTable::SymbolTable()
{
    // Group #1 instructions
    iinsert("ADC", I1, &INS_ADC);
    iinsert("AND", I1, &INS_AND);
    iinsert("BIT", I1, &INS_BIT);
    iinsert("CMP", I1, &INS_CMP);
    iinsert("MOV", I1, &INS_MOV);
    iinsert("OR", I1, &INS_OR);
    iinsert("SBB", I1, &INS_SBB);
    iinsert("XOR", I1, &INS_XOR);

    // Group #2 instructions
    iinsert("DEC", I2, &INS_DEC);
    iinsert("INC", I2, &INS_INC);
    iinsert("ROL", I2, &INS_ROL);
    iinsert("ROR", I2, &INS_ROR);
    iinsert("SHL", I2, &INS_SHL);
    iinsert("SHR", I2, &INS_SHR);

    // Group #3 instructions
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

    // Group #4 instructions
    iinsert("CALL", I4, &INS_CALL);
    iinsert("JMP", I4, &INS_JMP);

    // Group #5 instructions
    iinsert("JCC", I5, &INS_JCC);
    iinsert("JCS", I5, &INS_JCS);
    iinsert("JMI", I5, &INS_JMI);
    iinsert("JNZ", I5, &INS_JNZ);
    iinsert("JPL", I5, &INS_JPL);
    iinsert("JVC", I5, &INS_JVC);
    iinsert("JVS", I5, &INS_JVS);
    iinsert("JZ", I5, &INS_JZ);

    // Group #6 instructions
    iinsert("POP", I6, &INS_POP);

    // Group #7 instructions
    iinsert("PUSH", I7, &INS_PUSH);

    // 8-bit registers
    rinsert("AL", R8, REG8_AL);
    rinsert("AH", R8, REG8_AH);
    rinsert("BL", R8, REG8_BL);
    rinsert("BH", R8, REG8_BH);
    rinsert("CL", R8, REG8_CL);
    rinsert("CH", R8, REG8_CH);
    rinsert("DL", R8, REG8_DL);
    rinsert("DH", R8, REG8_DH);

    // 16-bit registers
    rinsert("A", R16, REG16_A);
    rinsert("B", R16, REG16_B);
    rinsert("C", R16, REG16_C);
    rinsert("D", R16, REG16_D);
    rinsert("X", R16, REG16_X);
    rinsert("SP", R16, REG16_SP);

    // Identifiers
    idinsert("BYTE", BYTE_PTR);
    idinsert("WORD", WORD_PTR);
    idinsert("DUP", DUP);

    // pseudo operations
    idinsert(".ORG", DECL_ORG);
    idinsert(".BYTE", DECL_BYTE);
    idinsert(".WORD", DECL_WORD);
    idinsert(".TEXT", DECL_TEXT);
}

/////////////////////////////////////////////////////////////////////////////
SymbolTable::~SymbolTable()
{
    symmap::const_iterator it = table.begin();
    for (; it != table.end(); ++it){
        delete (*it).second;
    }
}

/////////////////////////////////////////////////////////////////////////////
void SymbolTable::iinsert(const string& s, uint32_t t, const Instr* i)
{
    // instruction

    auto sym = new Symbol;
    sym->name = s;
    sym->type = SymbolType::ST_INSTRUCTION;
    sym->sub = t;
    sym->instr = i;
    table[s] = sym;
}

/////////////////////////////////////////////////////////////////////////////
void SymbolTable::rinsert(const string& s, uint32_t t, byte r)
{
    // register

    auto sym = new Symbol;
    sym->name = s;
    sym->type = SymbolType::ST_REG;
    sym->sub = t;
    sym->val8 = r;
    table[s] = sym;
}

/////////////////////////////////////////////////////////////////////////////
void SymbolTable::idinsert(const string& s, uint32_t id)
{
    // identifier

    auto sym = new Symbol;
    sym->name = s;
    sym->type = SymbolType::ST_ID;
    sym->sub = id;
    table[s] = sym;
}

/////////////////////////////////////////////////////////////////////////////
LPSYMBOL SymbolTable::install(const string& s)
{
    // undefined symbol

    LPSYMBOL sym;
    if ((sym = lookup(s)) == nullptr){
        sym = new Symbol;
        sym->name = s;
        sym->type = SymbolType::ST_UNDEF;
        sym->sub = 0;
        sym->lineno = yylineno;
        table[s] = sym;
    }

    return sym;
}

/////////////////////////////////////////////////////////////////////////////
LPSYMBOL SymbolTable::installs(const string& s)
{
    // string literal
    static auto counter = 0;

    auto sym = new Symbol;
    sym->name = (format("STRING:0x%08X") % counter++).str();

    sym->sval = s;
    sym->type = SymbolType::ST_STRING;
    sym->sub = 0;
    sym->lineno = yylineno;
    table[sym->name] = sym;

    return sym;
}

/////////////////////////////////////////////////////////////////////////////
LPSYMBOL SymbolTable::installw(SymbolType type, uint32_t sub, word value)
{
    // numeric
    static auto counter = 0;

    auto sym = new Symbol;
    sym->name = (format("NUMERIC:0x%08X") % counter++).str();
    sym->type = type;
    sym->sub = sub;
    sym->lineno = yylineno;
    sym->val16 = value;
    table[sym->name] = sym;

    return sym;
}

/////////////////////////////////////////////////////////////////////////////
LPSYMBOL SymbolTable::installo(uint32_t op, uint32_t sub, Symbol* args)
{
    // operator

    auto sym = new Symbol;

    sym->name = opname(op);
    sym->type = SymbolType::ST_OP;
    sym->sub = sub;
    sym->lineno = yylineno;
    sym->args = args; // argument list
    sym->opcode = op; // operator code
    table[sym->name] = sym;

    return sym;
}

/////////////////////////////////////////////////////////////////////////////
LPSYMBOL SymbolTable::opeval(uint32_t opcode, uint32_t sub, LPSYMBOL args)
{
    // critical expression operator evaluation
    switch (opcode){
    case PLUS:
        return plus(sub, args);
    case MINUS:
        return minus(sub, args);
    case MULT:
        return mult(sub, args);
    case DIV:
        return div(sub, args);
    default:
        throw Exception("unrecognized opcode %d.", opcode);
    };

    return nullptr;
}

/////////////////////////////////////////////////////////////////////////////
LPSYMBOL SymbolTable::plus(uint32_t sub, LPSYMBOL args)
{
    ASSERT(args->type == SymbolType::ST_LIST);
    ASSERT(args->vsyms.size() == 2);
    ASSERT(args->vsyms[0]->type == SymbolType::ST_CONST || args->vsyms[0]->type == SymbolType::ST_ID);
    ASSERT(args->vsyms[1]->type == SymbolType::ST_CONST || args->vsyms[1]->type == SymbolType::ST_ID);

    const word value = args->vsyms[0]->val16 + args->vsyms[1]->val16;

    return installw(SymbolType::ST_CONST, sub, value);
}

/////////////////////////////////////////////////////////////////////////////
LPSYMBOL SymbolTable::minus(uint32_t sub, LPSYMBOL args)
{
    ASSERT(args->type == SymbolType::ST_LIST);
    ASSERT(args->vsyms.size() == 2);
    ASSERT(args->vsyms[0]->type == SymbolType::ST_CONST || args->vsyms[0]->type == SymbolType::ST_ID);
    ASSERT(args->vsyms[1]->type == SymbolType::ST_CONST || args->vsyms[1]->type == SymbolType::ST_ID);

    const word value = args->vsyms[0]->val16 - args->vsyms[1]->val16;

    return installw(SymbolType::ST_CONST, sub, value);
}

/////////////////////////////////////////////////////////////////////////////
LPSYMBOL SymbolTable::mult(uint32_t sub, LPSYMBOL args)
{
    ASSERT(args->type == SymbolType::ST_LIST);
    ASSERT(args->vsyms.size() == 2);
    ASSERT(args->vsyms[0]->type == SymbolType::ST_CONST || args->vsyms[0]->type == SymbolType::ST_ID);
    ASSERT(args->vsyms[1]->type == SymbolType::ST_CONST || args->vsyms[1]->type == SymbolType::ST_ID);

    const word value = args->vsyms[0]->val16 * args->vsyms[1]->val16;

    return installw(SymbolType::ST_CONST, sub, value);
}

/////////////////////////////////////////////////////////////////////////////
LPSYMBOL SymbolTable::div(uint32_t sub, LPSYMBOL args)
{
    ASSERT(args->type == SymbolType::ST_LIST);
    ASSERT(args->vsyms.size() == 2);
    ASSERT(args->vsyms[0]->type == SymbolType::ST_CONST || args->vsyms[0]->type == SymbolType::ST_ID);
    ASSERT(args->vsyms[1]->type == SymbolType::ST_CONST || args->vsyms[1]->type == SymbolType::ST_ID);

    const word value = args->vsyms[0]->val16 / args->vsyms[1]->val16;

    return installw(SymbolType::ST_CONST, sub, value);
}

/////////////////////////////////////////////////////////////////////////////
LPSYMBOL SymbolTable::lookup(const string& s) const
{
    const auto it = table.find(s);
    if (it == table.end())
        return nullptr;

    return (*it).second;
}

/////////////////////////////////////////////////////////////////////////////
LPSYMBOL SymbolTable::mklist(LPSYMBOL s1, LPSYMBOL s2)
{
    LPSYMBOL list = nullptr;
    static auto counter = 0;

    if (!ISLIST(s1) && !ISLIST(s2)){
        // make a new list
        list = new Symbol;
        list->name = (format("LIST:0x%08X") % counter++).str();
        list->type = SymbolType::ST_LIST;
        list->lineno = yylineno;
        list->vsyms.push_back(s1);
        list->vsyms.push_back(s2);
        table[list->name] = list;
    } else if (ISLIST(s1) && !ISLIST(s2)){
        // s1 is an existing list
        list = s1;
        list->vsyms.push_back(s2);
    } else if (!ISLIST(s1) && ISLIST(s2)){
        // s2 is an existing list
        list = s2;
        list->vsyms.push_back(s1);
    } else if (s1 != s2){
        // s1 and s2 are distinct existing lists
        list = s1; // copy list values from s2 to s1

        SymbolVec::const_iterator it = s2->vsyms.begin();
        for (; it != s2->vsyms.end(); it++){
            list->vsyms.push_back(*it);
        }
    } else{
        // existing list s1 == s2
        list = s1;
    }

    return list;
}

/////////////////////////////////////////////////////////////////////////////
string SymbolTable::opname(uint32_t opcode)
{
    string opname;

    static auto counter = 0;

    switch (opcode){
    case PLUS:
        opname = "+";
        break;
    case MINUS:
        opname = "-";
        break;
    case MULT:
        opname = "*";
        break;
    case DIV:
        opname = "/";
        break;
    case LO_BYTE:
        opname = "lobyte";
        break;
    case HI_BYTE:
        opname = "hibyte";
        break;
    default:
        opname = "unknown";
    }

    auto name = (format("OPERATOR(%s):0x%08X") % opname.c_str() % counter++).str();

    return name;
}
