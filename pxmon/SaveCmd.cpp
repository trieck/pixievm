/////////////////////////////////////////////////////////////////////////////
//
// SAVECMD.CPP : Monitor save command
//
// Copyright (c) 2006-2019, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "SaveCmd.h"
#include <memory.h>

/////////////////////////////////////////////////////////////////////////////
void SaveCmd::exec(const stringvec& v)
{
    word start, end;
    if (v.size() < 3) {
        cerr << "? s range file" << endl;
        return;
    }
    auto n = sscanf(v[0].c_str(), "%hx", &start);
    if (n != 1) {
        cerr << "? s range file" << endl;
        return;
    }
    n = sscanf(v[1].c_str(), "%hx", &end);
    if (n != 1) {
        cerr << "? s range file" << endl;
        return;
    }

    auto filename = v[2];
    ofstream ofs;
    ofs.open(filename.c_str(), ofstream::out | ofstream::binary);
    if (!ofs.is_open()) {
        fprintf(stderr, "unable to open file \"%s\".\n",
                filename.c_str());
        return;
    }

    ofs.write((char*)&start, sizeof(word));
    if (ofs.bad()) {
        fprintf(stderr, "unable to write to file \"%s\".\n",
                filename.c_str());
        return;
    }

    if (!Memory::instance().save(ofs, start, (end - start) + 1)) {
        fprintf(stderr, "unable to save to file \"%s\".\n",
                filename.c_str());
    }
}
