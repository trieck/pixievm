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
    word startip_, currentip_;  // start, current CPU instruction pointer
    word address_;              // current address for code generation

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

    ASSERT_CARRY_CLEAR(cpu_);
    ASSERT_ZERO_CLEAR(cpu_);
    ASSERT_OVERFLOW_CLEAR(cpu_);
}

TEST_F(InstructionTest, TEST_ADC_RI8_1)
{
    // adc al, $FE -- set carry, zero

    memory_.store(address_++, OPCODE(&INS_ADC, AM_RI8));
    memory_.store(address_++, REG8_AL);
    memory_.store(address_++, 0xFE);

    cpu_.setAL(0x2);

    cpu_.run(); // go!

    ASSERT_EQ(startip_ + 3, cpu_.getIP());
    ASSERT_EQ(cpu_.getAL(), 0x00);

    ASSERT_CARRY_SET(cpu_);
    ASSERT_ZERO_SET(cpu_);
    ASSERT_OVERFLOW_CLEAR(cpu_);
}

TEST_F(InstructionTest, TEST_ADC_RI8_2)
{
    // adc al, $50 -- set overflow

    memory_.store(address_++, OPCODE(&INS_ADC, AM_RI8));
    memory_.store(address_++, REG8_AL);
    memory_.store(address_++, 0x50);

    cpu_.setAL(0x50);

    cpu_.run(); // go!

    ASSERT_EQ(startip_ + 3, cpu_.getIP());
    ASSERT_EQ(cpu_.getAL(), 0xA0);

    ASSERT_CARRY_CLEAR(cpu_);
    ASSERT_ZERO_CLEAR(cpu_);
    ASSERT_OVERFLOW_SET(cpu_);
}

TEST_F(InstructionTest, TEST_ADC_RR16_0)
{
    // adc a, b
    memory_.store(address_++, OPCODE(&INS_ADC, AM_RR16));
    memory_.store(address_++, MAKEREG(REG16_A, REG16_B));

    cpu_.setA(0x00);
    cpu_.setB(0xFE);

    cpu_.run(); // go!

    ASSERT_EQ(startip_ + 2, cpu_.getIP());
    ASSERT_EQ(cpu_.getA(), 0xFE);
    ASSERT_EQ(cpu_.getB(), 0xFE);

    ASSERT_CARRY_CLEAR(cpu_);
    ASSERT_ZERO_CLEAR(cpu_);
    ASSERT_OVERFLOW_CLEAR(cpu_);
}

TEST_F(InstructionTest, TEST_ADC_RR16_1)
{
    // adc a, b -- set carry, zero
    memory_.store(address_++, OPCODE(&INS_ADC, AM_RR16));
    memory_.store(address_++, MAKEREG(REG16_A, REG16_B));

    cpu_.setA(0xFFFE);
    cpu_.setB(0x0002);

    cpu_.run(); // go!

    ASSERT_EQ(startip_ + 2, cpu_.getIP());
    ASSERT_EQ(cpu_.getA(), 0x0000);
    ASSERT_EQ(cpu_.getB(), 0x0002);

    ASSERT_CARRY_SET(cpu_);
    ASSERT_ZERO_SET(cpu_);
    ASSERT_OVERFLOW_CLEAR(cpu_);
}

TEST_F(InstructionTest, TEST_ADC_RR16_2)
{
    // adc a, b -- set overflow
    memory_.store(address_++, OPCODE(&INS_ADC, AM_RR16));
    memory_.store(address_++, MAKEREG(REG16_A, REG16_B));

    cpu_.setA(0x7FFF);
    cpu_.setB(0x7FFF);

    cpu_.run(); // go!

    ASSERT_EQ(startip_ + 2, cpu_.getIP());
    ASSERT_EQ(cpu_.getA(), 0xFFFE);
    ASSERT_EQ(cpu_.getB(), 0x7FFF);

    ASSERT_CARRY_CLEAR(cpu_);
    ASSERT_ZERO_CLEAR(cpu_);
    ASSERT_OVERFLOW_SET(cpu_);
}

TEST_F(InstructionTest, TEST_ADC_MR8_0)
{
    // adc [d+x], ah
    memory_.store(address_, OPCODE(&INS_ADC, AM_MR8));
    memory_.store(address_ + 1, MAKEOFFSETREG(REG16_D, REG8_AH));

    memory_.store(0x8101, 0x01);

    cpu_.setD(0x8100);
    cpu_.setX(0x0001);
    cpu_.setAH(0x80);

    cpu_.run(); // go!

    ASSERT_EQ(startip_ + 2, cpu_.getIP());

    ASSERT_EQ(memory_.fetch(0x8101), 0x81);

    ASSERT_CARRY_CLEAR(cpu_);
    ASSERT_ZERO_CLEAR(cpu_);
    ASSERT_OVERFLOW_CLEAR(cpu_);
}

