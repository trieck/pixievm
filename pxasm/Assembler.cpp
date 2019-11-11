/////////////////////////////////////////////////////////////////////////////
//
// ASSEMBLER.CPP : Assembler interface
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Assembler.h"
#include "exception.h"
#include "code.h"
#include "util.h"
#include <boost/format.hpp>

extern int yyparse(void);   // bison parser routine
extern FILE* yyin;          // input file pointer
extern Code code;           // code instance

using boost::format;

/////////////////////////////////////////////////////////////////////////////
Assembler::Assembler() : m_pOut(nullptr)
{
}

/////////////////////////////////////////////////////////////////////////////
Assembler::~Assembler()
{
    close();
}

/////////////////////////////////////////////////////////////////////////////
void Assembler::open(const char* filename)
{
    close();

    if ((yyin = fopen(filename, "r")) == nullptr){
        throw Exception("can't open file \"%s\": %s.", filename,
                        strerror(errno));
    }
}

/////////////////////////////////////////////////////////////////////////////
void Assembler::close()
{
    if (yyin != nullptr && yyin != stdin){
        fclose(yyin);
        yyin = nullptr;
    }

    if (m_pOut != nullptr){
        fclose(m_pOut);
        m_pOut = nullptr;
    }
}

/////////////////////////////////////////////////////////////////////////////
int Assembler::assemble(const char* source, const char* output)
{
    open(source);

    int nret;
    if ((nret = yyparse()) != 0)
        return nret;

    // second pass
    code.pass2();

    // write code to output file	
    if ((m_pOut = fopen(output, "wb")) == nullptr){
        throw Exception("can't open file \"%s\": %s.", output, strerror(errno));
    }

    code.write(m_pOut);

    close();

    return 0;
}

/////////////////////////////////////////////////////////////////////////////
int Assembler::assemble(const char* source)
{
    const auto output = (format("%s.o") % basename(source).c_str()).str();
    return assemble(source, output.c_str());
}
