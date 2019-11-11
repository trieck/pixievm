/////////////////////////////////////////////////////////////////////////////
//
// MAIN.CPP : Application entry point
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Assembler.h"
#include "Exception.h"

ANON_BEGIN
void usage()
{
    cerr << "usage: pxasm source-file [outfile]" << endl;
    exit(EXIT_FAILURE);
}

ANON_END

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    if (argc < 2)
        usage();

    Assembler assembler;

    int nret;

    try{
        if (argc == 3){
            nret = assembler.assemble(argv[1], argv[2]);
        } else{
            nret = assembler.assemble(argv[1]);
        }
    } catch (const Exception& e){
        cerr << e.getDescription() << endl;
        exit(EXIT_FAILURE);
    }

    return nret;
}
