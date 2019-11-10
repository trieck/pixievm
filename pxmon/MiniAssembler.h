/////////////////////////////////////////////////////////////////////////////
//
// MINIASSEMBLER.H : Mini Assembler
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MINIASSEMBLER_H__
#define __MINIASSEMBLER_H__

/////////////////////////////////////////////////////////////////////////////
class MiniAssembler
{
    // Construction / Destruction
public:
    MiniAssembler();

    // Interface
    void assemble(word* start);
    bool assemble(word* start, const char* str);

    // Implementation
private:
    void initialize(const word* start);
    static bool tryParse();
    static int parse();
    static void prompt();

    bool init; // have we been entered ?
};

/////////////////////////////////////////////////////////////////////////////

#endif // __MINIASSEMBLER_H__
