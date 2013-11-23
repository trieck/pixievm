/////////////////////////////////////////////////////////////////////////////
//
// MEMORY.CPP : Pixie Virtual Machine Memory
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Memory.h"
#include "PixieVM.h"

MemoryPtr Memory::instance(Memory::getInstance());

/////////////////////////////////////////////////////////////////////////////
Memory::Memory()
{
	memory = new byte[MEM_SIZE];
	memset(memory, 0, MEM_SIZE * sizeof(byte));
}

/////////////////////////////////////////////////////////////////////////////
Memory::~Memory()
{
	delete[] memory;
}

/////////////////////////////////////////////////////////////////////////////
Memory *Memory::getInstance()
{
	if (instance.get() == NULL) {
		instance = MemoryPtr(new Memory);
	}
	return instance.get();
}

/////////////////////////////////////////////////////////////////////////////
byte Memory::fetch(word address)
{
	return memory[address];
}

/////////////////////////////////////////////////////////////////////////////
void Memory::store(word address, byte b)
{
	// writes to ROM have no effect
	if ((address >= CHARGEN_BASE && address < CHARGEN_BASE+CHARGEN_SIZE) ||
		(address >= KERNEL_BASE))
		return;

	memory[address] = b;
}

/////////////////////////////////////////////////////////////////////////////
bool Memory::load(istream & is, word base, int size)
{
	is.read((char *) &memory[base], size);
	return is.good();
}

/////////////////////////////////////////////////////////////////////////////
bool Memory::save(ostream & os, word base, int size)
{
	os.write((const char *)&memory[base], size);
	return os.good();
}