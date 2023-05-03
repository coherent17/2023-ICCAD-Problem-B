#include "inc/Technology.h"
#include "inc/Die.h"
#include "inc/Netlist.h"
#include "inc/Partition.h"

int main(int argc, char *argv[]){

    if(argc != 3){
        printf("usage: %s <input.txt> <output.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    //read the technoology info
    ifstream fin(*(argv + 1));
    Technology T(fin);
    T.showData();

    //read the die info, Dies[0] = top die, Dies[1] = bottom die
    Die *Dies = new Die[2];
    DieParser(fin, Dies, T);

    cout << "Top Die" << endl;
    cout << Dies[0] << endl;

    cout << "Bottom Die" << endl;
    cout << Dies[1] << endl;


    //read the terminal info
    Terminal Term(fin);
    cout << Term << endl;

    //read NetList
    Instance *instances = nullptr;
    int NumInstances;
    InstanceParser(fin, &instances, &NumInstances);
    cout << "NumInstances: " << NumInstances << endl;

    for(int i = 1; i <= NumInstances; i++){
        cout << "C" << i << " MC" <<  instances[i].LibCellIdx << endl;
    }


    Netlist N(fin);
    N.showNetlist();

    PartitionResult P(NumInstances, N.NumNets, N);

    delete []Dies;
    delete []instances;
    return 0;
}