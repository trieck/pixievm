/////////////////////////////////////////////////////////////////////////////
//
// CPU.H : Pixie VM I/O handling
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __IO_H__
#define __IO_H__

class IO;
typedef auto_ptr<IO> IOPtr;

/////////////////////////////////////////////////////////////////////////////
class IO 
{
// Construction / Destruction
private:
	IO();
public:
	~IO();

// Interface
public:
	static IO *getInstance();

	void reset();
	uint8_t readRegister(uint16_t address);
	void writeRegister(uint16_t address, uint8_t b);
	void keyOn(uint8_t key_code);
	void keyOff(uint8_t key_code);

// Implementation
private:
	static IOPtr instance;		// singleton instance

	enum { NREGS = 18 };			// number of registers
	byte regs[NREGS];					// registers
	byte key_matrix[8];				// keyboard matrix
};
/////////////////////////////////////////////////////////////////////////////

#endif // __IO_H__
