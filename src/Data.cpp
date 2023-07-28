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


    // sorted instances (C-N will locate in Instances[N-1])
    vector<Instance> tmp(instanceCount);
    for(int i=0;i<instanceCount;i++){
        stringstream zz(Instances[i].instName);
        char _;
        int idx;
        zz >> _ >> idx;
        idx--;
        tmp[idx] = Instances[i];
    }
    Instances = tmp;
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
            ss.clear();

            ss.str(tempinstName);
            int instNum;
            char _;
            ss >> _ >> instNum;
            Instances[instNum - 1].connectNets.push_back(i);
            ss.clear();
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
            // string temp = Nets[i].instName[j];
            // replace(temp.begin(), temp.end(), 'C', ' ');    //C1 -> 1
            stringstream ss(Nets[i].instName[j]);
            char _;
            int temp;
            ss >> _ >> temp;
            fprintf(unweighted_vertices_graph, "%d ", temp);
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
            // string temp = Nets[i].instName[j];
            // replace(temp.begin(), temp.end(), 'C', ' ');
            // fprintf(weighted_vertices_graph, "%d ", stoi(temp));
            stringstream ss(Nets[i].instName[j]);
            char _;
            int temp;
            ss >> _ >> temp;
            fprintf(unweighted_vertices_graph, "%d ", temp);
        }
        fprintf(weighted_vertices_graph, "\n");
    }

    //Following # of instance lines contains the cell weight
    for(int i = 0; i < instanceCount; i++){
        //if there exists 2 technology, then the weight should be the average of the area of the instances
        if(technologyCount == 2){
            fprintf(weighted_vertices_graph, "%d\n", (Techs[0].LibCells[Instances[i].libCellName_int - 1].libCellArea + Techs[1].LibCells[Instances[i].libCellName_int - 1].libCellArea) / 2 / 10);
        }
        else{
            fprintf(weighted_vertices_graph, "%d\n", Techs[0].LibCells[Instances[i].libCellName_int - 1].libCellArea);
        }
    }
    fclose(weighted_vertices_graph);
    //end of weighted vertices graph
}

