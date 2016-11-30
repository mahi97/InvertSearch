#ifndef BST_H
#define BST_H

#include "dataStructures/tree.h"


class BST : public Tree
{
    class BSTNode : Node{
        BSTNode* lc;
        BSTNode* rc;
    };


public:
    BST();
};

#endif // BST_H
