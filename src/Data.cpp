#include "../inc/Data.h"

void Data::readTechnologyInfo(ifstream& fin){
    string line;
    getline(fin, line);
    stringstream ss(line);

    ss >> line >> technologyCount;
    ss.clear();

    for(int i = 0; i < technologyCount; i++){
        Tech tempTech;
        getline(fin, line);
        ss.str(line);
        ss >> line >> tempTech.techName >> tempTech.libCellCount;
        ss.clear();
        for(int j = 0; j < tempTech.libCellCount; j++){
            LibCell tempLibCell;
            getline(fin, line);
            ss.str(line);
            char isMacro;
            ss >> line >> isMacro >> tempLibCell.libCellName >> tempLibCell.libCellSizeX >> tempLibCell.libCellSizeY >> tempLibCell.pinCount;
            tempLibCell.libCellArea = tempLibCell.libCellSizeX * tempLibCell.libCellSizeY;
            ss.clear();
            tempLibCell.isMacro = (isMacro == 'Y');
            for(int k = 0; k < tempLibCell.pinCount; k++){
                Pin tempPin;
                getline(fin, line);
                ss.str(line);
                ss >> line >> tempPin.pinName >> tempPin.pinLocationX >> tempPin.pinLocationY;
                ss.clear();
                tempLibCell.Pins.push_back(tempPin);
            }
            tempTech.LibCells.push_back(tempLibCell);
        }
        Techs.push_back(tempTech);
    }
    getline(fin, line);
}

void Data::readDieInfo(ifstream& fin){
    //start to read the die info
    string line;
    stringstream ss;
    getline(fin, line);
    ss.str(line);
    int upperRightX, upperRightY;
    ss >> line >> line >> line >> upperRightX >> upperRightY;
    ss.clear();
    TopDie.upperRightX = upperRightX;
    TopDie.upperRightY = upperRightY;
    BottomDie.upperRightX = upperRightX;
    BottomDie.upperRightY = upperRightY;
    getline(fin, line);
    getline(fin, line);
    ss.str(line);
    int UtilTop, UtilBottom;
    ss >> line >> UtilTop;
    ss.clear();
    ss.clear();
    TopDie.util = UtilTop;
    getline(fin, line);

    ss.str(line);
    ss >> line >> UtilBottom;
    BottomDie.util = UtilBottom;
    ss.clear();
    getline(fin, line);
    getline(fin, line);
    ss.str(line);
    ss >> line >> line >> line >> TopDie.rowLength >> TopDie.rowHeight >> TopDie.repeatCount;
    ss.clear();
    getline(fin, line);
    ss.str(line);
    ss >> line >> line >> line >> BottomDie.rowLength >> BottomDie.rowHeight >> BottomDie.repeatCount;
    ss.clear();
    getline(fin, line);
    getline(fin, line);
    ss.str(line);
    ss >> line >> TopDie.TechName;
    ss.clear();
    for(size_t i = 0; i < Techs.size(); i++){
        if(Techs[i].techName == TopDie.TechName){
            TopDie.DieTech = &Techs[i];
            break;
        }
    }
    
    getline(fin, line);
    ss.str(line);
    ss >> line >> BottomDie.TechName;
    ss.clear();
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
    ss.clear();
    getline(fin, line);
    ss.str(line);
    ss >> line >> HybridTerminal.spacing;
    ss.clear();
    getline(fin, line);
    ss.str(line);
    ss >> line >> HybridTerminal.val;
    ss.clear();
    getline(fin, line);
}