/*
brief about this function:
Generate 1 input file for shmetis
[2023/5/19 version 1.0]:
Distribute the Macro onto the top die and bottom die in the following priority:
    1. the area of the cell in different tech [only if the technology of top die and bottom die are different]
    2. the remain area in both dies

Make sure the remaining area at top die and bottom die are almost equal after assign the fix part of the instances

@Property check@:
    If the instance in TA is macro, then in TB it must be macro.
*/
void Data::GenerateFixPart(int8_t option){
    //calculate how many area at both dies (divide 100.o first or overflow encounter in big case)
    double TopDieMaxSize = TopDie.util / 100.0 * TopDie.rowLength * TopDie.rowHeight * TopDie.repeatCount;
    double BottomDieMaxSize = BottomDie.util / 100.0 * BottomDie.rowLength * BottomDie.rowHeight * BottomDie.repeatCount;
    double TopDieRemainArea = TopDieMaxSize;
    double BottomDieRemainArea = BottomDieMaxSize;

    if(!(option & GREEDY_FIX)){
        FILE *FixPart = fopen("FixPart.hgr", "w");
        for(int i = 0; i < instanceCount; i++){
            bool isMacro = Techs[0].LibCells[Instances[i].libCellName_int - 1].isMacro;
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
                if(option & STD_CELL_RANDOM_ASSIGN){
                    double Rand_Prob = static_cast<double>(std::rand()) / RAND_MAX * 0.5;
                    double Cmp = static_cast<double>(std::rand()) / RAND_MAX;
                    if(Cmp < Rand_Prob){
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
                        fprintf(FixPart, "%d\n", -1);
                    }
                }
                else{
                    fprintf(FixPart, "%d\n", -1);
                }
            }
        }
        fclose(FixPart);
    }
    //perform some greedy choose
    else if(option & GREEDY_FIX){
        FILE *FixPart = fopen("FixPart.hgr", "w");
        for(int i = 0; i < instanceCount; i++){
            bool isMacro = Techs[0].LibCells[Instances[i].libCellName_int - 1].isMacro;
            if(isMacro){
                //if there exist 2 technology
                if(technologyCount == 2){
                    bool placeWhere = 0;
                    placeWhere = TopDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea < BottomDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea ? PARTITION_TOP : PARTITION_BOTTOM;
                    if(placeWhere == PARTITION_TOP){
                        if(TopDieRemainArea > TopDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea){
                            TopDieRemainArea -= TopDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea;
                            fprintf(FixPart, "%d\n", 0);
                        }
                        else{
                            BottomDieRemainArea -= BottomDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea;
                            fprintf(FixPart, "%d\n", 1);
                        }
                    }

                    else{
                        if(BottomDieRemainArea > BottomDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea){
                            BottomDieRemainArea -= BottomDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea;
                            fprintf(FixPart, "%d\n", 1);
                        }
                        else{
                            TopDieRemainArea -= TopDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea;
                            fprintf(FixPart, "%d\n", 0);
                        }
                    }
                }
                //there exists only 1 technology
                else{
                    if(BottomDieRemainArea > TopDieRemainArea){
                        BottomDieRemainArea -= BottomDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea;
                        fprintf(FixPart, "%d\n", 1);
                    }
                    else{
                        TopDieRemainArea -= TopDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea;
                        fprintf(FixPart, "%d\n", 0);
                    }
                }
            }
            //not macro
            else{
                if(option & STD_CELL_RANDOM_ASSIGN){
                    double Rand_Prob = static_cast<double>(std::rand()) / RAND_MAX * 0.5;
                    double Cmp = static_cast<double>(std::rand()) / RAND_MAX;
                    if(Cmp < Rand_Prob){
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
                        fprintf(FixPart, "%d\n", -1);
                    }
                }
                else{
                    fprintf(FixPart, "%d\n", -1);
                }
            }
        }
        fclose(FixPart);
    }

    else abort();
    
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
            if(TopDieArea > TopDieMaxSize) ret = false;     //when releasing, here should add break
        }
        else{
            BottomDieArea += BottomDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea;
            if(BottomDieArea > BottomDieMaxSize) ret = false;   //when releasing, here should add break
        }
    }
    fin.close();
    cout << "-------------Partition Evaluation-------------------" << endl;
    cout << "TopDie Partition Summary: (" << TopDieArea << "/" <<  TopDieMaxSize << ") " << TopDieArea / double(TopDie.rowLength) / double(TopDie.rowHeight) / double(TopDie.repeatCount) * 100.0 << endl;
    cout << "BottomDie Partition Summary: (" << BottomDieArea << "/" <<  BottomDieMaxSize << ") " << BottomDieArea / double(BottomDie.rowLength)  / double(BottomDie.rowHeight) / double(BottomDie.repeatCount) * 100.0 << endl;
    cout << "----------------------------------------------------" << endl;
    return ret;
}

void Data::Partition(string input_filename, bool *isValidPartition, int8_t option){

    //unweighted partition
    if(!(option & WEIGHTED)){
        system("./lib/hmetis/shmetis Unweighted_Graph.hgr 2 5 > /dev/null");
    }
    
    //weighted graph without fix part
    else if((option & WEIGHTED) && !(option & FIX_PARTITION)){
        cout << "Weighted Partition" << endl;
        system("./lib/hmetis/shmetis Weighted_Graph.hgr 2 5 > /dev/null");
    }

    //weighted graph with fix partition generate by not considering greedy choice about the area
    else if((option & WEIGHTED) && (option & FIX_PARTITION) && !(option & GREEDY_FIX)){
        GenerateFixPart(option);
        system("./lib/hmetis/shmetis Weighted_Graph.hgr FixPart.hgr 2 5 > /dev/null");
    }

    else if((option & WEIGHTED) && (option & FIX_PARTITION) && (option & GREEDY_FIX)){
        GenerateFixPart(option);
        system("./lib/hmetis/shmetis Weighted_Graph.hgr FixPart.hgr 2 5 > /dev/null");
    }
    else abort();   //there is no way to reach here

    //evaluation whether this partition result is legal or not 
    *isValidPartition = Evaluation(input_filename + ".part.2");
    
    // if the partition is legal -> copy to the vector
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

    //perform the normal basic partition for case 1 remain for the condition of min cut
    for(int i = 0; i < 1; i++){
        cout << "Execution Partition " << i << endl;
        Partition(input_filename, &isValidPartition, 0);
        if(isValidPartition) return;
    }

    //for case 2 and 3 is good
    for(int i = 0; i < 2; i++){
        cout << "Execution Partition " << i << endl;
        Partition(input_filename, &isValidPartition, WEIGHTED | FIX_PARTITION | STD_CELL_RANDOM_ASSIGN | GREEDY_FIX);
        if(isValidPartition) return;
    }

    // cannot find legal solution -> copy to the vector
    if(!isValidPartition){
        ifstream fin(input_filename + ".part.2");
        int partition;
        for(int i = 0; i < instanceCount; i++){
            fin >> partition;
            PartitionResult.push_back(partition);
        }
    }

    legalizePartion();
}

