#include "inc/Data.h"

int main(int argc, char *argv[]){

    if(argc != 3){
        printf("usage: %s <input.txt> <output.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    //read the technoology info
    Data D(*(argv + 1));
    D.Display();
    D.GeneratePartitionGraph();
    D.PartitionUntilFindSolution();

    return 0;
}