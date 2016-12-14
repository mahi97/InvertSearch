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
    virtual void remove(Data*);
    virtual QStringList show();

    virtual LinkedList* search(QString)     ;

private:
    void insert(Data *, TSTNode*&, size_t cursor);
    QStringList show(TSTNode* _node, QStringList &_list);
    TSTNode* makeNode(Data* _data, size_t cursor);
    void search(QString, int, LinkedList* &, TSTNode*);

    TSTNode* root;

};

#endif // TST_H