void Data::legalizePartion(){
    cout << "Legalize Partition " << endl;
    bool ret = true;
    double TopDieMaxSize = TopDie.util / 100.0 * TopDie.rowLength * TopDie.rowHeight * TopDie.repeatCount;
    double BottomDieMaxSize = BottomDie.util / 100.0 * BottomDie.rowLength * BottomDie.rowHeight * BottomDie.repeatCount;
    double TopDieArea = 0;
    double BottomDieArea = 0;


    // initial die area
    int partition;
    for(int i = 0; i < instanceCount; i++){
        partition = PartitionResult[i];
        if(partition == PARTITION_TOP){
            TopDieArea += TopDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea;
        }
        else{
            BottomDieArea += BottomDie.DieTech->LibCells[Instances[i].libCellName_int - 1].libCellArea;
        }
    }

    // initial terminal number
    NumTerminals = 0;
    for(int i=0;i<netCount;i++){
        Nets[i].hasTerminal = false;
        if(needTerminal(i)){
            Nets[i].hasTerminal = true;
            NumTerminals++;
        }
    }  

    double maxNumOfTerminal = int((TopDie.upperRightX - HybridTerminal.spacing) / (HybridTerminal.sizeX + HybridTerminal.spacing))
                            * int((TopDie.upperRightY - HybridTerminal.spacing) / (HybridTerminal.sizeY + HybridTerminal.spacing));

    while(TopDieArea > TopDieMaxSize || BottomDieArea > BottomDieMaxSize || NumTerminals > maxNumOfTerminal){
        int idx = rand() % instanceCount;
        cout << "select instance : " << idx << endl;
        cout << "Num of terminal : " << NumTerminals << endl;
        if(TopDieArea > TopDieMaxSize){
            if(PartitionResult[idx] != 0)
                continue;
            if(BottomDieArea + BottomDie.DieTech->LibCells[Instances[idx].libCellName_int - 1].libCellArea < BottomDieMaxSize){
                for(int i=0;i<Instances[idx].connectNets.size();i++){
                    if(needTerminal(Instances[idx].connectNets[i]))
                        NumTerminals--;
                }

                PartitionResult[idx] = 1;
                TopDieArea -= TopDie.DieTech->LibCells[Instances[idx].libCellName_int - 1].libCellArea;
                BottomDieArea += BottomDie.DieTech->LibCells[Instances[idx].libCellName_int - 1].libCellArea;

                for(int i=0;i<Instances[idx].connectNets.size();i++){
                    if(needTerminal(Instances[idx].connectNets[i]))
                        NumTerminals++;
                }
            }
        }
        else{
            if(PartitionResult[idx] != 1)
                continue;
            if(TopDieArea + TopDie.DieTech->LibCells[Instances[idx].libCellName_int - 1].libCellArea < TopDieMaxSize){
                for(int i=0;i<Instances[idx].connectNets.size();i++){
                    if(needTerminal(Instances[idx].connectNets[i]))
                        NumTerminals--;
                }
                
                PartitionResult[idx] = 0;
                TopDieArea += TopDie.DieTech->LibCells[Instances[idx].libCellName_int - 1].libCellArea;
                BottomDieArea -= BottomDie.DieTech->LibCells[Instances[idx].libCellName_int - 1].libCellArea;
           
                for(int i=0;i<Instances[idx].connectNets.size();i++){
                    if(needTerminal(Instances[idx].connectNets[i]))
                        NumTerminals++;
                }
            }
        }
    }

    cout << "-------------Legalize Result-------------------" << endl;
    cout << "TopDie Partition Summary: (" << TopDieArea << "/" <<  TopDieMaxSize << ") " << TopDieArea / double(TopDie.rowLength) / double(TopDie.rowHeight) / double(TopDie.repeatCount) * 100.0 << endl;
    cout << "BottomDie Partition Summary: (" << BottomDieArea << "/" <<  BottomDieMaxSize << ") " << BottomDieArea / double(BottomDie.rowLength)  / double(BottomDie.rowHeight) / double(BottomDie.repeatCount) * 100.0 << endl;
    cout << "----------------------------------------------------" << endl;
}


