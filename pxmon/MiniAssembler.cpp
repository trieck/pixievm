/////////////////////////////////////////////////////////////////////////////
//
// MINIASSEMBLER.CPP : Mini Assembler
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "SymbolTable.h"
#include "MiniAssembler.h"
#include "Parser.hpp"
#include "CPU.H"

extern void yyrestart(FILE*);
extern FILE* yyin;
extern SymbolTable table;

struct yy_buffer_state;
typedef yy_buffer_state* YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char* str);
extern void yy_switch_to_buffer(YY_BUFFER_STATE buffer);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

// address of assembly
word address = 0x0000;

/////////////////////////////////////////////////////////////////////////////
MiniAssembler::MiniAssembler() : init(false)
{
}

/////////////////////////////////////////////////////////////////////////////
void MiniAssembler::prompt()
{
    fprintf(stdout, "$%.4hx: ", address);
}

/////////////////////////////////////////////////////////////////////////////
void MiniAssembler::assemble(word* start)
{
    initialize(start);

    for (;;) {
        prompt();
        if (!tryParse())
            break;
    }
}

/////////////////////////////////////////////////////////////////////////////
bool MiniAssembler::assemble(word* start, const char* str)
{
    initialize(start);

    const auto buffer = yy_scan_string(str);
    yy_switch_to_buffer(buffer);

    const auto result = tryParse();

    yy_delete_buffer(buffer);

    yyrestart(yyin);

    return result;
}

/////////////////////////////////////////////////////////////////////////////
void MiniAssembler::initialize(const word* start)
{
    if (start) {
        // start addres
        address = *start;
        init = true;
    } else if (!init) {
        // not entered
        address = CPU::instance().getIP();
        init = true;
    }
}

/////////////////////////////////////////////////////////////////////////////
bool MiniAssembler::tryParse()
{
    try {
        if (parse() == 0)
            return true;
    } catch (const std::exception& e) {
        yyrestart(yyin);
        cerr << e.what() << endl;
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////////
int MiniAssembler::parse()
{
    const auto nret = yyparse();
    table.flushtmp();
    return nret;
}
