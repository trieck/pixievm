/////////////////////////////////////////////////////////////////////////////
//
// MONITOR.CPP : Pixie Virtual Machine Monitor
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Monitor.h"
#include "LineReader.h"
#include "Util.h"
#include "HelpCmd.h"
#include "AssemCmd.h"
#include "DisassemCmd.h"
#include "LoadCmd.h"
#include "QuitCmd.h"
#include "RegistersCmd.h"
#include "SaveCmd.h"
#include "DumpCmd.h"
#include "StepCmd.h"
#include "StepUntilCmd.h"
#include "Interrupt.h"
#include "CPU.h"
#include "Options.h"
#include <signal.h>

MonitorPtr Monitor::instance(Monitor::getInstance());

/////////////////////////////////////////////////////////////////////////////
Monitor::Monitor() : m_exit_mon(false), m_show_notice(true), 
	m_pTestData(NULL), m_testMode(false), m_pTest(NULL)
{
	m_commands["?"] = new HelpCmd(this);
	m_commands["help"] = m_commands["?"]->CopyRef();
	m_commands["a"] = new AssemCmd(this);
	m_commands["d"] = new DisassemCmd(this);
	m_commands["l"] = new LoadCmd(this);
	m_commands["m"] = new DumpCmd(this);
	m_commands["q"] = new QuitCmd(this);
	m_commands["r"] = new RegistersCmd(this);
	m_commands["s"] = new SaveCmd(this);
	m_commands["t"] = new StepCmd(this);
	m_commands["u"] = new StepUntilCmd(this);
}

/////////////////////////////////////////////////////////////////////////////
Monitor::~Monitor()
{
	CommandMap::const_iterator it = m_commands.begin();
	for (; it != m_commands.end(); it++) {
		LPCOMMAND cmd = (*it).second;
		cmd->DecRef();
	}

	delete m_pTestData;
}

/////////////////////////////////////////////////////////////////////////////
Monitor *Monitor::getInstance()
{
	if (instance.get() == NULL) {
		instance = MonitorPtr(new Monitor);
	}
	return instance.get();
}

/////////////////////////////////////////////////////////////////////////////
bool Monitor::assemble(word address, const string &str)
{
	bool result = false;

	AssemCmd *assembler = static_cast<AssemCmd*>(m_commands["a"]);
	if (assembler != NULL) {
		result = assembler->assemble(address, str);
	}

	return result;
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::disassemble(word address)
{
	// this is a single line convenience method used by the stepper

	DisassemCmd *disassemble = static_cast<DisassemCmd*>(m_commands["d"]);
	if (disassemble != NULL) {
		disassemble->disassemble(address);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::run()
{
	notice();
	signal(SIGBREAK, &Monitor::sighandler);
	runLoop();
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::runLoop()
{
	LineReader reader(cin);
	string line;

	for (m_exit_mon = false; !m_exit_mon; ) {
		prompt();
		line = reader.readLine();
		if (line.length())
			dispatch(line);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::notice() const
{
	if (m_show_notice) {
		cout << "PixieVM Monitor version 0.0.1" << endl
		     << "Copyright (c) 2006-2009 Thomas A. Rieck" << endl
		     << "use CTRL+BREAK to break execution." << endl
		     << "type '?' for help." << endl;
	}
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::dispatch(const string & line)
{
	stringvec v = tokenize(line);
	if (v.size() == 0) {
		cerr << '?' << endl;
	} else {
		CommandMap::const_iterator it = m_commands.find(v[0]);
		if (it == m_commands.end()) {
			cerr << '?' << endl;
		} else {
			v.erase(v.begin());
			LPCOMMAND command = (*it).second;
			command->exec(v);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::prompt() const
{
	cout << "> ";
}

////////////////////////////////////////////////////////////////////////////
void Monitor::handle()
{
	m_testMode = Options::isoption("test");

	if (m_testMode) {
		nextTest();		
	} else {
		run();
	}
}

////////////////////////////////////////////////////////////////////////////
void Monitor::trap(void *data)
{
	if (m_testMode) {
		nextTest();
	} else {
		runLoop();
	}
}

////////////////////////////////////////////////////////////////////////////
void Monitor::verifyRegs() const
{
	CPU* cpu = CPU::getInstance();

	TEST_ASSERT(cpu->getA() == m_pTest->registers[0]);
	TEST_ASSERT(cpu->getB() == m_pTest->registers[1]);
	TEST_ASSERT(cpu->getC() == m_pTest->registers[2]);
	TEST_ASSERT(cpu->getD() == m_pTest->registers[3]);
	TEST_ASSERT(cpu->getX() == m_pTest->registers[4]);
	TEST_ASSERT(cpu->getSP() == m_pTest->registers[5]);
	TEST_ASSERT(cpu->getIP() == m_pTest->registers[6]);
	TEST_ASSERT(cpu->getFL() == m_pTest->registers[7]);
}

////////////////////////////////////////////////////////////////////////////
void Monitor::nextTest()
{
	CPU* cpu = CPU::getInstance();

	if (m_pTestData == NULL)
		m_pTestData = TestData::create();

	// verify test results
	if (m_pTest != NULL) {
		verifyRegs();
	}

	if ((m_pTest = m_pTestData->next()) == NULL) {
		cpu->setShutdown(true);
		return;	// no more data
	}

	// assemble test instruction
	cpu->setIP(0);
	TEST_ASSERT(assemble(0, m_pTest->instruction));

	g_interrupt.setPending(IK_TRAP);	// setup next test
}

////////////////////////////////////////////////////////////////////////////
void Monitor::sighandler(int signum)
{
	Monitor *This = Monitor::getInstance();
	CPU *cpu = CPU::getInstance();

	switch (signum) {
	case SIGBREAK:
		if (!This->isRunning()) {	// executing code, not in monitor
			This->setExit(false);		// set back to running to break
			signal(SIGBREAK, &Monitor::sighandler);	// re-install
		} else {
			cpu->setShutdown(true);	// shut down CPU
			This->setExit(true);		// exit monitor
		}		
	default:
		break;
	};
}