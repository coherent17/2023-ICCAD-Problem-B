#include "inc/Data.h"

#define DEBUG 1

int main(int argc, char *argv[]){

    if(argc != 3){
        printf("usage: %s <input.txt> <output.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    //read the technoology info
    Data D(*(argv + 1));
    // if(DEBUG)
    //     D.Display();
    // D.GeneratePartitionGraph();
    // D.PartitionUntilFindSolution();
    // if(DEBUG)
    //     D.showPartitionResult();
    return 0;
}