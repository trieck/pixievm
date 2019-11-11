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
#define ST_REG          (0)         /* cpu register */
#define ST_INSTRUCTION  (1 << 0)    /* machine instruction */
#define ST_ID           (1 << 1)    /* identifier */
#define ST_CONST        (1 << 2)    /* constant */
#define ST_TEMP         (1 << 3)    /* temporary */

/////////////////////////////////////////////////////////////////////////////
// Symbol struct
struct Symbol
{
    int type = 0;   /* symbol type */
    int sub = 0;    /* sub-type */
    string name;    /* symbol name */
    union
    {
        const Instr* instr{}; /* instruction */
        word val16; /* word value */
        byte val8; /* byte value */
    };
};

using SymbolPtr = std::shared_ptr<Symbol>;

/////////////////////////////////////////////////////////////////////////////
class SymbolTable
{
    // Construction / Destruction
public:
    SymbolTable();
    ~SymbolTable() = default;

    // Interface
    Symbol* installw(const string& s, int type, int sub, word w);
    Symbol* installb(const string& s, int type, int sub, byte b);
    Symbol* lookup(const string& s) const;
    void flushtmp();

    // Implementation
private:
    void iinsert(const string& s, int t, const Instr* i);
    void rinsert(const string& s, int t, byte r);
    void idinsert(const string& s, int id);

    using symmap = StringKeyMap<SymbolPtr>::Type;
    symmap table;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __SYMBOLTABLE_H__
