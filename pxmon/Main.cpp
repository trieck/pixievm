/////////////////////////////////////////////////////////////////////////////
//
// MAIN.CPP : Application entry point
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "machine.h"
#include "exception.h"
#include "options.h"

////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    Options::options(argc, argv);

    Machine machine;

    try{
        machine.init();
        machine.run();
    } catch (const Exception& e){
        cerr << e.getDescription() << endl;
        return 1;
    }

    return 0;
}
