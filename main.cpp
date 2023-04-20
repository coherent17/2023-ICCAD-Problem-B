#include "inc/Data.h"


int main(int argc, char *argv[]){
    Data d(*(argv + 1));
    d.showData();
    return 0;
}