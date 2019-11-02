#include "stdafx.h"
#include "pxemu.h"
#include "Exception.h"

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
    PxEmulator emulator;

    auto ret = 0;

    try{
        emulator.init();
        ret = emulator.run();
    } catch (const Exception& /*e*/){
        return 1;
    }

    return ret;
}
