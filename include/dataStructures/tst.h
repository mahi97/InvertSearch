#ifndef TST_H
#define TST_H

#include "dataStructures/tree.h"


struct TSTNode : public Node{
    QChar key;
    bool isEnd;
    TSTNode *lt, *eq, *gt;
};

class TST : public Tree
{


public:
    TST();
    virtual void insert(Data*)       ;
    virtual QStringList show();
//    virtual void del(size_t position);
//    virtual void search(QString)     ;
//    virtual void search(QStringList) ;

private:
    void insert(Data *, TSTNode*&, size_t cursor);
    QStringList show(TSTNode* _node, QStringList &_list);
    TSTNode* makeNode(Data* _data, size_t cursor);

    TSTNode* root;

};

#endif // TST_H
