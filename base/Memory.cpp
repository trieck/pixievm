/////////////////////////////////////////////////////////////////////////////
//
// MEMORY.CPP : Pixie Virtual Machine Memory
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "memory.h"
#include "PixieVM.h"
#include "PixieIO.h"

/////////////////////////////////////////////////////////////////////////////
Memory::Memory()
{
    memory_ = std::make_unique<byte[]>(MEM_SIZE);
    reset();
}

/////////////////////////////////////////////////////////////////////////////
void Memory::reset()
{
    memset(&memory_[0], 0, MEM_SIZE * sizeof(byte));
}

/////////////////////////////////////////////////////////////////////////////
byte Memory::fetch(word address)
{
    if (address >= IO_REGISTERS_START && address <= IO_REGISTERS_STOP) {
        return PixieIO::instance().readRegister(address & 0x0F);
    }

    return memory_[address];
}

/////////////////////////////////////////////////////////////////////////////
void Memory::store(word address, byte b)
{
    if (address >= IO_REGISTERS_START && address <= IO_REGISTERS_STOP) {
        PixieIO::instance().writeRegister(address & 0x0F, b);
        return;
    }

    memory_[address] = b;
}

void Memory::storeWord(word address, word value)
{
    store(address, HIBYTE(value));
    store(address+ 1, LOBYTE(value));
}

/////////////////////////////////////////////////////////////////////////////
bool Memory::load(istream& is, word base, int size)
{
    is.read(reinterpret_cast<char *>(&memory_[base]), size);
    return is.good();
}

/////////////////////////////////////////////////////////////////////////////
bool Memory::save(ostream& os, word base, int size)
{
    os.write(reinterpret_cast<const char *>(&memory_[base]), size);
    return os.good();
}
