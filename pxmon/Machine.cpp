/////////////////////////////////////////////////////////////////////////////
//
// MACHINE.CPP : Pixie Virtual Machine
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Interrupt.h"
#include "Machine.h"
#include "Exception.h"
#include "Opcodes.h"
#include "Monitor.h"
#include "PixieVM.h"

/////////////////////////////////////////////////////////////////////////////
Machine::Machine()
{
	memory = Memory::getInstance();
	cpu = CPU::getInstance();
}

/////////////////////////////////////////////////////////////////////////////
Machine::~Machine()
{
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
	Monitor *mon = Monitor::getInstance();

	// setup global interrupt
	g_interrupt.setMonitor(mon);
	g_interrupt.setTrap(mon);
	g_interrupt.clearPending(IK_TRAP);

	// run!
	cpu->run();
}