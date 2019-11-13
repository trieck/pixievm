/////////////////////////////////////////////////////////////////////////////
//
// MACHINE.CPP : Pixie Virtual Machine
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "CPU.H"
#include "interrupt.h"
#include "machine.h"
#include "memory.h"
#include "monitor.h"
#include "PixieVM.h"
#include <boost/format.hpp>
#include <sys/stat.h>

using boost::format;

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
    if (!ifs.is_open()) {
        throw std::exception((format("unable to open ROM image \"%s\".") % filename).str().c_str());
    }

    if (!Memory::instance().load(ifs, base, size)) {
        throw std::exception((format("unable to load ROM image \"%s\".") % filename).str().c_str());
    }

    ifs.close();
}

/////////////////////////////////////////////////////////////////////////////
void Machine::loadROM(const char* filename)
{
    // load rom with contained load address

    struct stat buf{};
    const auto n = stat(filename, &buf);
    if (n) {
        throw std::exception((format("unable to stat ROM image \"%s\".") % filename).str().c_str());
    }

    ifstream ifs;
    ifs.open(filename, ifstream::in | ifstream::binary);
    if (!ifs.is_open()) {
        throw std::exception((format("unable to open ROM image \"%s\".") % filename).str().c_str());
    }

    word start;
    ifs.read(reinterpret_cast<char*>(&start), sizeof(word));
    if (ifs.bad()) {
        throw std::exception((format("unable to read from ROM image \"%s\".") % filename).str().c_str());
    }

    if (!Memory::instance().load(ifs, start, buf.st_size - sizeof(word))) {
        throw std::exception((format("unable to load ROM image \"%s\".") % filename).str().c_str());
    }
}

/////////////////////////////////////////////////////////////////////////////
int Machine::run()
{
    auto& mon = Monitor::instance();

    // setup global interrupt
    g_interrupt.setMonitor(&mon);
    g_interrupt.setTrap(&mon);
    g_interrupt.clearPending(IK_TRAP);

    // run!
    return CPU::instance().run();
}
