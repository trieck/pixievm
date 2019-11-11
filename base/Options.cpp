/////////////////////////////////////////////////////////////////////////////
//
// OPTIONS.CPP : Program options
//
// Copyright (c) 2006-2019, Thomas A. Rieck
// All Rights Reserved
//

#include "common.h"
#include "options.h"
#include "util.h"

namespace Options {

const string NIL;

/////////////////////////////////////////////////////////////////////////////
class Options
{
    // Construction / Destruction
public:
    Options() = default;
    ~Options() = default;

    // Interface
    void put(const std::string& name, const std::string& value = NIL)
    {
        options[name] = value;
    }

    bool isoption(const std::string& name) const
    {
        return options.find(name) != options.end();
    }

    string value(const std::string& name) const
    {
        const auto it = options.begin();
        if (it == options.end())
            return NIL;

        return (*it).second;
    }

    // Implementation
private:
    using OptionMap = StringStringMap;
    OptionMap options;
};

Options g_Options;

/////////////////////////////////////////////////////////////////////////////
void options(int argc, char** argv)
{
    const char* pval;

    for (; argc; --argc, ++argv) {
        if (argv[0][0] != '-' && argv[0][1] != '-')
            continue;

        argv[0]++;
        argv[0]++;

        if ((pval = strchr(argv[0], '=')) != nullptr) {
            // option assignment
            auto name = string(argv[0], pval - argv[0]);
            name = trim(name);
            const auto value = trim(++pval);
            g_Options.put(name, value);
        } else {
            g_Options.put(argv[0]);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
bool isoption(const char* option)
{
    return g_Options.isoption(option);
}

/////////////////////////////////////////////////////////////////////////////
string value(const char* option)
{
    return g_Options.value(option);
}

} // Options
