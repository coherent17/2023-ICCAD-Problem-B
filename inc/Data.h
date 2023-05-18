#ifndef DATA_H_
#define DATA_H_

#include<bits/stdc++.h>
using namespace std;

#define PARTITION_TOP 0
#define PARTITION_BOTTOM 1

struct Pin{
    string pinName;
    int pinLocationX;
    int pinLocationY;
};

struct LibCell{
    bool isMacro;
    string libCellName;
    int libCellSizeX;
    int libCellSizeY;
    int libCellArea;
    int pinCount;
    vector<Pin> Pins;
};

struct Tech{
    string techName;
    int libCellCount;
    vector<LibCell> LibCells;
};

struct Die{
    int upperRightX;
    int upperRightY;
    int util;
    int rowLength;
    int rowHeight;
    int repeatCount;
    string TechName;
    Tech *DieTech;
};

struct Terminal{
    int sizeX;
    int sizeY;
    int spacing;
    int val;
};

struct Instance{
    string instName;
    int instName_int;
    string libCellName;
    int libCellName_int;
    LibCell *LibCellptr;
};

struct Net{
    string netName;
    int numPins;
    vector<string> instName;
    vector<string> libPinName;
};


class Data{
    private:
        //helper function used in constructor
        void readTechnologyInfo(ifstream&);
        void readDieInfo(ifstream&);
        void readTerminalInfo(ifstream&);
        void readInstanceInfo(ifstream&);
        void readNetlistInfo(ifstream&);

        //helper function used in partition
        void Partition(string input_filename, int UBfactor, bool *isValidPartition);
        

    public:
        //raw data
        int technologyCount;
        vector<Tech> Techs;
        Die TopDie;
        Die BottomDie;
        Terminal HybridTerminal;
        int instanceCount;
        vector<Instance> Instances;
        int netCount;
        vector<Net> Nets;

        vector<bool> PartitionResult;

        //constructor & destructor
        Data(string);
        ~Data();

        //show the parser result
        void Display();
    
        //partition
        
        void GeneratePartitionGraph();
        void GenerateFixPart();
        void PartitionUntilFindSolution();
        void showPartitionResult();
        bool Evaluation(string);
};

#endif