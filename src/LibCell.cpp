#include "../inc/LibCell.h"



libCell::libCell(vector<Pin> &v, bool isMacro, int libCellSizeX, int libCellSizeY, int pinCount){
    PinList = v;
    this->isMacro = isMacro;
    this->libCellSizeX = libCellSizeX;
    this->libCellSizeY = libCellSizeY;
    this->pinCount = pinCount;
}

libCell::libCell(){
    ;
}