/////////////////////////////////////////////////////////////////////////////
//
// LINEREADER.H : Read lines from input stream
//
// Copyright (c) 2006-2019, Thomas A. Rieck
//

#ifndef __LINEREADER_H__
#define __LINEREADER_H__

/////////////////////////////////////////////////////////////////////////////
class LineReader
{
    // Construction / Destruction
public:
    LineReader(istream& s) : is(s)
    {
    }

    ~LineReader() = default;

    // Interface
    string readLine();

    // Implementation
private:
    istream& is;
};

#endif // __LINEREADER_H__
