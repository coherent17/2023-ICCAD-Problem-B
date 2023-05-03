#include "../inc/Netlist.h"
#include "../inc/Technology.h"

Terminal::Terminal(ifstream& fin){
    string line;
    getline(fin, line);
    stringstream ss(line);

    ss >> line >> sizeX >> sizeY;
    ss.str("");

    getline(fin, line);
    ss.str(line);
    ss >> line >> spacing;
    ss.str("");

    getline(fin, line);
    ss.str(line);
    ss >> line >> cost;

    getline(fin, line);
}

ostream& operator<<(ostream& out, const Terminal& T){
    out << "TerminalSize <sizeX> <sizeY>: " << T.sizeX << " " << T.sizeY << endl;
    out << "TerminalSpacing <spacing>: " << T.spacing << endl;
    out << "TerminalCost <val>: " << T.cost << endl;
    return out;
}

Instance::Instance(){
    LibCellptr = nullptr;
}

Instance::~Instance(){

}

void InstanceParser(ifstream& fin, Instance **instances, int *NumInstances){
    string line;
    getline(fin, line);
    stringstream ss(line);
    ss >> line >> *NumInstances;

    *instances = new Instance[*(NumInstances) + 1];

    for(int i=1;i <= *NumInstances;i++){
        getline(fin, line);
        stringstream zz(line);
        zz >> line >> line >> line;
        line.replace(line.begin(), line.begin()+2, "");
        cout << line << endl;
        (*instances)[i].LibCellIdx = stoi(line);
    }

    getline(fin, line);
}

Net::Net(){
    numPins = 0;
    LibCellIdx = nullptr;
    PinIdx = nullptr;
}

Net::~Net(){
    delete []LibCellIdx;
    delete []PinIdx;
}

Netlist::Netlist(ifstream& fin){
    string line;
    getline(fin, line);
    stringstream ss(line);
    ss >> line >> NumNets;
    ss.str("");
    Nets = new Net[NumNets+1];
    
    for(int i=1;i<=NumNets;i++){
        // read Net Nx numPins
        getline(fin, line);
        stringstream zz(line);
        int numPins;
        zz >> line >> line >> numPins;
        zz.str("");
        Nets[i].numPins = numPins;
        Nets[i].LibCellIdx = new int[numPins + 1];
        Nets[i].PinIdx = new int[numPins + 1];
        cout<<numPins<<endl;
        for(int j=1;j<=numPins;j++){
            // read Pin Cx/Px
            getline(fin, line);
            replace(line.begin(), line.end(), '/', ' ');
            replace(line.begin(), line.end(), 'C', ' ');
            replace(line.begin(), line.end(), 'P', ' ');

            zz.str(line);
            zz >> line >> Nets[i].LibCellIdx[j] >> Nets[i].PinIdx[j];
            zz.str("");
        }
    }
}

Netlist::~Netlist(){
    delete [] Nets;
}

void Netlist::showNetlist(){
    for(int i=1;i<=NumNets;i++){
        cout<<"Net " << i << ":" << endl;
        for(int j=1;j<=Nets[i].numPins;j++){
            cout<<"C"<<Nets[i].LibCellIdx[j]<<" "<<"P"<<Nets[i].PinIdx[j]<<endl;
        }
    }
}