void Data::showPartitionResult(){
    ofstream fout("partition.txt");
    for(size_t i = 0; i < PartitionResult.size(); i++){
        fout << "Instance : "<< i+1 << " name : "<< Instances[i].instName<< " is on "<<PartitionResult[i] << endl;
    }
}

void Data::LoadPartition(){
    if(instanceCount == 8){
        PartitionResult[6] = 0;
        PartitionResult[2] = 1;
        PartitionResult[0] = 0;
        PartitionResult[3] = 0;
        PartitionResult[5] = 1;
        PartitionResult[1] = 0;
        PartitionResult[4] = 0;
        PartitionResult[7] = 0;
    }
    for(size_t i = 0; i < PartitionResult.size(); i++){
        if(PartitionResult[i] == PARTITION_TOP){
            Instances[i].LibCellptr = &(TopDie.DieTech->LibCells[Instances[i].libCellName_int - 1]);
        }
        else if(PartitionResult[i] == PARTITION_BOTTOM){
            Instances[i].LibCellptr = &(BottomDie.DieTech->LibCells[Instances[i].libCellName_int - 1]);
        }
        //never reach here
        else abort();
    }
    legalizePartion();
}

//***********************//
//      Placement        //
//***********************//
// Description:
// 1. transform data to GSRC/bookshelf format
// 2. call NTUplacer
// 3. read the result

void Data::Placement(){
    // create output directory
    system("mkdir -p placement");


    for(int i=0;i<3;i++){
        int curDie = i%2;
        // input file names for ntuplacer in bookshelf format
        string nodes_file = "./placement/iccad.nodes";
        string nets_file = "./placement/iccad.nets";
        string wts_file = "./placement/iccad.wts";
        string pl_file = "./placement/iccad.pl";
        string scl_file = "./placement/iccad.scl";

        // generat inputs file
        makeNodesFile(nodes_file, curDie);
        makeNetsFile(nets_file, curDie);
        makeWtsFile(wts_file, curDie);
        makePlFile(pl_file, curDie, i!=0, i>1);
        makeSclFile(scl_file, curDie);

        // generate aux file
        ofstream fout("./placement/iccad.aux");
        // fout << "RowBasedPlacement : "  << nodes_file << " " << nets_file << " " 
        //                                 << wts_file << " " << pl_file << " " << scl_file << endl;
        fout << "RowBasedPlacement : iccad.nodes iccad.nets iccad.wts iccad.pl iccad.scl" << endl;
        
        // Remove old result
        system("rm ./iccad.ntup.pl");
        
        // call ntuplacer
        string placer_path = "./lib/ntuplace/ntuplace3";
        string parameter = "";
        // if(instanceCount < 100 || instanceCount > 15000)
        //    parameter = "-noglobal ";
        if(i == 0)
           parameter = "-nolegal -nodetail";
        string cmd = placer_path + " -aux ./placement/iccad.aux -MRT " + parameter;
        system(("chmod +x " + placer_path).c_str());
        system(cmd.c_str());

        // load placement result
        string result_file = "./iccad.ntup.pl";
        loadPlacementResult(result_file, curDie);
        cout<<"Finish"<<endl;
    }
}

void Data::makeNodesFile(string file_name, int side){
    int NumNodes = 0;
    for(int i=0;i<instanceCount;i++){
        if(PartitionResult[i] == side)
            NumNodes++;
    }

    ofstream fout(file_name);
    fout << "UCLA nodes 1.0" << endl << endl;
    fout<<"NumNodes : "<<NumNodes<<endl;
    fout<<"NumTerminals : 0"<<endl<<endl;

    for(int i=0;i<instanceCount;i++){
        if(PartitionResult[i] == side){
            fout<<" "  <<Instances[i].instName<<" "
                        <<Instances[i].LibCellptr->libCellSizeX<<" "
                        <<Instances[i].LibCellptr->libCellSizeY<<endl;
        }
    }
    fout.close();
}