TEST_F(InstructionTest, TEST_ADC_MR8_1)
{
    // adc [d+x], ah -- set carry, zero
    memory_.store(address_, OPCODE(&INS_ADC, AM_MR8));
    memory_.store(address_ + 1, MAKEOFFSETREG(REG16_D, REG8_AH));

    memory_.store(0x8101, 0x01);

    cpu_.setD(0x8100);
    cpu_.setX(0x0001);
    cpu_.setAH(0xFF);

    cpu_.run(); // go!

    ASSERT_EQ(startip_ + 2, cpu_.getIP());

    ASSERT_EQ(memory_.fetch(0x8101), 0x00);

    ASSERT_CARRY_SET(cpu_);
    ASSERT_ZERO_SET(cpu_);
    ASSERT_OVERFLOW_CLEAR(cpu_);
}

TEST_F(InstructionTest, TEST_ADC_MR8_2)
{
    // adc [d+x], ah -- set overflow
    memory_.store(address_, OPCODE(&INS_ADC, AM_MR8));
    memory_.store(address_ + 1, MAKEOFFSETREG(REG16_D, REG8_AH));

    memory_.store(0x8101, 0x50);

    cpu_.setD(0x8100);
    cpu_.setX(0x0001);
    cpu_.setAH(0x50);

    cpu_.run(); // go!

    ASSERT_EQ(startip_ + 2, cpu_.getIP());

    ASSERT_EQ(memory_.fetch(0x8101), 0xA0);

    ASSERT_CARRY_CLEAR(cpu_);
    ASSERT_ZERO_CLEAR(cpu_);
    ASSERT_OVERFLOW_SET(cpu_);
}

TEST_F(InstructionTest, TEST_ADC_MR16_0)
{
    // adc [d+x], b
    memory_.store(address_, OPCODE(&INS_ADC, AM_MR16));
    memory_.store(address_ + 1, MAKEOFFSETREG(REG16_D, REG16_B));

    memory_.storeWord(0x8101, 0x0001);

    cpu_.setD(0x8100);
    cpu_.setX(0x0001);
    cpu_.setB(0x8000);

    cpu_.run(); // go!

    ASSERT_EQ(startip_ + 2, cpu_.getIP());

    ASSERT_EQ(memory_.fetchWord(0x8101), 0x8001);

    ASSERT_CARRY_CLEAR(cpu_);
    ASSERT_ZERO_CLEAR(cpu_);
    ASSERT_OVERFLOW_CLEAR(cpu_);
}

TEST_F(InstructionTest, TEST_ADC_MR16_1)
{
    // adc [d+x], b -- set carry, zero
    memory_.store(address_, OPCODE(&INS_ADC, AM_MR16));
    memory_.store(address_ + 1, MAKEOFFSETREG(REG16_D, REG16_B));

    memory_.storeWord(0x8101, 0x0001);

    cpu_.setD(0x8100);
    cpu_.setX(0x0001);
    cpu_.setB(0xFFFF);

    cpu_.run(); // go!

    ASSERT_EQ(startip_ + 2, cpu_.getIP());

    ASSERT_EQ(memory_.fetchWord(0x8101), 0x0000);

    ASSERT_CARRY_SET(cpu_);
    ASSERT_ZERO_SET(cpu_);
    ASSERT_OVERFLOW_CLEAR(cpu_);
}

TEST_F(InstructionTest, TEST_ADC_MR16_2)
{
    // adc [d+x], b -- set overflow
    memory_.store(address_, OPCODE(&INS_ADC, AM_MR16));
    memory_.store(address_ + 1, MAKEOFFSETREG(REG16_D, REG16_B));

    memory_.storeWord(0x8101, 0x7FFF);

    cpu_.setD(0x8100);
    cpu_.setX(0x0001);
    cpu_.setB(0x7FFF);

    cpu_.run(); // go!

    ASSERT_EQ(startip_ + 2, cpu_.getIP());

    ASSERT_EQ(memory_.fetchWord(0x8101), 0xFFFE);

    ASSERT_CARRY_CLEAR(cpu_);
    ASSERT_ZERO_CLEAR(cpu_);
    ASSERT_OVERFLOW_SET(cpu_);
}

TEST_F(InstructionTest, TEST_ADC_M8I8_0)
{
    // adc [d+x], $08
    memory_.store(address_++, OPCODE(&INS_ADC, AM_M8I8));
    memory_.store(address_++, EFFECTIVEREG(REG16_D));
    memory_.store(address_++, 0x08);

    memory_.store(0x8101, 0x01);

    cpu_.setD(0x8100);
    cpu_.setX(0x0001);

    cpu_.run(); // go!

    ASSERT_EQ(startip_ + 3, cpu_.getIP());

    ASSERT_EQ(memory_.fetch(0x8101), 0x09);

    ASSERT_CARRY_CLEAR(cpu_);
    ASSERT_ZERO_CLEAR(cpu_);
    ASSERT_OVERFLOW_CLEAR(cpu_);
}
