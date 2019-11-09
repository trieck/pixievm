/////////////////////////////////////////////////////////////////////////////
//
// MONITOR.CPP : Pixie Virtual Machine Monitor
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "monitor.h"
#include "LineReader.h"
#include "util.h"
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
#include "CPU.H"
#include <csignal>

MonitorPtr Monitor::instance(Monitor::getInstance());

/////////////////////////////////////////////////////////////////////////////
Monitor::Monitor() : m_exit_mon(false), m_show_notice(true)
{
    m_commands["?"] = std::make_shared<HelpCmd>(this);
    m_commands["help"] = m_commands["?"];
    m_commands["a"] = std::make_shared<AssemCmd>(this);
    m_commands["d"] = std::make_shared<DisassemCmd>(this);
    m_commands["l"] = std::make_shared<LoadCmd>(this);
    m_commands["m"] = std::make_shared<DumpCmd>(this);
    m_commands["q"] = std::make_shared<QuitCmd>(this);
    m_commands["r"] = std::make_shared<RegistersCmd>(this);
    m_commands["s"] = std::make_shared<SaveCmd>(this);
    m_commands["t"] = std::make_shared<StepCmd>(this);
    m_commands["u"] = std::make_shared<StepUntilCmd>(this);
}

/////////////////////////////////////////////////////////////////////////////
Monitor::~Monitor() = default;

/////////////////////////////////////////////////////////////////////////////
Monitor* Monitor::getInstance()
{
    if (instance.get() == nullptr){
        instance = MonitorPtr(new Monitor);
    }
    return instance.get();
}

/////////////////////////////////////////////////////////////////////////////
bool Monitor::assemble(word address, const string& str)
{
    auto result = false;

    const auto command = m_commands.at("a");
    if (command != nullptr){
        auto* assembler = dynamic_cast<AssemCmd *>(command.get());
        result = assembler->assemble(address, str);
    }

    return result;
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::disassemble(const word address)
{
    // this is a single line convenience method used by the stepper
    const auto command = m_commands.at("d");
    if (command != nullptr) {
      auto *disassembler = dynamic_cast<DisassemCmd *>(command.get());
      disassembler->disassemble(address);
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

    for (m_exit_mon = false; !m_exit_mon;){
        prompt();
        line = reader.readLine();
        if (line.length())
            dispatch(line);
    }
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::notice() const
{
    if (m_show_notice){
        cout << "PixieVM Monitor version 0.0.1" << endl
            << "Copyright (c) 2006-2013 Thomas A. Rieck" << endl
            << "use CTRL+BREAK to break execution." << endl
            << "type '?' for help." << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::dispatch(const string& line)
{
    stringvec v = tokenize(line);
    if (v.empty()){
        cerr << '?' << endl;
    } else{
        CommandMap::const_iterator it = m_commands.find(v[0]);
        if (it == m_commands.end()){
            cerr << '?' << endl;
        } else{
            v.erase(v.begin());
            auto command = (*it).second;
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
    run();
}

////////////////////////////////////////////////////////////////////////////
void Monitor::trap(void* data)
{
    runLoop();
}

////////////////////////////////////////////////////////////////////////////
void Monitor::sighandler(int signum)
{
    auto* This = Monitor::getInstance();

    switch (signum){
    case SIGBREAK:
        if (!This->isRunning()){
            // executing code, not in monitor
            This->setExit(false); // set back to running to break
            signal(SIGBREAK, &Monitor::sighandler); // re-install
        } else{
            CPU::instance().setShutdown(true); // shut down CPU
            This->setExit(true); // exit monitor
        }
    default:
        break;
    };
}
