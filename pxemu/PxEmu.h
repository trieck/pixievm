
#pragma once

#include "Memory.h"

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
	void loadROM(const char* filename, word base, word size);
	void loadROM(const char* filename);
	Memory* memory;		// pointer to memory
};

