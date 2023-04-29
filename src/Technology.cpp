#include "../inc/Technology.h"

Pin::Pin(){
    pinLocationX = 0;
    pinLocationY = 0;
}

Pin::~Pin(){

}

LibCell::LibCell(){
    isMacro = false;
    libCellSizeX = 0;
    libCellSizeY = 0;
    pinCount = 0;
    PinList = nullptr;
}

LibCell::~LibCell(){
    delete []PinList;
}

Tech::Tech(){

}

Tech::~Tech(){
    delete []libCellList;
}

Technology::Technology(ifstream &fin){
    string line;
    getline(fin, line);
    stringstream ss(line);
    
    ss >> line >> technologyCount;
    ss.str("");
    technologyList = new Tech[technologyCount];


    // Read technology
    for(int i = 0; i < technologyCount; i++){
        getline(fin, line);
        ss.str(line);
        ss >> line >> line >> technologyList[i].libCellCount;
        ss.str("");
        technologyList[i].libCellList = new LibCell[technologyList[i].libCellCount + 1];

        // Read LibCells of tech
        for(int j = 1 ;j <= technologyList[i].libCellCount; j++){
            getline(fin, line);
            int sizeX, sizeY, pinCount;
            char isMacro;
            ss.str(line);
            ss >> line >> isMacro >> line >> sizeX >> sizeY >> pinCount;
            technologyList[i].libCellList[j].isMacro = (isMacro == 'Y');
            technologyList[i].libCellList[j].libCellSizeX = sizeX;
            technologyList[i].libCellList[j].libCellSizeY = sizeY;
            technologyList[i].libCellList[j].pinCount = pinCount;
            technologyList[i].libCellList[j].PinList = new Pin[pinCount + 1];

            // Read pin for this LibCell
            for(int k = 1; k <= pinCount; k++){
                ss.str("");
                getline(fin, line);
                ss.str(line);
                ss >> line >> line >> technologyList[i].libCellList[j].PinList[k].pinLocationX >> technologyList[i].libCellList[j].PinList[k].pinLocationY;
            }
        }
    }
    getline(fin, line);
}

Technology::~Technology(){
    delete []technologyList;
}

void Technology::showData(){
    cout << "\nNumTechnologies <technologyCount>: " << technologyCount << endl << endl;
    for(int i = 0; i < technologyCount; i++){
        cout << "Tech <techName> <libCellCount>: " << (i == 0 ? "TA" : "TB") << " " << technologyList[i].libCellCount << endl;
        for(int j = 1; j <= technologyList[i].libCellCount; j++){
            cout << "\t" << "LibCell <isMacro> <libCellName> <libCellSizeX> <libCellSizeY> <pinCount>: " << (technologyList[i].libCellList[j].isMacro == 1 ? "Y" : "N") << " MC" << j << " " << technologyList[i].libCellList[j].libCellSizeX << " " << technologyList[i].libCellList[j].libCellSizeY << " " << technologyList[i].libCellList[j].pinCount << endl;
            for(int k = 1; k <= technologyList[i].libCellList[j].pinCount; k++){
                cout << "\t\tPin <pinName> <pinLocationX> <pinLocationY>: P" << k << " " << technologyList[i].libCellList[j].PinList[k].pinLocationX << " " << technologyList[i].libCellList[j].PinList[k].pinLocationY << endl;
            }
            cout << endl;
        }
        cout << endl << endl;
    }
    cout << endl;
}