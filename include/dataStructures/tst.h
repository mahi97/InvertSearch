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
    int balanceFactor{0};
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
    void        insert        (Data *, TSTNode*&, TSTNode *&, size_t);
    void        search        (QString, int, LinkedList* &, TSTNode*);
    void        remove        (QString, TSTNode*&, TSTNode*&, int);
    void        del           (TSTNode *, TSTNode*, int);
    void        findBF        (TSTNode *& _node);
    int         rFindBF       (TSTNode *& _node);
    void        adjustTree    (TSTNode *&);
    void        adjustTreeNode(TSTNode *&, TSTNode *&);
    void        shiftTree     (TSTNode *&, TSTNode *&, bool);
    TSTNode*    makeNode      (Data*, size_t);
    QStringList show          (TSTNode*, QStringList &);

    TSTNode* root;

};

#endif // TST_H
