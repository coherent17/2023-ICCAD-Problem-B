#include "../inc/Partition.h"

PartitionResult::PartitionResult(int NumInstances, int NumNets, Netlist& N){
    FILE *shmetisInput = fopen("Netlist.hgr", "w");
	fprintf(shmetisInput, "%d %d\n", NumNets, NumInstances);

    for(int i = 1; i <= NumNets; i++){
        for(int j = 1; j <= N.Nets[i].numPins; j++){
            fprintf(shmetisInput, "%d ", N.Nets[i].LibCellIdx[j]);
        }
        fprintf(shmetisInput, "\n");
    }
    fclose(shmetisInput);

    system("chmod +x lib/hmetis/shmetis");
	char command[100];
	sprintf(command,"./lib/hmetis/shmetis Netlist.hgr 2 5 > log.txt");
	system(command);
}

PartitionResult::~PartitionResult(){

}
