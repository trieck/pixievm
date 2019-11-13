/////////////////////////////////////////////////////////////////////////////
//
// MEMORY.H : Pixie Virtual Machine Memory
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "Singleton.h"

/////////////////////////////////////////////////////////////////////////////
class Memory : public Singleton<Memory>
{
    // Construction / Destruction
    Memory();
    friend class Singleton<Memory>;
public:
    ~Memory() = default;

    // Interface
    byte fetch(word address);
    void store(word address, byte b);
    bool load(istream& is, word base, int size);
    bool save(ostream& os, word base, int size);
private:
    enum { MEM_SIZE = 0x10000 };

    std::unique_ptr<byte[]> memory_;
};

#endif // __MEMORY_H__
