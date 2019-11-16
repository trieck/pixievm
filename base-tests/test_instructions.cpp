#include "pch.h"

#include "common.h"
#include "memory.h"
#include <CPU.H>
#include <interrupt.h>
#include "Opcodes.h"
#include "PixieVM.h"
#include "Modes.h"
#include "Instructions.h"

struct InstructionTest: testing::Test, TrapHandler
{
    enum { PROGRAM_START = 0x8000 };

    CPU& cpu_;
    Memory& memory_;
    word ip_;       // current CPU instruction pointer
    word address_;  // current address for code generation

    InstructionTest() : cpu_(CPU::instance()), memory_(Memory::instance()), ip_(PROGRAM_START), address_(PROGRAM_START)
    {}

    void SetUp() override
    {
        cpu_.setIP(PROGRAM_START);
        g_interrupt.setTrap(this, reinterpret_cast<void*>(ip_));
    }

    void TearDown() override
    {
        cpu_.clear();
        memory_.reset();
        ip_ = address_ = 0;
    }

    void trap(void* pip) override
    {
        auto ip = reinterpret_cast<word>(pip);
        EXPECT_GE(ip, ip_);

        if (ip == ip_) {    // keep going
            ip = cpu_.getIP();
            g_interrupt.setTrap(this, reinterpret_cast<void*>(ip));
        } else {
            cpu_.setShutdown(true);
        }
    }
};

TEST_F(InstructionTest, TEST_ADC_RR8)
{
    EXPECT_EQ(address_, PROGRAM_START);

    memory_.storeWord(RESET_VECTOR, PROGRAM_START);

    memory_.store(address_++, OPCODE(&INS_ADC, AM_RR8));
    memory_.store(address_++, MAKEREG(REG8_AL, REG8_AH));

    cpu_.run();
}
