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

#endif