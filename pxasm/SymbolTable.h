/////////////////////////////////////////////////////////////////////////////
//
// SYMBOLTABLE.H : Symbol table
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __SYMBOLTABLE_H__
#define __SYMBOLTABLE_H__

#include "Instructions.h"

/////////////////////////////////////////////////////////////////////////////
// Symbol type
enum class SymbolType
{
    ST_UNDEF = 0,   // undefined
    ST_REG,         // cpu register
    ST_INSTRUCTION, // CPU instruction
    ST_ID,          // identifier
    ST_CONST,       // numeric constant
    ST_STRING,      // string literal
    ST_OP,          // operator
    ST_LIST         // list of symbols
};

class Symbol;
using SymbolVec = vector<Symbol*>;

/////////////////////////////////////////////////////////////////////////////
// Symbol class
class Symbol
{
    friend class SymbolTable;

    Symbol() : type(SymbolType::ST_UNDEF), sub(0), lineno(0), instr(nullptr), args(0)
    {
    }

public:
    string name; // symbol name
    SymbolType type; // symbol type
    uint32_t sub; // sub-type
    uint32_t lineno; // line number where first seen
    union
    {
        const Instr* instr; // instruction
        uint32_t opcode{};  // operator code
        word val16;         // word value
        byte val8;          // byte value
    };

    string sval;            // string value
    Symbol* args;           // operator arguments
    SymbolVec vsyms;        // list values
};

typedef Symbol* LPSYMBOL;

/////////////////////////////////////////////////////////////////////////////
class SymbolTable
{
public:
    SymbolTable();
    ~SymbolTable();

    // Interface
    LPSYMBOL install(const string& s); // undefined
    LPSYMBOL installs(const string& s); // string literal
    LPSYMBOL installw(SymbolType type, uint32_t sub, word value); // numeric
    LPSYMBOL installo(uint32_t op, uint32_t sub, LPSYMBOL args); // operator
    LPSYMBOL lookup(const string& s) const;
    LPSYMBOL mklist(LPSYMBOL s1, LPSYMBOL s2);
    LPSYMBOL opeval(uint32_t opcode, uint32_t sub, LPSYMBOL args); // critical eval
    // Implementation
private:
    LPSYMBOL plus(uint32_t sub, LPSYMBOL args);
    LPSYMBOL minus(uint32_t sub, LPSYMBOL args);
    LPSYMBOL mult(uint32_t sub, LPSYMBOL args);
    LPSYMBOL div(uint32_t sub, LPSYMBOL args);
    void iinsert(const string& s, uint32_t t, const Instr* i);
    void rinsert(const string& s, uint32_t t, byte r);
    void idinsert(const string& s, uint32_t id);

    static string opname(uint32_t opcode);
    using symmap = StringKeyMap<LPSYMBOL>::Type;
    symmap table;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __SYMBOLTABLE_H__
