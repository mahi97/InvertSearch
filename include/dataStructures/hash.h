#ifndef HASH_H
#define HASH_H

#include "tree.h"

struct HashNode {
    QList<Node*> list;
    char key;
};

class Hash : public Tree{
public:
    Hash();
    ~Hash();

    virtual void insert(Data *);
    virtual void remove(QString);
    virtual QStringList show();
    virtual LinkedList* search(QString);

    static constexpr size_t SIZE{256};
private:
    unsigned char hashFunction(QString &);
    Node* makeNode(Data *);

    HashNode table[SIZE];

};

#endif // HASH_H
