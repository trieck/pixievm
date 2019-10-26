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
#include <sys/stat.h>

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
    loadROM("kernel.rom");
}

/////////////////////////////////////////////////////////////////////////////
void Machine::loadROM(const char* filename, word base, word size)
{
    ifstream ifs;
    ifs.open(filename, ifstream::in | ifstream::binary);
    if (!ifs.is_open()){
        throw Exception("unable to open ROM image \"%s\".", filename);
    }

    if (!memory->load(ifs, base, size)){
        throw Exception("unable to load ROM image \"%s\".", filename);
    }

    ifs.close();
}

/////////////////////////////////////////////////////////////////////////////
void Machine::loadROM(const char* filename)
{
    // load rom with contained load address

    struct _stat buf;
    int n = stat(filename, (struct stat*)&buf);
    if (n){
        throw Exception("unable to stat ROM image \"%s\".", filename);
    }

    ifstream ifs;
    ifs.open(filename, ifstream::in | ifstream::binary);
    if (!ifs.is_open()){
        throw Exception("unable to open ROM image \"%s\".", filename);
    }

    word start;
    ifs.read((char*)&start, sizeof(word));
    if (ifs.bad()){
        throw Exception("unable to read from ROM image \"%s\".", filename);
    }

    if (!memory->load(ifs, start, buf.st_size - sizeof(word))){
        throw Exception("unable to load ROM image \"%s\".", filename);
    }
}

/////////////////////////////////////////////////////////////////////////////
void Machine::run()
{
    Monitor* mon = Monitor::getInstance();

    // setup global interrupt
    g_interrupt.setMonitor(mon);
    g_interrupt.setTrap(mon);
    g_interrupt.clearPending(IK_TRAP);

    // run!
    cpu->run();
}
