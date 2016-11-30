#ifndef TRIE_H
#define TRIE_H

#include "tree.h"

struct TrieNode : Node {
    QList<TrieNode*> c; //Children
};


class Trie : public Tree
{
public:
    Trie();
};

#endif // TRIE_H
