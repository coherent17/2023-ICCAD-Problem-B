#include "inc/Data.h"

int main(int argc, char *argv[]){

    if(argc != 3){
        printf("usage: %s <input.txt> <output.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    srand(time(NULL));
    //read the technoology info
    Data D(*(argv + 1));
    if(DEBUG)
        D.Display();
    D.GeneratePartitionGraph();

    //make sure the executable permission is right
    system("chmod +x lib/hmetis/shmetis");
    D.PartitionUntilFindSolution();
    // if(DEBUG)
    //   D.showPartitionResult();
    
    D.LoadPartition();

    D.Placement();

    // if(DEBUG)
    //     D.showPlacementResult();

    D.terminalPlacement();

    D.output(argv[2]);
    return 0;
}