#ifndef TRIE_H
#define TRIE_H

#include "dataStructures/tree.h"



struct TrieNode : public Node{
    TrieNode() : Node() {
        isEnd = false;
    }

    QList<TrieNode*> c; //Children
    QChar key;
    bool isEnd;
};

class Trie : public Tree
{

public:
    Trie();
    virtual void insert(Data*)       ;
    virtual QStringList show();
//    virtual void del(size_t position);
    virtual LinkedList* search(QString)     ;
//    virtual void search(QStringList) ;

private:
    void search(QString, int, LinkedList *&, TrieNode*);
    void insert(Data*_data, TrieNode *&_node, size_t cursor);
    QStringList show(TrieNode* _node, QStringList &_list);
    TrieNode *makeNode(Data*_data, size_t cursor);
    TrieNode* root;
};

#endif // TRIE_H
