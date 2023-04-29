#include "../inc/Die.h"

Die::Die(){

}

Die::~Die(){
    for(int i = 0; i < rowHeight * repeatCount; i++){
        delete []placementState[i];
    }
    delete []placementState;
}


void DieParser(ifstream &fin, Die *Dies, Tech *TAptr, Tech *TBptr){
    string line;
    getline(fin, line);
    stringstream ss(line);
    int upperRightX, upperRightY;
    ss >> line >> line >> line >> upperRightX >> upperRightY;
    Dies[0].upperRightX = upperRightX;
    Dies[0].upperRightY = upperRightY;
    Dies[1].upperRightX = upperRightX;
    Dies[1].upperRightY = upperRightY;
    ss.str("");

    getline(fin, line);

    getline(fin, line);
    ss.str(line);
    ss >> line >>  Dies[0].util;
    ss.str("");

    getline(fin, line);
    ss.str(line);
    ss >> line >>  Dies[1].util;
    ss.str("");

    getline(fin, line);

    getline(fin, line);
    ss.str(line);
    ss >> line >> line >> line >> Dies[0].rowLength >> Dies[0].rowHeight >> Dies[0].repeatCount;
    ss.str("");

    getline(fin, line);
    ss.str(line);
    ss >> line >> line >> line >> Dies[1].rowLength >> Dies[1].rowHeight >> Dies[1].repeatCount;
    ss.str("");

    getline(fin, line);

    //read tech
    string temp;
    getline(fin, line);
    ss.str(line);
    ss >> line >> temp;
    ss.str("");
    Dies[0].techptr = (temp == "TA") ? TAptr : TBptr;

    getline(fin, line);
    ss.str(line);
    ss >> line >> temp;
    ss.str("");
    Dies[1].techptr = (temp == "TA") ? TAptr : TBptr;

    //initialize the placement state
    Dies[0].placementState = new bool *[Dies[0].rowHeight * Dies[0].repeatCount];
    for(int i = 0; i < Dies[0].rowHeight * Dies[0].repeatCount; i++){
        Dies[0].placementState[i] = new bool[Dies[0].rowLength];
    }

    for(int i = 0; i < Dies[0].rowHeight * Dies[0].repeatCount; i++){
        for(int j = 0; j < Dies[0].rowLength; j++){
            Dies[0].placementState[i][j] = UNOCCUPIED;
        }
    }

    Dies[1].placementState = new bool *[Dies[1].rowHeight * Dies[1].repeatCount];
    for(int i = 0; i < Dies[1].rowHeight * Dies[1].repeatCount; i++){
        Dies[1].placementState[i] = new bool[Dies[1].rowLength];
    }

    for(int i = 0; i < Dies[1].rowHeight * Dies[1].repeatCount; i++){
        for(int j = 0; j < Dies[1].rowLength; j++){
            Dies[1].placementState[i][j] = UNOCCUPIED;
        }
    }
    getline(fin, line);
}

ostream& operator<<(ostream& out, const Die &D){
    out << "\tDieSize <lowerLeftX> <lowerLeftY> <upperRightX> <upperRightY>: 0 0 " << D.upperRightX << " " << D.upperRightY << endl;
    out << "\tMaxUtil: " << D.util << endl;
    out << "\tDieRows <startX> <startY> <rowLength> <rowHeight> <repeatCount>: 0 0 " << D.rowLength << " " << D.rowHeight << " " << D.repeatCount << endl;
    out << "\tTechInfo: " << endl;
    for(int j = 1; j <= D.techptr->libCellCount; j++){
        out << "\t\t" << "LibCell <isMacro> <libCellName> <libCellSizeX> <libCellSizeY> <pinCount>: " << (D.techptr->libCellList[j].isMacro == 1 ? "Y" : "N") << " MC" << j << " " << D.techptr->libCellList[j].libCellSizeX << " " << D.techptr->libCellList[j].libCellSizeY << " " << D.techptr->libCellList[j].pinCount << endl;
        for(int k = 1; k <= D.techptr->libCellList[j].pinCount; k++){
            out << "\t\t\tPin <pinName> <pinLocationX> <pinLocationY>: P" << k << " " << D.techptr->libCellList[j].PinList[k].pinLocationX << " " << D.techptr->libCellList[j].PinList[k].pinLocationY << endl;
        }
        out << endl;
    }
    return out;
}