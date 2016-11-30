#ifndef TST_H
#define TST_H

#include "dataStructures/tree.h"


struct TSTNode : Node {
    TSTNode* c[3];
};

class TST : public Tree
{


public:
    TST();
    virtual void insert(Data*)       ;
//    virtual void del(size_t position);
//    virtual void search(QString)     ;
//    virtual void search(QStringList) ;
};

#endif // TST_H
