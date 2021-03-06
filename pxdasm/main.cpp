/////////////////////////////////////////////////////////////////////////////
//
// MAIN.CPP : Application entry point
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Disassembler.h"

ANON_BEGIN
void usage()
{
    cerr << "usage: pxdasm object-file" << endl;
    exit(EXIT_FAILURE);
}

ANON_END

/////////////////////////////////////////////////////////////////////////////
int main(int argc, const char** argv)
{
    if (argc < 2)
        usage();

    Disassembler disassembler;

    try {
        disassembler.disassemble(argv[1]);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
