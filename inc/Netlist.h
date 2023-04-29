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
        int WhichDie;               //(0, 1) = (top die, bottom die)
        LibCell **LibCellptrs;      

        //LibCellptrs[0] = TopDieLibCellptr [pointer to the LibCell of the top die]
        //LibCellptrs[1] = BottomDieLibCellptr [pointer to the LibCell of the bottom die]
        //-> LibCellptrs[WhichDie] can access the description of the LibCell
        Instance();
        ~Instance();
};

class Net{
    public:
        int numPins;
        //Pin **PinPtrArray;  //array of pointer
        //[how to store the net??]
        Net();
        ~Net();
};

class NetList{
    public:
        int instanceCount;
        Instance *Instances;
        int netCount;
        Net *Nets;

        NetList(ifstream&);
        ~NetList();
};

#endif