
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
#include "UIEventHandler.h"

#define CHARGEN_BASE (0xC000)
#define CHARGEN_SIZE (0x800)

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
	wndMain.ShowWindow(info.wShowWindow);

	g_alarms.addAlarm<UIEventHandler>();

	CPU* cpu = CPU::getInstance();
	int nRet = cpu->run();

	_Module.Term();

	return nRet;
}
