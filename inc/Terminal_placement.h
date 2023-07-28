#ifndef TERMINAL_PLACEMENT_H
#define TERMINAL_PLACEMENT_H

#include "Data.h"
#include <bits/stdc++.h>
using namespace std;
class TerminalPlacement{
    private:
        vector<vector<int>> NetExtreme;
        vector<vector<int>> HBlocation;
        int size;
        int dieX, dieY;
        int TerminalSize, spacing;
    public:
        TerminalPlacement(int, int, int, int);
        ~TerminalPlacement();
        void addTerminal(int, int, int, int);
        int getHBlocationX(int);
        int getHBlocationY(int);

        // for placement
        void Placement();
        void makeNodesFile(string);
        void makeNetsFile(string);
        void makeWtsFile(string);
        void makePlFile(string);
        void makeSclFile(string);
        void loadPlacementResult(string);
};

#endif