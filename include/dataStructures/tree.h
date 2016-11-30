#ifndef TREE_H
#define TREE_H

#include "base.h"

struct Node {
    QString key;
    QStringList files;
};

class Tree
{
public:
    Tree();
    void insert(Node*);
    void del(size_t position);
    void search(QString);
    void search(QStringList);
    void show();

private:

    QVector<Node*> nodes;

    PropertyGet(qint64, size, Size);
    Property(Node*, root, Root);
};

#endif // TREE_H
