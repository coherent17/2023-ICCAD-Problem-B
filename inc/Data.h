#ifndef DATA_H_
#define DATA_H_

#include<bits/stdc++.h>
using namespace std;

#define PARTITION_TOP 0
#define PARTITION_BOTTOM 1

//the fmt used in create shmetis input file
#define WEIGHTED_GRAPH_FMT 10

//print the things
#define DEBUG 1

//if 0 print important result of testcase only
#define DETAIL_DISPLAY 0

//different mode used in partition the graph
#define WEIGHTED                0b00000001
#define FIX_PARTITION           0b00000010
#define GREEDY_FIX              0b00000100
#define STD_CELL_RANDOM_ASSIGN  0b00001000

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

    // Placement
    // Bottom left coordinate
    int X, Y;
    string orientation;
};

struct Net{
    string netName;
    int numPins;
    vector<string> instName;
    vector<string> libPinName;


    // Terminal Placement
    bool hasTerminal;
    int HBlocationX;
    int HBlocationY;
};


class Data{
    private:
        //helper function used in constructor
        void readTechnologyInfo(ifstream&);
        void readDieInfo(ifstream&);
        void readTerminalInfo(ifstream&);
        void readInstanceInfo(ifstream&);
        void readNetlistInfo(ifstream&);

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
        void Partition(string input_filename, bool *isValidPartition, int8_t option);
        void GenerateFixPart(int8_t option);
        void PartitionUntilFindSolution();
        void showPartitionResult();
        bool Evaluation(string);
        void LoadPartition();
        void legalizePartion();

        // Placement
        void Placement();
        void makeNodesFile(string, int);
        void makeNetsFile(string, int);
        void makeWtsFile(string, int);
        void makePlFile(string, int);
        void makeSclFile(string, int);
        void loadPlacementResult(string, int);
        void showPlacementResult();
        void GeedyPlacement(int);

        // Terminal
        int NumTerminals;
        vector< vector<int> > terminalPlacementState;
        void terminalPlacement();
        bool needTerminal(int);
        void getNetExtreme(int, int&, int&, int&, int&);
        bool isValidTerminalPlacement(int, int, int ,int ,int );
        void fillTerminalPlacement(int ,int ,int ,int ,int);

        // Output
        void output(char *);
        string getOrientation(int);
};

#endif