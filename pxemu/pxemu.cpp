
#include "stdafx.h"
#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>
#include "pxemu.h"
#include "Exception.h"
#include "resource.h"
#include "pxemuView.h"
#include "aboutdlg.h"
#include "MainFrm.h"
#include "CPU.H"
#include "Alarm.h"
#include "RasterHandler.h"
#include "PixieVM.h"
#include <sys/stat.h>

CAppModule _Module;

/////////////////////////////////////////////////////////////////////////////
PxEmulator::PxEmulator()
{
	memory = Memory::getInstance();
}

/////////////////////////////////////////////////////////////////////////////
PxEmulator::~PxEmulator()
{
}

/////////////////////////////////////////////////////////////////////////////
void PxEmulator::init()
{
	HRESULT hr = _Module.Init(NULL, ModuleHelper::GetModuleInstance());
	if (FAILED(hr))
		throw Exception("could not initialize module.");

	loadROM("chargen.rom", CHARGEN_BASE, CHARGEN_SIZE);
	loadROM("kernel.rom");
}

/////////////////////////////////////////////////////////////////////////////
void PxEmulator::loadROM(const char *filename, word base, word size)
{
	ifstream ifs;
	ifs.open(filename, ifstream::in | ifstream::binary);
	if (!ifs.is_open()) {
		throw Exception("unable to open ROM image \"%s\".", filename);
	}

	if (!memory->load(ifs, base, size)) {
		throw Exception("unable to load ROM image \"%s\".", filename);
	}

	ifs.close();
}

/////////////////////////////////////////////////////////////////////////////
void PxEmulator::loadROM(const char* filename)
{
	// load rom with contained load address

	struct _stat buf;
	int n = stat(filename, (struct stat*)&buf);
	if (n) {
		throw Exception("unable to stat ROM image \"%s\".", filename);
	}

	ifstream ifs;
	ifs.open(filename, ifstream::in | ifstream::binary);
	if (!ifs.is_open()) {
		throw Exception("unable to open ROM image \"%s\".", filename);
	}

	word start;
	ifs.read((char*)&start, sizeof(word));
	if (ifs.bad()) {
		throw Exception("unable to read from ROM image \"%s\".", filename);
	}

	if (!memory->load(ifs, start, buf.st_size - sizeof(word))) {
		throw Exception("unable to load ROM image \"%s\".", filename);
	}
}

/////////////////////////////////////////////////////////////////////////////
int PxEmulator::run()
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);
	
	CMainFrame wndMain;
	if (wndMain.CreateEx() == NULL)
		throw Exception("Main window creation failed!");

	STARTUPINFO info;
	GetStartupInfo(&info);
	int nCmdShow = info.dwFlags & STARTF_USESHOWWINDOW
		? info.wShowWindow
		: SW_SHOWDEFAULT;

	wndMain.ShowWindow(nCmdShow);

	g_alarms.addAlarm<RasterHandler>();

	int nRet = CPU::getInstance()->run();

	_Module.Term();

	return nRet;
}
