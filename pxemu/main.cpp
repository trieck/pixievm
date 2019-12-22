#include "stdafx.h"
#include "pxemu.h"

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
    PxEmulator emulator;

    auto ret = 0;

    try {
        emulator.init();
        ret = emulator.run();
    } catch (const std::exception& /*e*/) {
        return 1;
    } catch (const CAtlException& /*e*/) {
        return 1;
    }

    return ret;
}
