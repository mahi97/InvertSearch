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
    virtual void        insert(Data*);
    virtual void        remove(QString);
    virtual LinkedList* search(QString);
    virtual QStringList show();


private:
    void        insert  (Data *,
                         TSTNode*&,
                         size_t);

    void        search  (QString,
                         int,
                         LinkedList* &,
                         TSTNode*);

    TSTNode*    makeNode(Data*,
                         size_t);

    QStringList show    (TSTNode*,
                         QStringList &);

    TSTNode* root;

};

#endif // TST_H
