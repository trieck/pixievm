#include "StdAfx.h"
#include "PxEmu.h"
#include "PxEmuApp.h"
#include "MainFrm.h"
#include "CPU.H"
#include "PixieVM.h"
#include <sys/stat.h>
#include "Memory.h"
#include <boost/format.hpp>

extern PxEmuApp _Module;

/////////////////////////////////////////////////////////////////////////////
void PxEmulator::init()
{
    const auto hr = _Module.Init(nullptr, ModuleHelper::GetModuleInstance());
    if (FAILED(hr))
        throw std::exception("could not initialize module.");

    loadROM("chargen.rom", CHARGEN_BASE, CHARGEN_SIZE);
    loadROM("kernel.rom");
}

/////////////////////////////////////////////////////////////////////////////
void PxEmulator::loadROM(const char* filename, word base, word size) const
{
    ifstream ifs;
    ifs.open(filename, ifstream::in | ifstream::binary);
    if (!ifs.is_open()) {
        throw std::exception((boost::format("unable to open ROM image \"%s\".") % filename).str().c_str());
    }

    if (!Memory::instance().load(ifs, base, size)) {
        throw std::exception((boost::format("unable to load ROM image \"%s\".") % filename).str().c_str());
    }

    ifs.close();
}

/////////////////////////////////////////////////////////////////////////////
void PxEmulator::loadROM(const char* filename) const
{
    // load rom with contained load address

    struct _stat buf{};
    const auto n = stat(filename, reinterpret_cast<struct stat*>(&buf));
    if (n) {
        throw std::exception((boost::format("unable to stat ROM image \"%s\".") % filename).str().c_str());
    }

    ifstream ifs;
    ifs.open(filename, ifstream::in | ifstream::binary);
    if (!ifs.is_open()) {
        throw std::exception((boost::format("unable to open ROM image \"%s\".") % filename).str().c_str());
    }

    word start;
    ifs.read(reinterpret_cast<char*>(&start), sizeof(word));
    if (ifs.bad()) {
        throw std::exception((boost::format("unable to read from ROM image \"%s\".") % filename).str().c_str());
    }

    if (!Memory::instance().load(ifs, start, buf.st_size - sizeof(word))) {
        throw std::exception((boost::format("unable to load ROM image \"%s\".") % filename).str().c_str());
    }
}

/////////////////////////////////////////////////////////////////////////////
int PxEmulator::run()
{
    CMessageLoop theLoop;
    _Module.AddMessageLoop(&theLoop);

    CMainFrame wndMain;
    if (wndMain.CreateEx() == nullptr)
        throw std::exception("Main window creation failed!");

    STARTUPINFO info;
    GetStartupInfo(&info);
    const auto nCmdShow = info.dwFlags & STARTF_USESHOWWINDOW
                        ? info.wShowWindow
                        : SW_SHOWDEFAULT;

    wndMain.ShowWindow(nCmdShow);

    const auto nRet = CPU::instance().run();

    _Module.Term();

    return nRet;
}
