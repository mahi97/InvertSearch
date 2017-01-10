#ifndef BST_H
#define BST_H

#include "dataStructures/tree.h"

struct BSTNode : public Node{
    BSTNode* lc;
    BSTNode* rc;
    int balanceFactor{0};
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
    void insert(Data *_data,
                BSTNode *&_node,
                BSTNode *&_par);

    void addNode(Data *_data,
                 BSTNode *&_node);
    void findBF(BSTNode*& _node);
    int rfindBF(BSTNode*& _node);
    void adjustTree(BSTNode*& _node, BSTNode *&_par);
    void shiftTree(BSTNode*& _node, BSTNode *&_par, bool shiftToLeft);
    void remove(QString, BSTNode*&, BSTNode*&, bool left = false);
    void del(BSTNode*, BSTNode *_parent, bool left);
    QStringList show(BSTNode*, QStringList &_list);
    BSTNode* makeNode(Data*);
    void search(QString _word, LinkedList *&_list, BSTNode*_node);
    BSTNode* root;
};

#endif // BST_H
