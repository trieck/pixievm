/////////////////////////////////////////////////////////////////////////////
//
// DISASSEMBLER.H : PixieVM Disassembler
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __DISASSEMBLER_H__
#define __DISASSEMBLER_H__

#include "PxDisassembler.h"

/////////////////////////////////////////////////////////////////////////////
class Disassembler : public PxDisassembler
{
public:
    Disassembler();
    virtual ~Disassembler();

    void disassemble(const char* filename);

protected:
    byte fetch() override;
private:
    void open(const char* filename);
    void close() noexcept;
    FILE* m_fp;
};

#endif // __DISASSEMBLER_H__
