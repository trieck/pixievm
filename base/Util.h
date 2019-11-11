/////////////////////////////////////////////////////////////////////////////
//
// UTIL.H : Utility functions
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __UTIL_H__
#define __UTIL_H__

/////////////////////////////////////////////////////////////////////////////
stringvec split(const string& s, const char* del);
stringvec tokenize(const string& s);
string trim(const string& s);
string basename(const string& file);
uint32_t hash32(const void* key, uint32_t len);
/////////////////////////////////////////////////////////////////////////////

#endif // __UTIL_H__
