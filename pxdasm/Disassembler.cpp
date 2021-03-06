/////////////////////////////////////////////////////////////////////////////
//
// DISASSEMBLER.CPP : PixieVM Disassembler
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Disassembler.h"
#include <boost/format.hpp>

/////////////////////////////////////////////////////////////////////////////
Disassembler::Disassembler() : m_fp(nullptr)
{
}

/////////////////////////////////////////////////////////////////////////////
Disassembler::~Disassembler()
{
    close();
}

/////////////////////////////////////////////////////////////////////////////
void Disassembler::close() noexcept
{
    if (m_fp != nullptr) {
        fclose(m_fp);
        m_fp = nullptr;
    }
}

/////////////////////////////////////////////////////////////////////////////
void Disassembler::open(const char* filename)
{
    close();

    if ((m_fp = fopen(filename, "rb")) == nullptr) {
        throw std::exception((boost::format("can't open file \"%s\": %s.") % filename
            % strerror(errno)).str().c_str());
    }
}

/////////////////////////////////////////////////////////////////////////////
void Disassembler::disassemble(const char* filename)
{
    open(filename);

    word start;
    if ((1 != fread(&start, sizeof(word), 1, m_fp))) {
        throw std::exception((boost::format("can't read from file \"%s\": %s.") % filename
            % strerror(errno)).str().c_str());
    }

    ip = start;

    int c;
    while ((c = fgetc(m_fp)) != EOF) {
        ungetc(c, m_fp);
        printip();
        PxDisassembler::disassemble(fetch());
    }

    close();
}

/////////////////////////////////////////////////////////////////////////////
byte Disassembler::fetch()
{
    int c;
    if ((c = fgetc(m_fp)) == EOF)
        return 0;

    ++ip;

    return c;
}
