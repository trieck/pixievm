/////////////////////////////////////////////////////////////////////////////
//
// MACHINE.H : Pixie Virtual Machine
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MACHINE_H__
#define __MACHINE_H__

/////////////////////////////////////////////////////////////////////////////
class Machine
{
    // Construction / Destruction
public:
    Machine() = default;
    ~Machine() = default;

    // Interface
    void init();
    int run();

    // Implementation
private:
    void loadROM(const char* filename, word base, word size);
    void loadROM(const char* filename);
};

/////////////////////////////////////////////////////////////////////////////

#endif // __MACHINE_H__
