
#pragma once

#include "Memory.h"
#include "cominit.h"

/////////////////////////////////////////////////////////////////////////////
class PxEmulator
{
	// Construction / Destruction
public:
	PxEmulator();
	~PxEmulator();

	// Interface
	void init();
	int run();

	// Implementation
private:
	void loadROM(const char *filename, word base, word size);
	Memory* memory;		// pointer to memory
	COMInitializer coinit;
};


