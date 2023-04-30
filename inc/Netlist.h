#ifndef _NETLIST_H_
#define _NETLIST_H_

#include "Technology.h"

class Terminal{
    public:
        int sizeX;
        int sizeY;
        int spacing;
        int cost;

        Terminal(ifstream& fin);
        friend ostream& operator<<(ostream&, const Terminal&);
};

class Instance{
    public:
        LibCell *LibCellptr;      

        Instance();
        ~Instance();
};

#endif