void Data::readInstanceInfo(ifstream& fin){
    string line;
    stringstream ss;
    getline(fin, line);
    ss.str(line);
    ss >> line >> instanceCount;
    ss.clear();
    for(int i = 0; i < instanceCount; i++){
        Instance temp;
        getline(fin, line);
        ss.str(line);
        ss >> line >> temp.instName >> temp.libCellName;
        ss.clear();
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
    ss.clear();
    for(int i = 0; i < netCount; i++){
        Net temp;
        getline(fin, line);
        ss.str(line);
        ss >> line >> temp.netName >> temp.numPins;
        ss.clear();
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
    if(DETAIL_DISPLAY){
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

    if(DETAIL_DISPLAY){
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

    //calculate the area if all place in 1 partition
    double topTotalArea = 0;
    double bottomTotalArea = 0;
    for(int i = 0; i < instanceCount; i++){
        topTotalArea += TopDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea;
        bottomTotalArea += BottomDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea;
    }
    //in experiment, there exist some cells need to fix on 1 side, since the difference of their area in different tech is large
    cout << "TopTotalArea: " << topTotalArea << endl;
    cout << "BottomTotalArea: " << bottomTotalArea << endl;
}

/*
brief about this function:
Generate 2 input files for shmetis
*   1. unweighted vertices graph
*   2. weighted vertices graph, with fmt = 10
*/
void Data::GeneratePartitionGraph(){

    //generate unweighted vertices graph (no fmt)
    FILE *unweighted_vertices_graph = fopen("Unweighted_Graph.hgr", "w");

    //first line contains # of net & # of instance.
    fprintf(unweighted_vertices_graph, "%d %d\n", netCount, instanceCount);

    //Following # of net lines contains the cell connected by the net
    for(int i = 0; i < netCount; i++){
        for(int j = 0; j < Nets[i].numPins; j++){
            string temp = Nets[i].instName[j];
            replace(temp.begin(), temp.end(), 'C', ' ');    //C1 -> 1
            fprintf(unweighted_vertices_graph, "%d ", stoi(temp));
        }
        fprintf(unweighted_vertices_graph, "\n");
    }
    fclose(unweighted_vertices_graph);
    //end of unweighted vertices graph


    //generate weighted vertices graph (fmt = 10)
    FILE *weighted_vertices_graph = fopen("Weighted_Graph.hgr", "w");

    //first line contains # of net & # of instance and fmt = 10
	fprintf(weighted_vertices_graph, "%d %d %d\n", netCount, instanceCount, WEIGHTED_GRAPH_FMT);

    //Following # of net lines contains the cell connected by the net
    for(int i = 0; i < netCount; i++){
        for(int j = 0; j < Nets[i].numPins; j++){
            string temp = Nets[i].instName[j];
            replace(temp.begin(), temp.end(), 'C', ' ');
            fprintf(weighted_vertices_graph, "%d ", stoi(temp));
        }
        fprintf(weighted_vertices_graph, "\n");
    }

    //Following # of instance lines contains the cell weight
    for(int i = 0; i < instanceCount; i++){
        fprintf(weighted_vertices_graph, "%d\n", Techs[0].LibCells[Instances[i].libCellName_int - 1].libCellArea);
    }
    fclose(weighted_vertices_graph);
    //end of weighted vertices graph
}

/*
brief about this function:
Generate 1 input file for shmetis
[2023/5/19 version 1.0]:
Distribute the Macro onto the top die and bottom die
Make sure the remaining area at top die and bottom die are almost equal
*/
void Data::GenerateFixPart(){
    //calculate how many area at both dies
    double TopDieMaxSize = TopDie.util/100.0 * TopDie.rowLength * TopDie.rowHeight * TopDie.repeatCount;
    double BottomDieMaxSize = BottomDie.util/100.0 * BottomDie.rowLength * BottomDie.rowHeight * BottomDie.repeatCount;
    double TopDieRemainArea = TopDieMaxSize;
    double BottomDieRemainArea = BottomDieMaxSize;

    FILE *FixPart = fopen("FixPart.hgr", "w");
    for(int i = 0; i < instanceCount; i++){
        bool isMacro = Techs[0].LibCells[Instances[i].libCellName_int - 1].isMacro;

        //macro placement by myself
        if(isMacro){
            if(BottomDieRemainArea > TopDieRemainArea){
                BottomDieRemainArea -= BottomDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea;
                fprintf(FixPart, "%d\n", 1);
            }
            else{
                TopDieRemainArea -= TopDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea;
                fprintf(FixPart, "%d\n", 0);
            }
        }
        else{
            //standard cell partition by shmetis
            double rand_portition = static_cast<double>(std::rand()) / RAND_MAX * 0.5;
            double compare = static_cast<double>(std::rand()) / RAND_MAX;
            if(compare < rand_portition){
                if(BottomDieRemainArea > TopDieRemainArea){
                    BottomDieRemainArea -= BottomDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea;
                    fprintf(FixPart, "%d\n", 1);
                }
                else{
                    TopDieRemainArea -= TopDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea;
                    fprintf(FixPart, "%d\n", 0);
                }
            }
            else
                fprintf(FixPart, "%d\n", -1);
            
        }
    }
    fclose(FixPart);
    cout << "Top remain: " << TopDieRemainArea << endl;
    cout << "Bottom remain: " << BottomDieRemainArea << endl;
}

bool Data::Evaluation(string filename){
    cout << "Evaluation Part: " + filename << endl;
    bool ret = true;
    double TopDieMaxSize = TopDie.util / 100.0 * TopDie.rowLength * TopDie.rowHeight * TopDie.repeatCount;
    double BottomDieMaxSize = BottomDie.util / 100.0 * BottomDie.rowLength * BottomDie.rowHeight * BottomDie.repeatCount;
    double TopDieArea = 0;
    double BottomDieArea = 0;

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
    cout << "-------------Partition Evaluation-------------------" << endl;
    cout << "TopDie Partition Summary: (" << TopDieArea << "/" <<  TopDieMaxSize << ") " << double(TopDieArea) / double(TopDie.rowLength * TopDie.rowHeight * TopDie.repeatCount) * 100 << endl;
    cout << "BottomDie Partition Summary: (" << BottomDieArea << "/" <<  BottomDieMaxSize << ") " << double(BottomDieArea) / double(BottomDie.rowLength  * BottomDie.rowHeight * BottomDie.repeatCount) * 100 << endl;
    cout << "----------------------------------------------------" << endl;
    return ret;
}

void Data::Partition(string input_filename, int UBfactor, bool *isValidPartition){
    GenerateFixPart();
    system("chmod +x lib/hmetis/shmetis");
    string command = "./lib/hmetis/shmetis " + input_filename + " FixPart.hgr" + " 2 " + to_string(UBfactor) + " > " + "/dev/null";
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
    string input_filename = "Weighted_Graph.hgr";
    bool isValidPartition = false;

    for(int i = 0; i < 60; i++){
        int randomOffset = rand() % 5;  //generate the random number between -2 ~ 2
        Partition(input_filename, 5 + randomOffset, &isValidPartition);
        if(isValidPartition) break;
    }

}

void Data::showPartitionResult(){
    for(size_t i = 0; i < PartitionResult.size(); i++){
        cout << PartitionResult[i] << endl;
    }
}