#ifndef _NETLIST_H_
#define _NETLIST_H_

#include "Technology.h"
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

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
        int LibCellIdx;
        Instance();
        ~Instance();

        friend void InstanceParser(ifstream& fin, Instance **instances, int *NumInstances);
};

class Net{
    public:
        int numPins;
        int *LibCellIdx;
        int *PinIdx;

        Net();
        ~Net();

};

class Netlist{
    public:
        Net *Nets;
        int NumNets;
        Netlist(ifstream& fin);
        ~Netlist();
        void showNetlist();
};

#endif