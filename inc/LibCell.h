#ifndef _LIBCELL_H_
#define _LIBCELL_H_

#include "../inc/Pin.h"
#include <vector>

using namespace std;

class libCell{
    public:
        libCell(vector<Pin> &, bool, int, int, int);
        libCell();
        vector<Pin> PinList;
        bool isMacro;
        int libCellSizeX, libCellSizeY, pinCount;
};

#endif