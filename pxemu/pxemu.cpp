#include "StdAfx.h"
#include "PxEmu.h"
#include "exception.h"
#include "MainFrm.h"
#include "CPU.H"
#include "Alarm.h"
#include "RasterHandler.h"
#include "PixieVM.h"
#include <sys/stat.h>
#include "memory.h"

CAppModule _Module;

/////////////////////////////////////////////////////////////////////////////
PxEmulator::PxEmulator()
{
}

/////////////////////////////////////////////////////////////////////////////
void PxEmulator::init()
{
    auto hr = _Module.Init(nullptr, ModuleHelper::GetModuleInstance());
    if (FAILED(hr))
        throw Exception("could not initialize module.");

    loadROM("chargen.rom", CHARGEN_BASE, CHARGEN_SIZE);
    loadROM("kernel.rom");
}

/////////////////////////////////////////////////////////////////////////////
void PxEmulator::loadROM(const char* filename, word base, word size) const
{
    ifstream ifs;
    ifs.open(filename, ifstream::in | ifstream::binary);
    if (!ifs.is_open()){
        throw Exception("unable to open ROM image \"%s\".", filename);
    }

    if (!Memory::instance().load(ifs, base, size)){
        throw Exception("unable to load ROM image \"%s\".", filename);
    }

    ifs.close();
}

/////////////////////////////////////////////////////////////////////////////
void PxEmulator::loadROM(const char* filename) const
{
    // load rom with contained load address

    struct _stat buf{};
    const auto n = stat(filename, reinterpret_cast<struct stat*>(&buf));
    if (n){
        throw Exception("unable to stat ROM image \"%s\".", filename);
    }

    ifstream ifs;
    ifs.open(filename, ifstream::in | ifstream::binary);
    if (!ifs.is_open()){
        throw Exception("unable to open ROM image \"%s\".", filename);
    }

    word start;
    ifs.read(reinterpret_cast<char*>(&start), sizeof(word));
    if (ifs.bad()){
        throw Exception("unable to read from ROM image \"%s\".", filename);
    }

    if (!Memory::instance().load(ifs, start, buf.st_size - sizeof(word))){
        throw Exception("unable to load ROM image \"%s\".", filename);
    }
}

/////////////////////////////////////////////////////////////////////////////
int PxEmulator::run()
{
    CMessageLoop theLoop;
    _Module.AddMessageLoop(&theLoop);

    CMainFrame wndMain;
    if (wndMain.CreateEx() == nullptr)
        throw Exception("Main window creation failed!");

    STARTUPINFO info;
    GetStartupInfo(&info);
    int nCmdShow = info.dwFlags & STARTF_USESHOWWINDOW
                       ? info.wShowWindow
                       : SW_SHOWDEFAULT;

    wndMain.ShowWindow(nCmdShow);

    Alarms::instance().addAlarm<RasterHandler>();
    //auto nRet = theLoop.Run();

    auto nRet = CPU::instance().run();

    _Module.Term();

    return nRet;
}
