#ifndef _DATA_H_
#define _DATA_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../inc/Tech.h"
#include "../inc/LibCell.h"

using namespace std;

class Data{

    private:
        int technologyCount;
        int libCellCount;
        vector<Tech> technologyList;

    public:
        Data();
        Data(char *filename);
};

#endif