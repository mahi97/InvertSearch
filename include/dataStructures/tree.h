#ifndef TREE_H
#define TREE_H

#include "base.h"
#include "dataStructures/linkedlist.h"




class Tree
{
protected:
    struct Node {
        QString key;
        LinkedList values;
    };

public:
    Tree();
    void insert(Data*);
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
