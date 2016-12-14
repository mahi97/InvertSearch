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
    virtual void        insert(Data*);
    virtual void        remove(QString);
    virtual QStringList show();
    virtual LinkedList* search(QString);


private:
    void insert(Data *_data, BSTNode *&_node);
    void remove(QString, BSTNode*&, BSTNode*&, bool left = false);
    void del(BSTNode*, BSTNode *_parent, bool left);
    QStringList show(BSTNode*, QStringList &_list);
    BSTNode* makeNode(Data*);
    void search(QString _word, LinkedList *&_list, BSTNode*_node);
    BSTNode* root;
};

#endif // BST_H
