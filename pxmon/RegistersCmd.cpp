/////////////////////////////////////////////////////////////////////////////
//
// REGISTERSCMD.CPP : Monitor registers command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "RegistersCmd.h"
#include <CPU.H>

/////////////////////////////////////////////////////////////////////////////
void RegistersCmd::exec(const stringvec& v)
{
    auto& cpu = CPU::instance();

    char sr[9]{};
    sr[0] = cpu.getNeg() ? '1' : '0';
    sr[1] = cpu.getOverflow() ? '1' : '0';
    sr[2] = '0'; /* unused */
    sr[3] = '0'; /* unused */
    sr[4] = cpu.getBreak() ? '1' : '0';
    sr[5] = cpu.getIntDisable() ? '1' : '0';
    sr[6] = cpu.getZero() ? '1' : '0';
    sr[7] = cpu.getCarry() ? '1' : '0';
    sr[8] = '\0';

    printf(" A: $%.4hX"
           "  B: $%.4hX"
           "  C: $%.4hX"
           "  D: $%.4hX\n"
           " X: $%.4hX"
           " SP: $%.4hX"
           " IP: $%.4hX"
           " FL: %s (NV--BIZC)\n",
           cpu.getA(), cpu.getB(), cpu.getC(), cpu.getD(),
           cpu.getX(), cpu.getSP(), cpu.getIP(), &sr[0]);
}
