#ifndef BST_H
#define BST_H

#include "tree.h"

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
