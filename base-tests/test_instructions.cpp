#include "pch.h"

#include "common.h"
#include "memory.h"
#include <CPU.H>
#include <interrupt.h>
#include "PixieVM.h"
#include "Modes.h"
#include "Instructions.h"

struct InstructionTest: testing::Test, TrapHandler
{
    enum { PROGRAM_START = 0x8000 };

    CPU& cpu_;
    Memory& memory_;
    word startip_, currentip_;       // start, current CPU instruction pointer
    word address_;  // current address for code generation

    InstructionTest() : cpu_(CPU::instance()),
    memory_(Memory::instance()), startip_(PROGRAM_START), currentip_(PROGRAM_START), address_(PROGRAM_START)
    {}

    void SetUp() override
    {
        startip_ = currentip_ = address_ = PROGRAM_START;
        cpu_.setIP(startip_);
        g_interrupt.setTrap(this, &currentip_);
    }

    void TearDown() override
    {
        cpu_.clear();
        memory_.reset();
        startip_ = currentip_ = address_ = 0;
    }

    void trap(void* pip) override
    {
        ASSERT_NE(pip, nullptr);

        const auto ip = *reinterpret_cast<word*>(pip);
        ASSERT_GE(ip, startip_);

        currentip_ = cpu_.getIP();
        ASSERT_GE(currentip_, ip);

        if (ip == currentip_) {    // keep going
            g_interrupt.setTrap(this, &currentip_);
        } else {
            cpu_.setShutdown(true);
        }
    }
};

TEST_F(InstructionTest, TEST_ADC_RR8)
{
    ASSERT_EQ(address_, PROGRAM_START);
    memory_.storeWord(RESET_VECTOR, PROGRAM_START);

    // mov al, ah
    memory_.store(address_++, OPCODE(&INS_ADC, AM_RR8));
    memory_.store(address_++, MAKEREG(REG8_AL, REG8_AH));

    cpu_.setAL(0x00);
    cpu_.setAH(0xFE);

    cpu_.run();

    ASSERT_EQ(startip_ + 2, cpu_.getIP());
    ASSERT_EQ(cpu_.getAL(), 0xFE);
    ASSERT_EQ(cpu_.getAH(), 0xFE);
}
