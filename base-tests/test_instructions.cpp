#include "pch.h"

#include "common.h"
#include "Memory.h"
#include <CPU.H>
#include <interrupt.h>
#include "PixieVM.h"
#include "Modes.h"
#include "Instructions.h"

#define ASSERT_CARRY_CLEAR(cpu) \
    ASSERT_FALSE((cpu).getCarry())

#define ASSERT_CARRY_SET(cpu) \
    ASSERT_TRUE((cpu).getCarry())

#define ASSERT_ZERO_CLEAR(cpu) \
    ASSERT_FALSE((cpu).getZero())

#define ASSERT_ZERO_SET(cpu) \
    ASSERT_TRUE((cpu).getZero())

#define ASSERT_OVERFLOW_CLEAR(cpu) \
    ASSERT_FALSE((cpu).getOverflow())

#define ASSERT_OVERFLOW_SET(cpu) \
    ASSERT_TRUE((cpu).getOverflow())

struct InstructionTest : testing::Test, TrapHandler
{
    enum { PROGRAM_START = 0x8000 };

    CPU& cpu_;
    Memory& memory_;
    word startip_, currentip_;       // start, current CPU instruction pointer
    word address_;  // current address for code generation

    InstructionTest() : cpu_(CPU::instance()),
                        memory_(Memory::instance()), startip_(PROGRAM_START), currentip_(PROGRAM_START),
                        address_(PROGRAM_START)
    {
    }

    void SetUp() override
    {
        startip_ = currentip_ = address_ = PROGRAM_START;
        memory_.storeWord(RESET_VECTOR, PROGRAM_START);

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

TEST_F(InstructionTest, TEST_ADC_RR8_0)
{
    // adc al, ah
    memory_.store(address_++, OPCODE(&INS_ADC, AM_RR8));
    memory_.store(address_++, MAKEREG(REG8_AL, REG8_AH));

    cpu_.setAL(0x00);
    cpu_.setAH(0xFE);

    cpu_.run(); // go!

    ASSERT_EQ(startip_ + 2, cpu_.getIP());
    ASSERT_EQ(cpu_.getAL(), 0xFE);
    ASSERT_EQ(cpu_.getAH(), 0xFE);

    ASSERT_CARRY_CLEAR(cpu_);
    ASSERT_ZERO_CLEAR(cpu_);
    ASSERT_OVERFLOW_CLEAR(cpu_);
}

TEST_F(InstructionTest, TEST_ADC_RR8_1)
{
    // adc al, ah -- set carry, zero

    memory_.store(address_++, OPCODE(&INS_ADC, AM_RR8));
    memory_.store(address_++, MAKEREG(REG8_AL, REG8_AH));

    cpu_.setAL(0x02);
    cpu_.setAH(0xFE);

    cpu_.run(); // go!

    ASSERT_EQ(startip_ + 2, cpu_.getIP());
    ASSERT_EQ(cpu_.getAL(), 0x00);
    ASSERT_EQ(cpu_.getAH(), 0xFE);

    ASSERT_CARRY_SET(cpu_);
    ASSERT_ZERO_SET(cpu_);
    ASSERT_OVERFLOW_CLEAR(cpu_);
}

TEST_F(InstructionTest, TEST_ADC_RR8_2)
{
    // adc al, ah -- set overflow
    memory_.store(address_++, OPCODE(&INS_ADC, AM_RR8));
    memory_.store(address_++, MAKEREG(REG8_AL, REG8_AH));

    cpu_.setAL(0x50);
    cpu_.setAH(0x50);

    cpu_.run(); // go!

    ASSERT_EQ(startip_ + 2, cpu_.getIP());
    ASSERT_EQ(cpu_.getAL(), 0xA0);
    ASSERT_EQ(cpu_.getAH(), 0x50);

    ASSERT_CARRY_CLEAR(cpu_);
    ASSERT_ZERO_CLEAR(cpu_);
    ASSERT_OVERFLOW_SET(cpu_);
}

TEST_F(InstructionTest, TEST_ADC_RI8_0)
{
    // adc al, $01

    memory_.store(address_++, OPCODE(&INS_ADC, AM_RI8));
    memory_.store(address_++, REG8_AL);
    memory_.store(address_++, 0xFE);

    cpu_.setAL(0x1);

    cpu_.run(); // go!

    ASSERT_EQ(startip_ + 3, cpu_.getIP());
    ASSERT_EQ(cpu_.getAL(), 0xFF);
    ASSERT_EQ(cpu_.getAH(), 0x00);

    ASSERT_CARRY_CLEAR(cpu_);
    ASSERT_ZERO_CLEAR(cpu_);
    ASSERT_OVERFLOW_CLEAR(cpu_);
}