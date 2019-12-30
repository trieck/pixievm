/////////////////////////////////////////////////////////////////////////////
//
// MEMORY.H : Pixie Virtual Machine Memory
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "Singleton.h"
#include "PixieIO.h"

/////////////////////////////////////////////////////////////////////////////
class Memory : public Singleton<Memory>
{
    // Construction / Destruction
    Memory();
    friend class Singleton<Memory>;
public:
    ~Memory() = default;

    // Interface
    void reset();
    byte fetch(word address) const;
    void store(word address, byte b);
    void storeWord(word address, word value);
    word fetchWord(word address) const;
    bool load(istream& is, word base, int size);
    bool save(ostream& os, word base, int size);
    const byte* ptr() const;
private:
    BytePtr memory_;
    PixieIO& io_;
};

#endif // __MEMORY_H__
