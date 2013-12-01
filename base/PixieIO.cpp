/////////////////////////////////////////////////////////////////////////////
//
// PIXIEIO.CPP : Pixie VM I/O handling
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "PixieIO.h"
#include "interrupt.h"

PixieIOPtr PixieIO::instance(PixieIO::getInstance());

#define DATA_REG_A	(regs[0])
#define DATA_REG_B	(regs[1])
#define DDR_A				(regs[2])
#define DDR_B				(regs[3])
#define TIMER_A_LO	(regs[4])
#define TIMER_A_HI	(regs[5])
#define TIMER_B_LO	(regs[6])
#define TIMER_B_HI	(regs[7])
#define	TOD_10THS		(regs[8])
#define TOD_SEC			(regs[9])
#define TOD_MIN			(regs[10])
#define TOD_HR			(regs[11])
#define SDR					(regs[12])
#define ICR					(regs[13])
#define CRA					(regs[14])
#define CRB					(regs[15])

#define LATCH_A_LO	(149)
#define LATCH_A_HI	(66)

/////////////////////////////////////////////////////////////////////////////
PixieIO::PixieIO()
{
	reset();
}

/////////////////////////////////////////////////////////////////////////////
PixieIO::~PixieIO()
{
}

/////////////////////////////////////////////////////////////////////////////
PixieIO *PixieIO::getInstance()
{
	if (instance.get() == NULL) {
		instance = PixieIOPtr(new PixieIO);
	}
	return instance.get();
}

/////////////////////////////////////////////////////////////////////////////
void PixieIO::reset()
{
	memset(regs, 0, sizeof(byte) * NREGS);
	memset(key_matrix, 0xFF, sizeof(byte) * 8);

	// total latch value of 17045
	TIMER_A_LO = LATCH_A_LO;
	TIMER_A_HI = LATCH_A_HI;

	TIMER_B_LO = TIMER_B_HI = 0xFF;
}

/////////////////////////////////////////////////////////////////////////////
uint8_t PixieIO::readRegister(uint16_t address)
{
	return regs[address & 0x0F];
}

/////////////////////////////////////////////////////////////////////////////
void PixieIO::writeRegister(uint16_t address, uint8_t b)
{
	regs[address & 0x0F] = b;
}

/////////////////////////////////////////////////////////////////////////////
void PixieIO::keyOn(uint8_t key_code)
{
	int byte = key_code >> 3;
	int bit = key_code & 7;
	key_matrix[byte] &= ~(1 << bit);
}

/////////////////////////////////////////////////////////////////////////////
void PixieIO::keyOff(uint8_t key_code)
{
	int byte = key_code >> 3;
	int bit = key_code & 7;
	key_matrix[byte] |= (1 << bit);
}

/////////////////////////////////////////////////////////////////////////////
void PixieIO::clockTrigger()
{
	if (--TIMER_A_LO == 0xFF) {		// underflow
		if (--TIMER_A_HI == 0xFF) {	// underflow
			TIMER_A_LO = LATCH_A_LO;
			TIMER_A_HI = LATCH_A_HI;
			g_interrupt.setPending(IK_IRQ);
		}
	}
}