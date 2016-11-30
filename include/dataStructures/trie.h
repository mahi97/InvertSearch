#ifndef TRIE_H
#define TRIE_H

#include "dataStructures/tree.h"




class Trie : public Tree
{
    struct TrieNode : Node {
        QList<TrieNode*> c; //Children
    };

public:
    Trie();
};

#endif // TRIE_H
