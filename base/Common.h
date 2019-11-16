/////////////////////////////////////////////////////////////////////////////
//
// COMMON.H : Common include
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef _MSC_VER
#pragma warning(disable : 4302)  // disable truncation warnings
#pragma warning(disable : 4996)  // disable deprecation warnings

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif  // _MSC_VER

/////////////////////////////////////////////////////////////////////////////
#include <stdarg.h>
#include <stdint.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string.hpp>

using std::unique_ptr;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::istream;
using std::unordered_map;
using std::ofstream;
using std::ostream;
using std::ostringstream;
using std::string;
using std::vector;

typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;

typedef vector<string> stringvec;

template <typename Value>
class StringKeyMap
{
    StringKeyMap() = default;

    struct case_insensitive_hash
    {
        size_t operator()(const std::string& key) const
        {
            const auto copy = boost::to_lower_copy(key);
            return std::hash<std::string>()(copy);
        }
    };

    struct case_insensitive_compare
    {
        bool operator()(const string& left, const string& right) const
        {
            return boost::iequals(left, right);
        }
    };

public:
    using Type = unordered_map<string, Value, case_insensitive_hash, case_insensitive_compare>;
};

using StringStringMap = StringKeyMap<string>::Type;

#ifndef HIBYTE
#define HIBYTE(w) ((w & 0xFF00) >> 8)
#endif  // HIBYTE

#ifndef LOBYTE
#define LOBYTE(w) (w & 0xFF)
#endif  // LOBYTE

#define HINYBBLE(b) ((b & 0xF0) >> 4)
#define LONYBBLE(b) (b & 0x0F)

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

#define ANON_BEGIN namespace {
#define ANON_END }

#undef ASSERT
#ifdef _DEBUG
extern void AssertMessage(const char* msg, const char* file, uint32_t line);
#define ASSERT(f)                            \
  {                                          \
    if (!(f))                                \
      AssertMessage(#f, __FILE__, __LINE__); \
  }
#else
#define ASSERT(f) ((void)0)
#endif

/////////////////////////////////////////////////////////////////////////////

#endif  // __COMMON_H__
