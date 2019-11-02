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
StepUntilCmd::StepUntilCmd(Monitor* mon) : Command(mon)
{
}

/////////////////////////////////////////////////////////////////////////////
StepUntilCmd::~StepUntilCmd()
= default;

/////////////////////////////////////////////////////////////////////////////
void StepUntilCmd::exec(const stringvec& v)
{
    CPU* cpu = CPU::getInstance();
    Memory* mem = Memory::getInstance();

    // set the stack pointer to a sane value if zero
    word sp;
    if ((sp = cpu->getSP()) == 0){
        cpu->setSP(0x1FF);
    }

    // push the current value of IP onto the stack
    word ip = cpu->getIP();
    cpu->push16(ip);

    if (v.size() > 0){
        const auto n = sscanf(v[0].c_str(), "%hx", &ip);
        if (n != 1){
            cerr << "? u [address]" << endl;
            return;
        }

        // set instruction pointer
        cpu->setIP(ip);
    }

    auto* mon = getMonitor();

    g_interrupt.setTrap(this, reinterpret_cast<void*>(ip));
    mon->setExit(true);
}

/////////////////////////////////////////////////////////////////////////////
void StepUntilCmd::trap(void* data)
{
    auto* mon = getMonitor();
    auto* mem = Memory::getInstance();
    auto* cpu = CPU::getInstance();

    auto ip = word(size_t(data));

    // check whether the last instruction executed was RET
    // if so, break back into the monitor. Otherwise, keep stepping.

    const byte instruction = mem->fetch(ip);
    if (instruction == RET || mon->isRunning()){
        g_interrupt.setMonitorBreak(mon);
    } else{
        ip = cpu->getIP();
        g_interrupt.setTrap(this, reinterpret_cast<void*>(ip));
    }
}
