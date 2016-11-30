#ifndef BST_H
#define BST_H

#include "dataStructures/tree.h"

class BSTNode : Node{
    BSTNode* lc;
    BSTNode* rc;
};

class BST : public Tree
{
public:
    BST();
};

#endif // BST_H
