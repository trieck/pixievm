
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

CAppModule _Module;
HWND hwndClient;

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

	for (int i = 0; i < 50; ++i) {
		for (int j = 0; j < 80; ++j) {
			memory->store(VIDEORAM_BASE+(i*80)+j, 65 + (j%26));
			memory->store(COLORRAM_BASE+(i*80)+j, i*80+j);
		}
	}
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
