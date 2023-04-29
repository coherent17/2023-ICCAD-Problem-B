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