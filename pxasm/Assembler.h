/////////////////////////////////////////////////////////////////////////////
//
// ASSEMBLER.H : Assembler interface
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

/////////////////////////////////////////////////////////////////////////////
class Assembler
{
public:
    Assembler() = default;
    ~Assembler();

    int assemble(const char* source);
    int assemble(const char* source, const char* output);
private:
    void open(const char* filename);
    void close();

    FILE* m_pOut = nullptr; // output file pointer
};

#endif // __ASSEMBLER_H__
