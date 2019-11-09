#pragma once

/////////////////////////////////////////////////////////////////////////////
class PxEmulator
{
    // Construction / Destruction
public:
    PxEmulator();
    ~PxEmulator() = default;

    // Interface
    void init();
    int run();

    // Implementation
private:
    void loadROM(const char* filename, word base, word size) const;
    void loadROM(const char* filename) const;
};
