/////////////////////////////////////////////////////////////////////////////
//
// MEMORY.H : Pixie Virtual Machine Memory
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "Singleton.h"

/////////////////////////////////////////////////////////////////////////////
class Memory : public Singleton<Memory>
{
    // Construction / Destruction
private:
    Memory();
    friend class Singleton<Memory>;
public:
    ~Memory();

    // Interface
    byte fetch(word address);
    void store(word address, byte b);
    bool load(istream& is, word base, int size);
    bool save(ostream& os, word base, int size);
private:
    enum { MEM_SIZE = 0x10000 };
    byte* memory;
};

#endif // __MEMORY_H__
