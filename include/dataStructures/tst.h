#ifndef TST_H
#define TST_H

#include "dataStructures/tree.h"


struct TSTNode : public Node{
    TSTNode () {
        lt = eq = gt = NULL;
    }

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
    void        insert  (Data *, TSTNode*&, size_t);
    void        search  (QString, int, LinkedList* &, TSTNode*);
    void        remove  (QString, TSTNode*&, TSTNode*&, int);
    void        del     (TSTNode*, TSTNode*, int);
    TSTNode*    makeNode(Data*, size_t);
    QStringList show    (TSTNode*, QStringList &);


    TSTNode* root;

};

#endif // TST_H
