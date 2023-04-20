#include "../inc/Data.h"

Pin::Pin(){

}

Pin::~Pin(){

}

LibCell::LibCell(){

}

LibCell::~LibCell(){
    delete []PinList;
}

Tech::Tech(){

}

Tech::~Tech(){
    delete []libCellList;
}

Data::Data(char *file_name){
    ifstream fin(file_name);
    string line;
    getline(fin, line);
    stringstream ss(line);
    
    ss >> line >> NumTechnologies;
    ss.str("");
    technologyList = new Tech[NumTechnologies];


    // Read technology
    for(int i = 0; i < NumTechnologies; i++){
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
}

Data::~Data(){
    delete []technologyList;
}

void Data::showData(){
    cout << "\nNumTechnologies <technologyCount>: " << NumTechnologies << endl << endl;
    for(int i = 0; i < NumTechnologies; i++){
        cout << "Tech <techName> <libCellCount>: " << i+1 << " " << technologyList[i].libCellCount << endl;
        for(int j = 1; j <= technologyList[i].libCellCount; j++){
            cout << "\t" << "LibCell <libCellName> <libCellSizeX> <libCellSizeY> <pinCount>: " << j << " " << technologyList[i].libCellList[j].libCellSizeX << " " << technologyList[i].libCellList[j].libCellSizeY << " " << technologyList[i].libCellList[j].pinCount << endl;
            for(int k = 1; k <= technologyList[i].libCellList[j].pinCount; k++){
                cout << "\t\tPin <pinName> <pinLocationX> <pinLocationY>: " << k << " " << technologyList[i].libCellList[j].PinList[k].pinLocationX << " " << technologyList[i].libCellList[j].PinList[k].pinLocationY << endl;
            }
            cout << endl;
        }
        cout << endl << endl;
    }
    cout << endl;
}