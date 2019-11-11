/////////////////////////////////////////////////////////////////////////////
//
// MAIN.CPP : Application entry point
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "machine.h"
#include "options.h"

////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    Options::options(argc, argv);

    Machine machine;

    auto ret = 0;

    try {
        machine.init();
        ret = machine.run();
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return ret;
}
