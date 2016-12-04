#ifndef BST_H
#define BST_H

#include "dataStructures/tree.h"

struct BSTNode : public Node{
    BSTNode* lc;
    BSTNode* rc;
};

class BST : public Tree
{


public:
    BST();
    virtual void insert(Data*);
    QStringList show();
//    virtual void del(size_t position);
//    virtual void search(QString);
//    virtual void search(QStringList);

private:
    void insert(Data *_data, BSTNode *&_node);
    QStringList show(BSTNode*, QStringList &_list);
    BSTNode* makeNode(Data*);
    BSTNode* root;
};

#endif // BST_H
