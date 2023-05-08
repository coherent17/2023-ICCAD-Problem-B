#include "../inc/Data.h"

Data::Data(string filename){
    ifstream fin(filename);
    string line;
    getline(fin, line);
    stringstream ss(line);

    ss >> line >> technologyCount;
    ss.str("");

    for(int i = 0; i < technologyCount; i++){
        Tech tempTech;
        getline(fin, line);
        ss.str(line);
        ss >> line >> tempTech.techName >> tempTech.libCellCount;
        ss.str("");
        for(int j = 0; j < tempTech.libCellCount; j++){
            LibCell tempLibCell;
            getline(fin, line);
            ss.str(line);
            char isMacro;
            ss >> line >> isMacro >> tempLibCell.libCellName >> tempLibCell.libCellSizeX >> tempLibCell.libCellSizeY >> tempLibCell.pinCount;
            ss.str("");
            tempLibCell.isMacro = (isMacro == 'Y');
            for(int k = 0; k < tempLibCell.pinCount; k++){
                Pin tempPin;
                getline(fin, line);
                ss.str(line);
                ss >> line >> tempPin.pinName >> tempPin.pinLocationX >> tempPin.pinLocationY;
                ss.str("");
                tempLibCell.Pins.push_back(tempPin);
            }
            tempTech.LibCells.push_back(tempLibCell);
        }
        Techs.push_back(tempTech);
    }

    //start to read the die info
    getline(fin, line);
    ss.str("");
    getline(fin, line);
    ss.str(line);
    int upperRightX, upperRightY;
    ss >> line >> line >> line >> upperRightX >> upperRightY;
    ss.str("");
    TopDie.upperRightX = upperRightX;
    TopDie.upperRightY = upperRightY;
    BottomDie.upperRightX = upperRightX;
    BottomDie.upperRightY = upperRightY;
    getline(fin, line);
    getline(fin, line);
    ss.str(line);
    ss >> line >> TopDie.util;
    ss.str("");
    getline(fin, line);
    ss.str(line);
    ss >> line >> BottomDie.util;
    ss.str("");
    getline(fin, line);
    getline(fin, line);
    ss.str(line);
    ss >> line >> line >> line >> TopDie.rowLength >> TopDie.rowHeight >> TopDie.repeatCount;
    ss.str("");
    getline(fin, line);
    ss.str(line);
    ss >> line >> line >> line >> BottomDie.rowLength >> BottomDie.rowHeight >> BottomDie.repeatCount;
    ss.str("");
    getline(fin, line);
    getline(fin, line);
    ss.str(line);
    ss >> line >> TopDie.TechName;
    ss.str("");
    getline(fin, line);
    ss.str(line);
    ss >> line >> BottomDie.TechName;
    ss.str("");
    getline(fin, line);

    //start to read terminal info
    getline(fin, line);
    ss.str(line);
    ss >> line >> HybridTerminal.sizeX >> HybridTerminal.sizeY;
    ss.str("");
    getline(fin, line);
    ss.str(line);
    ss >> line >> HybridTerminal.spacing;
    ss.str("");
    getline(fin, line);
    ss.str(line);
    ss >> line >> HybridTerminal.val;
    ss.str("");
    getline(fin, line);

    //start to read Instance info
    getline(fin, line);
    ss.str(line);
    ss >> line >> instanceCount;
    ss.str("");
    for(int i = 0; i < instanceCount; i++){
        Instance temp;
        getline(fin, line);
        ss.str(line);
        ss >> line >> temp.instName >> temp.libCellName;
        ss.str("");
        Instances.push_back(temp);
    }
    getline(fin, line);

    //start to read Nets
    getline(fin, line);
    ss.str(line);
    ss >> line >> netCount;
    ss.str("");
    for(int i = 0; i < netCount; i++){
        Net temp;
        getline(fin, line);
        ss.str(line);
        ss >> line >> temp.netName >> temp.numPins;
        ss.str("");
        for(int j = 0; j < temp.numPins; j++){
            getline(fin, line);
            replace(line.begin(), line.end(), '/', ' ');
            ss.str(line);
            string tempinstName, templibPinName;
            ss >> line >> tempinstName >> templibPinName;
            temp.instName.push_back(tempinstName);
            temp.libPinName.push_back(templibPinName);
        }
        Nets.push_back(temp);
    }

    fin.close();
}

Data::~Data(){

}

