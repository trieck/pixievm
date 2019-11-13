/////////////////////////////////////////////////////////////////////////////
//
// UTIL.CPP : Utility functions
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "util.h"

#ifdef _MSC_VER
#define PATH_SEP '\\'
#else
#define PATH_SEP '/'
#endif	// _MSC_VER

#define SUFFIX_SEP '.'

/////////////////////////////////////////////////////////////////////////////
stringvec tokenize(const string& s)
{
    stringvec output;

    const auto* pstart = s.c_str();
    const auto** ppin = &pstart;
    const auto* pin = *ppin;

    for (;;) {
        switch (*pin) {
        case '\0':
            if (pin > *ppin) {
                output.push_back(string(*ppin, pin - *ppin));
                *ppin = pin;
            }
            return output;
        case '"':
            if (pin > *ppin) {
                output.push_back(string(*ppin, pin - *ppin));
                *ppin = pin;
            }
            pin++; /* eat quote */
            (*ppin)++;
            while (*pin && *pin++ != '"');
            output.push_back(string(*ppin, pin - *ppin - 1));
            *ppin = pin;
            continue;
        case '\r':
        case '\n':
        case '\t':
        case ' ':
            if (pin > *ppin) {
                output.push_back(string(*ppin, pin - *ppin));
                *ppin = pin;
            }
            (*ppin)++; /* eat white */
            break;
        default:
            pin++;
            continue;
        }
        pin++;
    }
}

/////////////////////////////////////////////////////////////////////////////
string trim(const string& s)
{
    string output;

    const auto* pin = s.c_str();
    for (; *pin; pin++) {
        if (!isspace(*pin))
            break;
    }

    const auto* pend = s.c_str() + s.length();
    for (; pend != pin;) {
        if (!isspace(*--pend))
            break;
    }

    for (; *pin && pin <= pend; pin++) {
        output += *pin;
    }

    return output;
}

/////////////////////////////////////////////////////////////////////////////
string basename(const string& filename)
{
    string output;

    const auto* fname = filename.c_str();
    const char* p;
    if ((p = strrchr(fname, PATH_SEP)) != nullptr) {
        fname = p + 1;
    }

    for (; *fname != '\0'; fname++) {
        if (*fname == SUFFIX_SEP)
            break;

        output += *fname;
    }

    return output;
}

////////////////////////////////////////////////////////////////////////////
// 32-bit Fowler/Noll/Vo hash
uint32_t hash32(const void* key, uint32_t len)
{
    uint32_t i;
    uint32_t hash;
    const auto* k = static_cast<const uint8_t*>(key);

    for (hash = 0, i = 0; i < len; ++i) {
        hash *= 16777619;
        hash ^= k[i];
    }

    return hash;
}
