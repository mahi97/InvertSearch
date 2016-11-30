#ifndef TRIE_H
#define TRIE_H

#include "dataStructures/tree.h"



struct TrieNode : Node {
    QList<TrieNode*> c; //Children
};

class Trie : public Tree
{

public:
    Trie();
    virtual void insert(Data*)       ;
    virtual void show();
//    virtual void del(size_t position);
//    virtual void search(QString)     ;
//    virtual void search(QStringList) ;
};

#endif // TRIE_H
