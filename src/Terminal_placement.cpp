#include "../inc/Terminal_placement.h"

TerminalPlacement::TerminalPlacement(int TerminalSize, int spacing, int length, int heigh){
    this->size = TerminalSize + spacing; // terminal place size
    dieX = length;
    dieY = heigh;
    this->TerminalSize = TerminalSize;
    this->spacing = spacing;
}

TerminalPlacement::~TerminalPlacement(){

}

void TerminalPlacement::addTerminal(int max_x, int min_x, int max_y, int min_y){
    NetExtreme.push_back({max_x, min_x, max_y, min_y});
}

int TerminalPlacement::getHBlocationX(int i){
    return HBlocation[i][0] + TerminalSize/2 + floor(spacing/2.0);
}

int TerminalPlacement::getHBlocationY(int i){
    return HBlocation[i][1] + TerminalSize/2 + floor(spacing/2.0);
}

void TerminalPlacement::Placement(){
    // create output directory
    system("mkdir -p placementT");


    // input file names for ntuplacer in bookshelf format
    string nodes_file = "./placementT/iccad.nodes";
    string nets_file = "./placementT/iccad.nets";
    string wts_file = "./placementT/iccad.wts";
    string pl_file = "./placementT/iccad.pl";
    string scl_file = "./placementT/iccad.scl";

    // generat inputs file
    makeNodesFile(nodes_file);
    makeNetsFile(nets_file);
    makeWtsFile(wts_file);
    makePlFile(pl_file);
    makeSclFile(scl_file);

    // generate aux file
    ofstream fout("./placementT/iccad.aux");
    // fout << "RowBasedPlacement : "  << nodes_file << " " << nets_file << " " 
    //                                 << wts_file << " " << pl_file << " " << scl_file << endl;
    fout << "RowBasedPlacement : iccad.nodes iccad.nets iccad.wts iccad.pl iccad.scl" << endl;
    
    // Remove old result
    system("rm ./iccad.ntup.pl");
    
    // call ntuplacer
    string placer_path = "./lib/ntuplace/ntuplace3";
    string parameter = "-noglobal -nodetail";
    parameter = "-nodetail -noglobal";
    string cmd = placer_path + " -aux ./placementT/iccad.aux " + parameter;
    system(("chmod +x " + placer_path).c_str());
    system(cmd.c_str());

    // load placement result
    string result_file = "./iccad.ntup.pl";
    loadPlacementResult(result_file);
    cout<<"Finish"<<endl;
}

void TerminalPlacement::makeNodesFile(string file_name){
    int NumTerminal = NetExtreme.size();
    
    ofstream fout(file_name);
    fout << "UCLA nodes 1.0" << endl << endl;
    fout<<"NumNodes : "<<NumTerminal<<endl;
    fout<<"NumTerminals : 0"<<endl<<endl;

    for(int i=0;i<NumTerminal;i++){
        fout<<" "  << "T" << i << " "
                    <<size<<" "
                    <<size<<endl;
    }
    fout.close();
}

void TerminalPlacement::makeNetsFile(string file_name){
    ofstream fout(file_name);
    fout << "UCLA nets 1.0" << endl << endl;
    int pinCount = 0;
    int curNetCount = 0;

    fout << "NumNets : "<< curNetCount << endl;
    fout << "NumPins : "<< pinCount << endl << endl;

    fout.close();
}

void TerminalPlacement::makeWtsFile(string file_name){
    ofstream fout(file_name);
    int NumTerminal = NetExtreme.size();
    fout << "UCLA wts 1.0" << endl << endl;
    for(int i=0;i<NumTerminal;i++){
        fout << "\t"  << "T" << i << " " << 1 << endl;
    }

    fout.close();
}

void TerminalPlacement::makePlFile(string file_name){
    ofstream fout(file_name);
    int NumTerminal = NetExtreme.size();
    fout << "UCLA pl 1.0" << endl << endl;
    for(int i=0;i<NumTerminal;i++){
        int x = (NetExtreme[i][0] + NetExtreme[i][1]) / 2;
        int y = (NetExtreme[i][2] + NetExtreme[i][3]) / 2;
        int w = (NetExtreme[i][1] - NetExtreme[i][0]);
        int h = (NetExtreme[i][3] - NetExtreme[i][2]);
        // cout<<"shift"<<endl;
        // if(w != 0)
        //     x = x + (random()%(w/2) - w);
        // if(h != 0)
        //     y = y + (random()%(h/2) - h);
        x = min(x,22900);
        y = min(y, 18900);
        x = max(0, x);
        y = max(0, y);
        // cout<<"end shift"<<endl;
        // x = 0;
        // y = 0;
        fout << "\t" << "T" << i << "\t" << x << "\t" << y << " : N" << endl;
    }

    fout.close();
}

void TerminalPlacement::makeSclFile(string file_name){
    ofstream fout(file_name);
    
    fout << "UCLA scl 1.0" << endl << endl;


    fout << "NumRows : " << int(dieY-ceil(spacing))/size << endl << endl;    

    // fixed start Y for coordinate
    int coordinate = ceil(spacing / 2.0);
    // coordinate = 0;
    for(int i=0;i<int(dieY-ceil(spacing)-1)/size;i++){
        fout << "CoreRow Horizontal" << endl;
        fout << " Coordinate : " << coordinate << endl;
        fout << " Height : " << size << endl;
        fout << " Sitewidth : 1" << endl;
        fout << " Sitespacing : 1" << endl;
        fout << " Siteorient : 1" << endl;
        fout << " Sitesymmetry : 1" << endl;
        // fixed start X
        // if(i > ceil(spacing / 2.0) && i < dieY - ceil(spacing / 2.0))
            fout << " SubrowOrigin : " << ceil(spacing / 2.0) << "  NumSites : " << dieX - (spacing)<< endl;
        // else
        //     fout << " SubrowOrigin : " << 0 << "  NumSites : " << spacing - ceil(spacing / 2.0) << endl;
        fout << "End" << endl; 

        coordinate += size;
    }

    fout.close();   
}

void TerminalPlacement::loadPlacementResult(string file_name){
    ifstream fin(file_name);

    if(!fin.is_open()){
        cout<<"Fail to place Terminal"<<endl;
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
        HBlocation.push_back({x, y});
    }

    fin.close();
}