void Data::makeNetsFile(string file_name, int side){
    ofstream fout(file_name);
    fout << "UCLA nets 1.0" << endl << endl;
    int pinCount = 0;
    int curNetCount = 0;
    vector<int> numOfPin(netCount, 0);
    for(int i=0;i<netCount;i++){
        int curPinCount = 0;
        for(int j=0;j<Nets[i].numPins;j++){
            string name = Nets[i].instName[j];
            // get instance index
            stringstream ss(name); 
            char trash;
            int instance_idx;
            ss >> trash >> instance_idx;
            instance_idx--;

            if(PartitionResult[instance_idx] == side){ 
                pinCount++;
                curPinCount++;
            }
        }
        numOfPin[i] = curPinCount;
        if(curPinCount > 1)
            curNetCount++;
        else
            pinCount -= curPinCount;
    }

    fout << "NumNets : "<< curNetCount << endl;
    fout << "NumPins : "<< pinCount << endl << endl;

    for(int i=0;i<netCount;i++){
        if(numOfPin[i] <= 1)
            continue;
        // assume all Net has numPins == numInstances
        fout << "NetDegree : " << numOfPin[i] << endl;
        for(int j=0;j<Nets[i].numPins;j++){
            string name = Nets[i].instName[j];
            // get instance index
            // assume instance index = 1 to N
            stringstream ss(name);
            char trash;
            int instance_idx;
            ss >> trash >> instance_idx;
            instance_idx--;

            // if is not on the same die no need to do placement
            if(PartitionResult[instance_idx] != side)
                continue;
            // get cell information
            int w = Instances[instance_idx].LibCellptr->libCellSizeX;
            int h = Instances[instance_idx].LibCellptr->libCellSizeY;

            // get pin index;
            // assume pin number start with 1 to N
            stringstream zz(Nets[i].libPinName[j]);
            int pin_idx;
            zz >> trash >> pin_idx;
            pin_idx--;

            // get pin information
            int x = Instances[instance_idx].LibCellptr->Pins[pin_idx].pinLocationX;
            int y = Instances[instance_idx].LibCellptr->Pins[pin_idx].pinLocationY;

            // get offset
            double offset_x = x - w/2.0;
            double offset_y = y - h/2.0;

            // write back

            fout << "\t" << name << " I : " << offset_x << " " << offset_y << endl;
        }
    }

    fout.close();
}

void Data::makeWtsFile(string file_name, int side){
    ofstream fout(file_name);
    fout << "UCLA wts 1.0" << endl << endl;
    for(int i=0;i<instanceCount;i++){
        if(PartitionResult[i] == side)
            fout << "\t"  << Instances[i].instName << " " << 1 << endl;
    }

    fout.close();
}

void Data::makePlFile(string file_name, int side, bool initialPl, bool all){
    ofstream fout(file_name);
    fout << "UCLA pl 1.0" << endl << endl;
    for(int i=0;i<instanceCount;i++){
        if(!initialPl) // no fixed instances for first die
            continue;
        // fixed initial placement for second die
        if(PartitionResult[i] == side){
            int initX = 0;
            int initY = 0;
            for(int j=0;j<Instances[i].connectNets.size();j++){
                if(Nets[j].hasTerminal){
                    int max_x, min_x, max_y, min_y;
                    min_x = INT_MAX;
                    min_y = INT_MAX;
                    max_x = INT_MIN;
                    max_y = INT_MIN;
                    if(!all)
                        getNetExtremeConsiderSide(j, max_x, min_x, max_y, min_y, side);
                    // cout<<max_x<<" "<<min_x<<" "<<max_y<<" "<<min_y<<endl;
                    else
                        getNetExtreme(j, max_x, min_x, max_y, min_y);
                    if(initX == 0 && initY == 0){
                        initX = (max_x + min_x) / 2.0;
                        initY = (max_y + min_y) / 2.0;
                    }
                    else{
                        initX = (((max_x + min_x) / 2.0) + initX) / 2.0;
                        initY = (((max_y + min_y) / 2.0) + initY) / 2.0; 
                    }
                    // break; // now only consider first net
                }
            }
            if(initX == 0 && initY == 0)
                fout << "\t" << Instances[i].instName << "\t0\t0 : N" << endl;
            else
                fout << "\t" << Instances[i].instName << "\t" << initX << "\t" << initY << " : N" << endl; 
        }
    }

    fout.close();
}

