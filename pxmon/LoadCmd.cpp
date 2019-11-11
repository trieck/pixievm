/////////////////////////////////////////////////////////////////////////////
//
// LOADCMD.CPP : Monitor load command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "LoadCmd.h"
#include <memory.h>
#include <sys/stat.h>

/////////////////////////////////////////////////////////////////////////////
void LoadCmd::exec(const stringvec& v)
{
    if (v.size() < 1) {
        cerr << "? l file" << endl;
        return;
    }

    auto filename = v[0];

    struct stat buf;
    const auto n = stat(filename.c_str(), &buf);
    if (n) {
        fprintf(stderr, "unable to stat file \"%s\".\n", filename.c_str());
        return;
    }

    ifstream ifs;
    ifs.open(filename.c_str(), ifstream::in | ifstream::binary);
    if (!ifs.is_open()) {
        fprintf(stderr, "unable to open file \"%s\".\n", filename.c_str());
        return;
    }

    word start;
    ifs.read((char*)&start, sizeof(word));
    if (ifs.bad()) {
        fprintf(stderr, "unable to read from file \"%s\".\n",
                filename.c_str());
        return;
    }

    if (!Memory::instance().load(ifs, start, static_cast<word>(buf.st_size - sizeof(word)))) {
        fprintf(stderr, "unable to load file \"%s\".\n",
                filename.c_str());
    }

    printf("file \"%s\" loaded @ $%.4x-$%.4x.\n", filename.c_str(),
           start, static_cast<word>(start + (buf.st_size - sizeof(word)) - 1));
}
