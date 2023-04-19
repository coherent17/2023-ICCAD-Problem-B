#include "../inc/Data.h"

Data::Data(char *file_name){
    ifstream fin(file_name);
    string line;
    getline(fin, line);
    stringstream ss(line);
    
    ss >> line >> this->technologyCount;
    ss.str("");


    this->technologyList = vector<Tech> (this->technologyCount);
    // Read technology
    for(int i = 0; i < this->technologyCount;i++){
        getline(fin, line);
        ss.str(line);
        ss >> line >> line >> this->libCellCount;
        // this->technologyList[i].libCellList = vector<LibCell> (this->libCellCount+1);
        ss.str("");
        this->technologyList[i].libCellList.push_back(libCell());
        // Read cells of tech
        for(int j = 1 ;j <= this->libCellCount; j++){
            getline(fin, line);
            int x, y, c;
            char isMacro;
            ss.str(line);
            ss>>line>>isMacro>>line>>x>>y>>c;
            /*
            this->technologyList[i].libCellList[j].isMacro = (isMacro == 'Y');
            this->technologyList[i].libCellList[j].libCellSizeX = x;
            this->technologyList[i].libCellList[j].libCellSizeY = y;
            this->technologyList[i].libCellList[j].pinCount = c;
            */
            // Read pin for this cell
            vector<Pin> curPinList(c+1);
            for(int k=1;k<=c;k++){
                ss.str("");
                getline(fin, line);
                ss.str(line);
                ss>>line>>line>>curPinList[k].pinLocationX>>curPinList[k].pinLocationY;
            
            }
            libCell curCell(curPinList, isMacro=='y', x, y, c);
            this->technologyList[i].libCellList.push_back(curCell);
        }
    }


}