void Data::makeSclFile(string file_name, int side){
    ofstream fout(file_name);
    
    fout << "UCLA scl 1.0" << endl << endl;

    Die *curDie = (side==0)?&TopDie:&BottomDie;

    fout << "NumRows : " << curDie->repeatCount << endl << endl;    

    // fixed start Y for coordinate
    int coordinate = 0;
    for(int i=0;i<curDie->repeatCount;i++){
        fout << "CoreRow Horizontal" << endl;
        fout << " Coordinate : " << coordinate << endl;
        fout << " Height : " << curDie->rowHeight << endl;
        fout << " Sitewidth : 1" << endl;
        fout << " Sitespacing : 1" << endl;
        fout << " Siteorient : 1" << endl;
        fout << " Sitesymmetry : 1" << endl;
        // fixed start X
        fout << " SubrowOrigin : " << 0 << "  NumSites : " << curDie->rowLength << endl;
        fout << "End" << endl; 

        coordinate += curDie->rowHeight;
    }

    fout.close();   
}

void Data::loadPlacementResult(string file_name, int side){
    ifstream fin(file_name);

    if(!fin.is_open()){
        cout<<"Fail to place "<<side<<endl;
        cout<<"Greedy placement"<<endl;
        GeedyPlacement(side);
        return ;
    }

    string line;
    getline(fin, line); // load UCLA pl 1.0 Useless

    while(getline(fin, line)){
        if(line == "")
            continue;
        stringstream ss(line);
        char _;
        int x, y, idx;
        string orientation;
        ss >> _ >> idx >> x >> y >> _ >> orientation;
        idx--;
        Instances[idx].X = x;
        Instances[idx].Y = y;
        Instances[idx].orientation = orientation; 
    }

    fin.close();
}

void Data::GeedyPlacement(int side){
    int startX = 0;
    int startY = 0;
    int nextY = 0;
    int dieSizeX = (side == 0)?TopDie.upperRightX:BottomDie.upperRightX;
    int dieSizeY = (side == 0)?TopDie.upperRightY:BottomDie.upperRightY;
    for(int i=0;i<instanceCount;i++){
        if(PartitionResult[i] == side){
            if(Instances[i].LibCellptr->libCellSizeX + startX < dieSizeX){
                ;
            }
            else{
                startX = 0;
                startY = nextY;
                nextY = 0;
            }

            Instances[i].X = startX;
            Instances[i].Y = startY;
            Instances[i].orientation = "N";
            startX += Instances[i].LibCellptr->libCellSizeX;
            nextY = max(Instances[i].LibCellptr->libCellSizeY, nextY); 
        }
    }
}

void Data::showPlacementResult(){
    ofstream fout("test.txt");
    for(size_t i = 0; i < PartitionResult.size(); i++){
        fout    << "Instance : "<< i+1 << " is on "<<Instances[i].X << " " << Instances[i].Y 
                << " with orientation :" << Instances[i].orientation << endl;
    }
}


//***********************//
//      Terminal         //
//***********************//
// Description:
// 1. Reference to Coherent

