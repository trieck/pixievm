/////////////////////////////////////////////////////////////////////////////
//
// MACHINE.CPP : Pixie Virtual Machine
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Memory.h"
#include "Trap.h"
#include "Handler.h"
#include "Interrupt.h"
#include "CPU.h"
#include "Monitor.h"
#include "Machine.h"
#include "Exception.h"
#include "Opcodes.h"

#define CHARGEN_BASE (0xC000)
#define CHARGEN_SIZE (0x800)

/////////////////////////////////////////////////////////////////////////////
Machine::Machine()
{
	memory = Memory::getInstance();
	cpu = CPU::getInstance();
}

/////////////////////////////////////////////////////////////////////////////
void Machine::init()
{
	loadROM("chargen.rom", CHARGEN_BASE, CHARGEN_SIZE);
}

/////////////////////////////////////////////////////////////////////////////
void Machine::loadROM(const char *filename, word base, word size)
{
	ifstream ifs;
	ifs.open(filename, ifstream::in | ifstream::binary);
	if (!ifs.is_open()) {
		throw Exception("unable to open ROM image \"%s\".", filename);
	}

	if (!memory->load(ifs, base, size)) {
		throw Exception("unable to load ROM image \"%s\".", filename);
	}

	ifs.close();
}

/////////////////////////////////////////////////////////////////////////////
void Machine::run()
{
	// setup global interrupt
	g_interrupt.setMonitor(&monitor);
	g_interrupt.setTrap(&monitor, NULL);
	g_interrupt.clearPending(IK_TRAP);

	cpu->run();
}

