#include "common.h"

/////////////////////////////////////////////////////////////////////////////
void AssertMessage(const char* msg, const char* file, uint32_t line)
{
    fprintf(stderr, "ASSERTION FAILURE (%s)! in file %s at line %d.",
            msg, file, line);
    exit(EXIT_FAILURE);
}
