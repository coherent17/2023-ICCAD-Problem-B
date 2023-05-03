#ifndef _PARTITION_H_
#define _PARTITION_H_

#include "Netlist.h"

class PartitionResult{
    public:
        int NumInstances;
        int NumNets;
        bool *partition_result;     //0: Top Die, 1: Bottom Die
        


    public:
        PartitionResult(int NumInstances, int NumNets, Netlist& N);
        ~PartitionResult();

};

#endif