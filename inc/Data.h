#ifndef _DATA_H_
#define _DATA_H_

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Pin{
    public:
        int pinLocationX;
        int pinLocationY;

        Pin();
        ~Pin();
};

class LibCell{
    public:
        bool isMacro;
        int libCellSizeX;
        int libCellSizeY;
        int pinCount;
        Pin *PinList;

        LibCell();
        ~LibCell();
        
};

class Tech{
    public:
        int libCellCount;
        LibCell *libCellList;

        Tech();
        ~Tech();

};

class Data{
    public:
        int NumTechnologies;
        Tech *technologyList;
        Data(char *filename);
        ~Data();

        void showData();
};

class Die{
    public:
        int lowerLeftX;
        int lowerLeftY;
        int upperRightX;
        int upperRightY;
        int MaxUtil;
        int startX;
        int startY;
        int rowLength;
        int rowHeight;
        int repeatCount;
        int techID;
        bool **placementState;  //1: occupied, 0: not-occupied
        
        Die();
        ~Die();
};

class HybridTerminal{
    public:
        int sizeX;
        int sizeY;
        int spacing;
        int cost;

        HybridTerminal();
};

class Instance{
    public:
        static int NumInstance;
        int libCellId;          //  MC "1"
        int techID;             //  After partition TechA or B
        LibCell &Info;          //  ref to technologyList[techID].libCellList[libCellId]

        Instance();
};


class Net{
    public:
        static int NumNet;
        int numPins;
        //no good idea, any thought?
};

class Netlist{
    public:
        static int NumNet;
        Net *Nets;                  //[TO-DO] figure out what is a better structure for Net?
        Instance *Instances;

        Netlist();
        ~Netlist();
};

#endif