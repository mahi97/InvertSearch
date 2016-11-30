#ifndef TST_H
#define TST_H

#include "dataStructures/tree.h"



class TST : public Tree
{

    struct TSTNode : Node {
        TSTNode* c[3];
    };

public:
    TST();
};

#endif // TST_H
