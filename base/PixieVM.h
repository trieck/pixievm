/////////////////////////////////////////////////////////////////////////////
//
// PIXIEVM.H : Pixie virtual machine definitions
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __PIXIEVM_H__
#define __PIXIEVM_H__

// 8-bit registers
#define REG8_AL				(0x00)
#define REG8_AH				(0x01)
#define REG8_BL				(0x02)
#define REG8_BH				(0x03)
#define REG8_CL				(0x04)
#define REG8_CH				(0x05)
#define REG8_DL				(0x06)
#define REG8_DH				(0x07)

// 16-bit registers
#define REG16_A				(0x00)
#define REG16_B				(0x01)
#define REG16_C				(0x02)
#define REG16_D				(0x03)
#define REG16_X				(0x04)
#define REG16_SP			(0x05)

// CPU flags
#define NEG_FLAG            (0x80)
#define OVERFLOW_FLAG       (0x40)
#define BRK_FLAG            (0x08)
#define INT_DISABLE_FLAG    (0x04)
#define ZERO_FLAG           (0x02)
#define CARRY_FLAG          (0x01)

// register encoding
#define MAKEREG(hi, lo)		((hi << 4) | lo)

// 8-bit register decoding
#define HIREG8(n)           (LOREG8((n >> 4)))
#define LOREG8(n)           (n & 7)

// 16-bit register decoding
#define HIREG16(n)          (LOREG16((n >> 4)))
#define LOREG16(n)          (n & ((n&5) | ((~n&4) >> 1)))

// instruction opcode lookup by addressing mode
#define OPCODE(i, m)				(*(*i)[m])

#define VIDEORAM_BASE				(0xA000)
#define VIDEORAM_SIZE				(0x1000)

#define COLORRAM_BASE				(0xB000)
#define COLORRAM_SIZE				(0x1000)

#define CHARGEN_BASE				(0xC000)
#define CHARGEN_SIZE				(0x800)

#define TOP_STACK_AREA			(0x01FF)

#define IO_REGISTER_BASE		(0xD000)
#define IO_REGISTER_SIZE		(0x1000)

#define IO_REGISTERS_START	(0xD100)
#define IO_REGISTERS_STOP		(0xD10F)

#define KERNEL_BASE					(0xE000)

#endif // __PIXIEVM_H__
