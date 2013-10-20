/////////////////////////////////////////////////////////////////////////////
//
// MAIN.CPP : Application entry point
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Machine.h"
#include "Exception.h"
#include "Options.h"

////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	Options::options(argc, argv);

	Machine machine;

	try {
		machine.init();
		machine.run();
	} catch (const Exception & e) {
		cerr << e.getDescription() << endl;
		return 1;
	}

	return 0;
}