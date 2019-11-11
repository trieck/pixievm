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

/////////////////////////////////////////////////////////////////////////////
Monitor::Monitor() : m_exit_mon(false), m_show_notice(true)
{
    m_commands["help"] = m_commands["?"] = std::make_shared<HelpCmd>();
    m_commands["a"] = std::make_shared<AssemCmd>();
    m_commands["d"] = std::make_shared<DisassemCmd>();
    m_commands["l"] = std::make_shared<LoadCmd>();
    m_commands["m"] = std::make_shared<DumpCmd>();
    m_commands["q"] = std::make_shared<QuitCmd>();
    m_commands["r"] = std::make_shared<RegistersCmd>();
    m_commands["s"] = std::make_shared<SaveCmd>();
    m_commands["t"] = std::make_shared<StepCmd>();
    m_commands["u"] = std::make_shared<StepUntilCmd>();
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
    if (command != nullptr){
        auto* disassembler = dynamic_cast<DisassemCmd *>(command.get());
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

    for (m_exit_mon = false; !m_exit_mon;){
        prompt();
        const auto line = reader.readLine();
        if (line.length()){
            dispatch(line);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::notice() const
{
    if (m_show_notice){
        cout << "PixieVM Monitor version 0.0.2" << endl
            << "Copyright (c) 2006-2019 Thomas A. Rieck" << endl
            << "use CTRL+BREAK to break execution." << endl
            << "type '?' for help." << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////
void Monitor::dispatch(const string& line)
{
    auto v = tokenize(line);
    if (v.empty()){
        cerr << '?' << endl;
    } else{
        const auto it = m_commands.find(v.at(0));
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
    auto& This = instance();

    if (signum == SIGBREAK){
        if (!This.isRunning()){
            // executing code, not in monitor
            This.setExit(false); // set back to running to break
            signal(SIGBREAK, &Monitor::sighandler); // re-install
        } else{
            CPU::instance().setShutdown(true); // shut down CPU
            This.setExit(true); // exit monitor
        };
    }
}
