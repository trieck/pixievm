/////////////////////////////////////////////////////////////////////////////
//
// STEPUNTILCMD.CPP : Step until return command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "StepUntilCmd.h"
#include "CPU.H"
#include "memory.h"
#include "interrupt.h"
#include "Opcodes.h"

/////////////////////////////////////////////////////////////////////////////
void StepUntilCmd::exec(const stringvec& v)
{
    auto& cpu = CPU::instance();

    // set the stack pointer to a sane value if zero
    word sp;
    if ((sp = cpu.getSP()) == 0) {
        cpu.setSP(0x1FF);
    }

    // push the current value of IP onto the stack
    word ip = cpu.getIP();
    cpu.push16(ip);

    if (!v.empty()) {
        const auto n = sscanf(v[0].c_str(), "%hx", &ip);
        if (n != 1) {
            cerr << "? u [address]" << endl;
            return;
        }

        // set instruction pointer
        cpu.setIP(ip);
    }

    g_interrupt.setTrap(this, reinterpret_cast<void*>(ip));

    Monitor::instance().setExit(true);
}

/////////////////////////////////////////////////////////////////////////////
void StepUntilCmd::trap(void* data)
{
    auto& mon = Monitor::instance();
    auto& mem = Memory::instance();
    auto& cpu = CPU::instance();

    auto ip = word(size_t(data));

    // check whether the last instruction executed was RET
    // if so, break back into the monitor. Otherwise, keep stepping.

    const byte instruction = mem.fetch(ip);
    if (instruction == RET || mon.isRunning()) {
        g_interrupt.setMonitorBreak(&mon);
    } else {
        ip = cpu.getIP();
        g_interrupt.setTrap(this, reinterpret_cast<void*>(ip));
    }
}
