/////////////////////////////////////////////////////////////////////////////
//
// MONITOR.H : Pixie Virtual Machine Monitor
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MONITOR_H__
#define __MONITOR_H__

#include "trap.h"
#include "Handler.h"
#include "Singleton.h"
#include "common.h"

// Forward declarations
class Monitor;

/////////////////////////////////////////////////////////////////////////////
// Monitor command
class Command
{
protected:
    Command() = default;
public:
    virtual ~Command() = default;
    virtual void exec(const stringvec& v) = 0;
};

/////////////////////////////////////////////////////////////////////////////

using CommandPtr = std::shared_ptr<Command>;
using CommandMap = StringKeyMap<CommandPtr>::Type;

class Monitor;
using MonitorPtr = unique_ptr<Monitor>;

/////////////////////////////////////////////////////////////////////////////
// Monitor class
class Monitor : public Singleton<Monitor>, public TrapHandler, public Handler
{
    // Construction / Destruction
    Monitor();
    friend class Singleton<Monitor>;
public:
    // Interface
    void trap(void* data) override; // trap handler
    void handle() override; // monitor handler

    void setExit(bool f) noexcept;
    bool assemble(word address, const string& str);
    void disassemble(word address);

    bool isRunning() const noexcept
    {
        return !m_exit_mon;
    }

    // Implementation
private:
    void run();
    void runLoop();

    void dispatch(const string& line);
    void prompt() const;
    void notice() const;

    static void sighandler(int signum);

    CommandMap m_commands;  // map of commands
    bool m_exit_mon;        // exit flag
    bool m_show_notice;     // show notice
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
inline void Monitor::setExit(bool f) noexcept
{
    m_exit_mon = f;
}

#endif // __MONITOR_H__
