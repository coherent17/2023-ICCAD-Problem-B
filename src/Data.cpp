#include "../inc/Data.h"

void Data::readTechnologyInfo(ifstream& fin){
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
            tempLibCell.libCellArea = tempLibCell.libCellSizeX * tempLibCell.libCellSizeY;
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
}

void Data::readDieInfo(ifstream& fin){
        //start to read the die info
    string line;
    stringstream ss;
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
    for(size_t i = 0; i < Techs.size(); i++){
        if(Techs[i].techName == TopDie.TechName){
            TopDie.DieTech = &Techs[i];
            break;
        }
    }
    
    getline(fin, line);
    ss.str(line);
    ss >> line >> BottomDie.TechName;
    ss.str("");
    for(size_t i = 0; i < Techs.size(); i++){
        if(Techs[i].techName == BottomDie.TechName){
            BottomDie.DieTech = &Techs[i];
            break;
        }
    }
    getline(fin, line);
}

void Data::readTerminalInfo(ifstream& fin){
    string line;
    stringstream ss;
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
}

void Data::readInstanceInfo(ifstream& fin){
    string line;
    stringstream ss;
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
        string n1 = temp.instName;
        replace(n1.begin(), n1.end(), 'C', ' ');
        stringstream ssn1(n1);
        ssn1 >> temp.instName_int;
        
        string n2 = temp.libCellName;
        replace(n2.begin(), n2.end(), 'M', ' ');
        replace(n2.begin(), n2.end(), 'C', ' ');
        stringstream ssn2(n2);
        ssn2 >> temp.libCellName_int;
        Instances.push_back(temp);
    }
    getline(fin, line);
}

void Data::readNetlistInfo(ifstream& fin){
    string line;
    stringstream ss;
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
}


Data::Data(string filename){
    ifstream fin(filename);
    readTechnologyInfo(fin);
    readDieInfo(fin);
    readTerminalInfo(fin);
    readInstanceInfo(fin);
    readNetlistInfo(fin);
    fin.close();
}

Data::~Data(){

}

