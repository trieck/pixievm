/////////////////////////////////////////////////////////////////////////////
//
// EXCEPTION.H : Simple exception class
//
// Copyright (c) 2006-2013, Thomas A. Rieck
// All Rights Reserved
//

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <utility>

/////////////////////////////////////////////////////////////////////////////
class Exception
{
    // Construction / Destruction
public:
    Exception(const char* fmt, ...) 
    {
        char buffer[BUFF_SIZE];
        va_list arglist;
        va_start(arglist, fmt);
        vsprintf_s(buffer, fmt, arglist);
        va_end(arglist);
        m_desc = buffer;
    }

    Exception(string desc) : m_desc(std::move(desc))
    {
    }

    Exception(const Exception& rhs)
    {
        *this = rhs;
    }

    virtual ~Exception() = default;

    // Interface
    Exception& operator=(const Exception& rhs)
    {
        if (this != &rhs){
            m_desc = rhs.m_desc;
        }
        return *this;
    }

    string getDescription() const noexcept
    {
        return m_desc;
    }

    // Implementation
private:
    string m_desc;

    enum { BUFF_SIZE = 1024 };
};

#endif  // __EXCEPTION_H__
