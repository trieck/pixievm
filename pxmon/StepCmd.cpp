/////////////////////////////////////////////////////////////////////////////
//
// STEPCMD.CPP : Monitor step command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "StepCmd.h"
#include "CPU.h"
#include "Interrupt.h"

/////////////////////////////////////////////////////////////////////////////
void StepCmd::exec(const stringvec& v)
{
    auto& cpu = CPU::instance();

    auto ip = cpu.getIP();
    if (!v.empty()){
        const auto n = sscanf(v[0].c_str(), "%hx", &ip);
        if (n != 1){
            cerr << "? t [address]" << endl;
            return;
        }

        // set instruction pointer
        cpu.setIP(ip);
    }

    auto& mon = Monitor::instance();
    mon.disassemble(ip);

    g_interrupt.setPending(IK_TRAP);
    mon.setExit(true);
}