void Data::terminalPlacement(){
    terminalPlacementState = vector< vector<int> >(TopDie.upperRightY, vector<int>(TopDie.upperRightX, 0));
    int spacing = HybridTerminal.spacing;
    int sizeY = HybridTerminal.sizeY;
    int sizeX = HybridTerminal.sizeX;
    int dieSizeX = TopDie.upperRightX;
    int dieSizeY = TopDie.upperRightY;
    NumTerminals = 0;

    TerminalPlacement TerminalPlacer(HybridTerminal.sizeX, HybridTerminal.spacing, TopDie.upperRightX, TopDie.upperRightY);

    int startX = sizeX/2 + spacing;
    int startY = sizeY/2 + spacing;
    for(int i=0;i<netCount;i++){
        Nets[i].hasTerminal = false;
        if(needTerminal(i)){
            // cout << "Place Terminal for net : "<< i <<endl;
            NumTerminals++;
            // stupid placement
            if(0){
                if(startX + spacing + sizeX/2 < dieSizeX){
                    Nets[i].HBlocationX = startX;
                    Nets[i].HBlocationY = startY;
                    Nets[i].hasTerminal = true;
                    startX += spacing + sizeX;
                }
                else{
                    startX = sizeX/2 + spacing;
                    startY += spacing + sizeY;
                    Nets[i].HBlocationX = startX;
                    Nets[i].HBlocationY = startY;
                    Nets[i].hasTerminal = true;
                    startX += spacing + sizeX;
                }
                
                continue;
            }
            Nets[i].hasTerminal = true;
            int x_max, x_min, y_max, y_min;
            x_min = INT_MAX;
            y_min = INT_MAX;
            x_max = INT_MIN;
            y_max = INT_MIN;
            getNetExtreme(i, x_max, x_min, y_max, y_min);
            // cout<<x_max << " "<<x_min<<" "<<y_max<<" "<<y_min<<endl;
            // exit(0);
            TerminalPlacer.addTerminal(x_max, x_min, y_max, y_min);
            continue;

            int lower = (y_min < (spacing + (sizeY/2))) ? (spacing + sizeY/2) : y_min;
            int upper = min(y_max, dieSizeY - spacing - sizeY/2 -1);
            int left = max(x_min, spacing + sizeX/2);
            int right = min(x_max, dieSizeX - spacing - sizeX/2 - 1);

            bool placed = false;

            for(int j=lower; j<=upper;j++){
                for(int k=left; k<=right;j++){
                    if(isValidTerminalPlacement(j, k, sizeX, sizeY, spacing)){
                        fillTerminalPlacement(j, k, sizeX, sizeY, spacing);
                        Nets[i].HBlocationX = k;
                        Nets[i].HBlocationY = j;
                        placed = true;
                        break;
                    }
                }
                if(placed)
                    break;
            }

            if(!placed){
                cout << "net failed : " << i << endl;
            }
        }
    }
    if(0)
        return ;
    // cout<<"call placer"<<endl;
    TerminalPlacer.Placement();

    int terminalIdx = 0;
    for(int i=0;i<netCount;i++){
        if(Nets[i].hasTerminal){
            Nets[i].HBlocationX = TerminalPlacer.getHBlocationX(terminalIdx);
            Nets[i].HBlocationY = TerminalPlacer.getHBlocationY(terminalIdx);
            terminalIdx++;
        }
    }

    cout<<"Num of terminal : "<< NumTerminals<<endl;
}

bool Data::needTerminal(int in){
    int prev = -1;
    for(int i=0;i<Nets[in].instName.size();i++){
        char _;
        int idx;
        stringstream ss(Nets[in].instName[i]);
        ss >> _ >> idx;
        idx--;

        if(prev != -1 && PartitionResult[idx] != prev){
            return true;
        }
        prev = PartitionResult[idx];
    }

    return false;
}

void Data::getNetExtreme(int in, int& x_max, int& x_min, int& y_max, int& y_min){
    for(int i=0;i<Nets[in].instName.size();i++){
        char _;
        int idx;
        stringstream ss(Nets[in].instName[i]);
        ss >> _ >> idx;
        idx--;
        // cout << Instances[idx].X << " " << Instances[idx].Y<<endl;
        if(x_max < Instances[idx].X + Instances[idx].LibCellptr->libCellSizeX / 2){
            x_max = Instances[idx].X + Instances[idx].LibCellptr->libCellSizeX / 2;
        }
        if(x_min > Instances[idx].X + Instances[idx].LibCellptr->libCellSizeX / 2){
            x_min = Instances[idx].X + Instances[idx].LibCellptr->libCellSizeX / 2;
        }

        if(y_max < Instances[idx].Y + Instances[idx].LibCellptr->libCellSizeY / 2){
            y_max = Instances[idx].Y + Instances[idx].LibCellptr->libCellSizeY / 2;
        }
        if(y_min > Instances[idx].Y + Instances[idx].LibCellptr->libCellSizeY / 2){
            y_min = Instances[idx].Y + Instances[idx].LibCellptr->libCellSizeY / 2;
        }
    }
}

