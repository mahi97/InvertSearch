#ifndef TST_H
#define TST_H

#include "dataStructures/tree.h"


struct TSTNode {
    QChar key;
    bool isEnd = 1;
    TSTNode *lt, *eq, *gt;
    LinkedList value;
    QString key_;
};

class TST : public Tree
{


public:
    TST();
    virtual void insert(Data*)       ;
    virtual void show();
//    virtual void del(size_t position);
//    virtual void search(QString)     ;
//    virtual void search(QStringList) ;

private:
    void insert(Data *, TSTNode*&, size_t cursor);
    void show(TSTNode* _node);
    TSTNode* makeNode(Data* _data, size_t cursor);

    TSTNode* root;

};

#endif // TST_H
