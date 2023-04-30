#ifndef _DIE_H_
#define _DIE_H_

#include "../inc/Technology.h"

#define OCCUPIED 1
#define UNOCCUPIED 0


class Die{
    public:
        //no need for lowerLeftX, lowerLeftY [always be 0 0]
        //http://iccad-contest.org/Document/Problems/QA/Problem%20B_QA_0428.pdf (Q4-3)
        int upperRightX;
        int upperRightY;
        int util;
        int rowLength;
        int rowHeight;
        int repeatCount;
        Tech* techptr;
        bool **placementState;  //1: occupied, 0: not-occupied
        
        Die();
        ~Die();
        friend void DieParser(ifstream& fin, Die *Dies, Technology& T);
        friend ostream& operator<<(ostream& out, const Die &D);
};

#endif