void Data::Display(){
    cout << "\nNumTechnologies <technologyCount>: " << technologyCount << endl << endl;
    for(int i = 0; i < technologyCount; i++){
        cout << "Tech <techName> <libCellCount>: " << Techs[i].techName << " " << Techs[i].libCellCount << endl;
        for(int j = 0; j < Techs[i].libCellCount; j++){
            cout << "\t" << "LibCell <isMacro> <libCellName> <libCellSizeX> <libCellSizeY> <libCellArea> <pinCount>: " << (Techs[i].LibCells[j].isMacro == 1 ? "Y " : "N ") << Techs[i].LibCells[j].libCellName << " " << Techs[i].LibCells[j].libCellSizeX << " " << Techs[i].LibCells[j].libCellSizeY << " " << Techs[i].LibCells[j].libCellArea << " " << Techs[i].LibCells[j].pinCount << endl;
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


//weighted hyperedge
// void Data::GeneratePartitionGraph(){
//     FILE *shmetisInput = fopen("Netlist.hgr", "w");
// 	fprintf(shmetisInput, "%d %d %d\n", netCount, instanceCount, 1);

//     for(int i = 0; i < netCount; i++){
//         for(int j = 0; j < Nets[i].numPins; j++){
//             string temp = Nets[i].instName[j];
//             replace(temp.begin(), temp.end(), 'C', ' ');
//             fprintf(shmetisInput, "%d ", stoi(temp));
//         }
//         fprintf(shmetisInput, "%d\n", Nets[i].numPins);
//     }
//     fclose(shmetisInput);
// }

//weighted vertices
void Data::GeneratePartitionGraph(){
    FILE *shmetisInput = fopen("Netlist.hgr", "w");
	fprintf(shmetisInput, "%d %d %d\n", netCount, instanceCount, 10);

    for(int i = 0; i < netCount; i++){
        for(int j = 0; j < Nets[i].numPins; j++){
            string temp = Nets[i].instName[j];
            replace(temp.begin(), temp.end(), 'C', ' ');
            fprintf(shmetisInput, "%d ", stoi(temp));
        }
        fprintf(shmetisInput, "\n");
    }
    for(int i = 0; i < instanceCount; i++){
        fprintf(shmetisInput, "%d\n", Techs[0].LibCells[Instances[i].libCellName_int - 1].libCellArea);
    }
    fclose(shmetisInput);
}


//unweighted graph
// void Data::GeneratePartitionGraph(){
//     FILE *shmetisInput = fopen("Netlist.hgr", "w");
// 	fprintf(shmetisInput, "%d %d\n", netCount, instanceCount);

//     for(int i = 0; i < netCount; i++){
//         for(int j = 0; j < Nets[i].numPins; j++){
//             string temp = Nets[i].instName[j];
//             replace(temp.begin(), temp.end(), 'C', ' ');
//             fprintf(shmetisInput, "%d ", stoi(temp));
//         }
//         fprintf(shmetisInput, "\n");
//     }
//     fclose(shmetisInput);
// }

bool Data::Evaluation(string filename){
    bool ret = true;
    unsigned long long int TopDieMaxSize = TopDie.util * TopDie.rowLength / 100 * TopDie.rowHeight * TopDie.repeatCount;
    unsigned long long int BottomDieMaxSize = BottomDie.util * BottomDie.rowLength / 100 * BottomDie.rowHeight * BottomDie.repeatCount;
    unsigned long long int TopDieArea = 0;
    unsigned long long int BottomDieArea = 0;

    ifstream fin(filename);

    int partition;
    for(int i = 0; i < instanceCount; i++){
        fin >> partition;
        if(partition == PARTITION_TOP){
            TopDieArea += TopDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea;
            if(TopDieArea > TopDieMaxSize) ret = false;
        }
        else{
            BottomDieArea += BottomDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea;
            if(BottomDieArea > BottomDieMaxSize) ret = false;
        }
    }
    fin.close();
    cout << "----------------------------------------------------" << endl;
    cout << "TopDie Partition Summary: (" << TopDieArea << "/" <<  TopDieMaxSize << ") " << double(TopDieArea) / double(TopDie.rowLength * TopDie.rowHeight * TopDie.repeatCount) * 100 << endl;
    cout << "BottomDie Partition Summary: (" << BottomDieArea << "/" <<  BottomDieMaxSize << ") " << double(BottomDieArea) / double(BottomDie.rowLength  * BottomDie.rowHeight * BottomDie.repeatCount) * 100 << endl;
    cout << "----------------------------------------------------" << endl;
    return ret;
}

void Data::Partition(string input_filename, int UBfactor, bool *isValidPartition){
    system("chmod +x lib/hmetis/shmetis");
    string command = "./lib/hmetis/shmetis " + input_filename + " 2 " + to_string(UBfactor) + " > " + "/dev/null";
    cout << command << endl;
    system(command.c_str());
    *isValidPartition = Evaluation(input_filename + ".part.2");

    
    if(*isValidPartition){
        ifstream fin(input_filename + ".part.2");
        int partition;
        for(int i = 0; i < instanceCount; i++){
            fin >> partition;
            PartitionResult.push_back(partition);
        }
    }
}

void Data::PartitionUntilFindSolution(){
    string input_filename = "Netlist.hgr";
    bool isValidPartition = false;
    //do 10 times balance partition
    for(int i = 0; i < 10; i++){
        Partition(input_filename, 5, &isValidPartition);
        if(isValidPartition) break;
    }

    if(!isValidPartition){
        for(int i = 0; i < 30; i++){
            int randomOffset = rand() % 3 - 1;  //generate the random number between -2 ~ 2
            Partition(input_filename, 5 + randomOffset, &isValidPartition);
            if(isValidPartition) break;
        }
    }

}

//helper functions used in PartitionUntilFindSolution
// void Partition(string input_filename, int UBfactor, Data *data, bool *ret){
//     system("chmod +x lib/hmetis/shmetis");
//     string command = "./lib/hmetis/shmetis " + input_filename + " 2 " + to_string(UBfactor) + " > " + "/dev/null";
//     system(command.c_str());
//     cout<<"finish partition"<<endl;
//     *ret = data->Evaluation(input_filename + ".part.2");
// }

// void Data::PartitionUntilFindSolution(){
//     string input_filename = "Netlist.hgr";
//     vector<string> input_filenames = {"1.in", "2.in", "3.in", "4.in"};
//     vector<string> output_filenames = {"1.out", "2.out", "3.out", "4.out"};

//     for (int i = 0; i < 4; i++) {
//         string command = "cp " + input_filename + " " + input_filenames[i];
//         system(command.c_str());
//     } 
//     bool checkBox[4] = {0};
//     while(1){
//         vector<thread> threads;
//         // vector<bool> checkBox(4, false);
//         for (int i = 0; i < 4; i++) {
//             int UBfactor = 5;
//             threads.emplace_back(Partition, input_filenames[i], UBfactor, output_filenames[i], this, &checkBox[i]);
//         }
//         for (auto& thread : threads) {
//             thread.join();
//         }


//         if(checkBox[0] || checkBox[1] || checkBox[2] || checkBox[3])
//             break;
//     }

//     //parse the correct partition
//     int idx;
//     for(int i = 0; i < 4; i++){
//         if(checkBox[i]){
//             idx = i;
//             break;
//         }
//     }

//     // read file
//     ifstream fin(input_filenames[idx] + ".part.2");
    
//     int cur;
//     int cur_idx = 0;
//     while(fin >> cur){
        
//         if(cur){
//             Instances[cur_idx].LibCellptr = &TopDie.DieTech->LibCells[Instances[cur_idx].libCellName_int - 1];
//         }
//         else{
//             Instances[cur_idx].LibCellptr = &BottomDie.DieTech->LibCells[Instances[cur_idx].libCellName_int - 1];   
//         }
//         PartitionResult.push_back(cur);
//     }
//     fin.close();
// }

void Data::showPartitionResult(){
    for(size_t i = 0; i < PartitionResult.size(); i++){
        cout << PartitionResult[i] << endl;
    }
}