void Data::Display(){
    cout << "\nNumTechnologies <technologyCount>: " << technologyCount << endl << endl;
    for(int i = 0; i < technologyCount; i++){
        cout << "Tech <techName> <libCellCount>: " << Techs[i].techName << " " << Techs[i].libCellCount << endl;
        for(int j = 0; j < Techs[i].libCellCount; j++){
            cout << "\t" << "LibCell <isMacro> <libCellName> <libCellSizeX> <libCellSizeY> <pinCount>: " << (Techs[i].LibCells[j].isMacro == 1 ? "Y " : "N ") << Techs[i].LibCells[j].libCellName << " " << Techs[i].LibCells[j].libCellSizeX << " " << Techs[i].LibCells[j].libCellSizeY << " " << Techs[i].LibCells[j].pinCount << endl;
            for(int k = 0; k < Techs[i].LibCells[j].pinCount; k++){
                cout << "\t\tPin <pinName> <pinLocationX> <pinLocationY>: " << Techs[i].LibCells[j].Pins[k].pinName << " " << Techs[i].LibCells[j].Pins[k].pinLocationX << " " << Techs[i].LibCells[j].Pins[k].pinLocationY << endl;
            }
            cout << endl;
        }
        cout << endl << endl;
    }
    cout << endl;

    cout << "TopDie:" << endl;
    cout << "\tDieSize <lowerLeftX> <lowerLeftY> <upperRightX> <upperRightY>: 0 0 " << TopDie.upperRightX << " " << TopDie.upperRightY << endl;
    cout << "\tMaxUtil: " << TopDie.util << endl;
    cout << "\tDieRows <startX> <startY> <rowLength> <rowHeight> <repeatCount>: 0 0 " << TopDie.rowLength << " " << TopDie.rowHeight << " " << TopDie.repeatCount << endl;
    cout << "\tTechName: " << TopDie.TechName << endl << endl;

    cout << "BottomDie:" << endl;
    cout << "\tDieSize <lowerLeftX> <lowerLeftY> <upperRightX> <upperRightY>: 0 0 " << BottomDie.upperRightX << " " << BottomDie.upperRightY << endl;
    cout << "\tMaxUtil: " << BottomDie.util << endl;
    cout << "\tDieRows <startX> <startY> <rowLength> <rowHeight> <repeatCount>: 0 0 " << BottomDie.rowLength << " " << BottomDie.rowHeight << " " << BottomDie.repeatCount << endl;
    cout << "\tTechName: " << BottomDie.TechName << endl << endl;

    cout << "HybrodTerminal: " << endl;
    cout << "\tTerminalSize <sizeX> <sizeY>: " << HybridTerminal.sizeX << " " << HybridTerminal.sizeY << endl;
    cout << "\tTerminalSpacing <spacing>: " << HybridTerminal.spacing << endl;
    cout << "\tTerminalCost <val>: " << HybridTerminal.val << endl << endl;

    cout << "Instances: " << instanceCount << endl;
    for(int i = 0; i < instanceCount; i++){
        cout << "Inst " << Instances[i].instName << " " << Instances[i].libCellName << endl;
    }
    cout << endl;

    cout << "Nets: " << netCount << endl;
    for(int i = 0; i < netCount; i++){
        cout << "Net " <<  Nets[i].netName << " " <<  Nets[i].numPins << endl;
        for(int j = 0; j < Nets[i].numPins; j++){
            cout << "\tPin " << Nets[i].instName[j] << "/" << Nets[i].libPinName[j] << endl;
        }
        cout << endl;
    }
}



void Data::GeneratePartitionGraph(){
    FILE *shmetisInput = fopen("Netlist.hgr", "w");
	fprintf(shmetisInput, "%d %d\n", netCount, instanceCount);

    for(int i = 0; i < netCount; i++){
        for(int j = 0; j < Nets[i].numPins; j++){
            string temp = Nets[i].instName[j];
            replace(temp.begin(), temp.end(), 'C', ' ');
            fprintf(shmetisInput, "%d ", stoi(temp));
        }
        fprintf(shmetisInput, "\n");
    }
    fclose(shmetisInput);
}


//helper functions used in PartitionUntilFindSolution
void Partition(string input_filename, int UBfactor, string output_filename){
    system("chmod +x lib/hmetis/shmetis");
    string command = "./lib/hmetis/shmetis " + input_filename + " 2 " + to_string(UBfactor) + " > " + output_filename;
    system(command.c_str());
}

void Data::PartitionUntilFindSolution(){
    string input_filename = "Netlist.hgr";
    vector<string> output_filenames = {"1.out", "2.out", "3.out", "4.out"};

    vector<thread> threads;
    for (int i = 0; i < 4; i++) {
        threads.emplace_back(Partition, input_filename, 5 , output_filenames[i]);
    }
    for (auto& thread : threads) {
        thread.join();
    }
}