void Data::getNetExtremeConsiderSide(int in, int& x_max, int& x_min, int& y_max, int& y_min, int side){
    for(int i=0;i<Nets[in].instName.size();i++){        
        char _;
        int idx;
        stringstream ss(Nets[in].instName[i]);
        ss >> _ >> idx;
        idx--;

        if(PartitionResult[idx] == side)
            continue;
        // cout << Instances[idx].X << " " << Instances[idx].Y<<endl;
        if(x_max < Instances[idx].X + Instances[idx].LibCellptr->libCellSizeX / 2){
            x_max = Instances[idx].X + Instances[idx].LibCellptr->libCellSizeX / 2;
        }
        if(x_min > Instances[idx].X + Instances[idx].LibCellptr->libCellSizeX / 2){
            x_min = Instances[idx].X + Instances[idx].LibCellptr->libCellSizeX / 2;
        }

        if(y_max < Instances[idx].Y + Instances[idx].LibCellptr->libCellSizeY / 2){
            y_max = Instances[idx].Y + Instances[idx].LibCellptr->libCellSizeY / 2;
        }
        if(y_min > Instances[idx].Y + Instances[idx].LibCellptr->libCellSizeY / 2){
            y_min = Instances[idx].Y + Instances[idx].LibCellptr->libCellSizeY / 2;
        }
    }
}

bool Data::isValidTerminalPlacement(int center_x, int center_y, int terminalX, int terminalY, int spacing){
    for(int i= center_y - terminalY/2 - spacing +1 ; i <= center_y + terminalY/2 +spacing; i++){
        for(int j= center_x - terminalX/2 - spacing +1 ; j <= center_x + terminalX/2 +spacing; j++){
            
            if(terminalPlacementState[i][j]){
                return false;
            }
        }
    }
    return true;
}

void Data::fillTerminalPlacement(int center_x, int center_y, int terminalX, int terminalY, int spacing){
    for(int i= center_y - terminalY/2 +1 ; i <= center_y + terminalY/2 ; i++){
        for(int j= center_x - terminalX/2 +1 ; j <= center_x + terminalX/2 ; j++){
            terminalPlacementState[i][j]=1;
        }
    }
}

//***********************//
//      Output           //
//***********************//
// Description:
// 1. TopDie
// 2. BottomDie
// 3. Terminals

void Data::output(char *file_name){
    FILE *out = fopen(file_name, "w");

    // calculate cell number
    int TopDieCell = 0;
    int BottomDieCell = 0;
    for(int i=0;i<instanceCount;i++)
        if(PartitionResult[i])
            BottomDieCell++;
        else
            TopDieCell++;

    fprintf(out, "TopDiePlacement %d\n", TopDieCell);
    for(int i=0;i<instanceCount;i++){
        if(PartitionResult[i] == 0){
            string output_orientation = getOrientation(i);
            fprintf(out, "Inst %s %d %d %s\n", Instances[i].instName.c_str(), Instances[i].X, Instances[i].Y, output_orientation.c_str());
        }
    }

    fprintf(out, "BottomDiePlacement %d\n", BottomDieCell);
    for(int i=0;i<instanceCount;i++){
        if(PartitionResult[i] == 1){
            string output_orientation = getOrientation(i);
            fprintf(out, "Inst %s %d %d %s\n", Instances[i].instName.c_str(), Instances[i].X, Instances[i].Y, output_orientation.c_str());
        }
    }

    fprintf(out, "NumTerminals %d\n", NumTerminals);
    for(int i=0;i<netCount;i++){
        if(Nets[i].hasTerminal){
            fprintf(out, "Terminal %s %d %d\n", Nets[i].netName.c_str(), Nets[i].HBlocationX, Nets[i].HBlocationY);
        }
    }
}

string Data::getOrientation(int i){
    char comp = Instances[i].orientation[0];
    if(comp == 'F')
        comp = Instances[i].orientation[1];
    switch(comp){
        case 'N':
            return "R0";
            break;
        case 'S':
            return "R180";
            break;
        case 'E':
            return "R270";
            break;
        case 'W':
            return "R90";
            break;

        default:
            cout<<"Invalid choice"<<endl;
            break;
    }
    return "R0";
}