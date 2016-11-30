#ifndef TST_H
#define TST_H

#include "tree.h"

struct TSTNode : Node {
    TSTNode* c[3];
};


class TST : public Tree
{
public:
    TST();
};

#endif // TST_H
