#ifndef DATA_H_
#define DATA_H_

#include<bits/stdc++.h>
using namespace std;

//start of Tech Data structure//
class Pin{
    public:
        string pinName;
        int pinLocationX;
        int pinLocationY;
};

class LibCell{
    public:
        bool isMacro;
        string libCellName;
        int libCellSizeX;
        int libCellSizeY;
        int pinCount;
        vector<Pin> Pins;
};

class Tech{
    public:
        string techName;
        int libCellCount;
        vector<LibCell> LibCells;
};

//end of Tech Data structure//

//start of Die Data structure//
class Die{
    public:
        int upperRightX;
        int upperRightY;
        int util;
        int rowLength;
        int rowHeight;
        int repeatCount;
        string TechName;
};
//end of Die Data structure//


//start of Terminal Data structure//
class Terminal{
    public:
        int sizeX;
        int sizeY;
        int spacing;
        int val;
};
//end of Terminal Data structure//


//start of Netlist Data structure//
class Instance{
    public:
        string instName;
        string libCellName;
};

class Net{
    public:
        string netName;
        int numPins;
        vector<string> instName;
        vector<string> libPinName;
};

//end of Netlist Data structure//

class Data{
    public:
        //tech data structure
        int technologyCount;
        vector<Tech> Techs;

        //Die data structure
        Die TopDie;
        Die BottomDie;

        //Hybrid-Bonding Terminal data structure
        Terminal HybridTerminal;

        //Netlist Data Structure
        int instanceCount;
        vector<Instance> Instances;
        int netCount;
        vector<Net> Nets;

        //constructor & destructor
        Data(string filename);
        ~Data();

        //show the parser result
        void Display();
    
        //partition
        void GeneratePartitionGraph();
        void PartitionUntilFindSolution();

};

#endif