#ifndef TREE_H
#define TREE_H

#include "base.h"
#include "dataStructures/linkedlist.h"



//struct Node {
//    QString key;
//    LinkedList values;
//};

class Tree
{

public:
    Tree();
    virtual void insert(Data*)        = 0;
    virtual void show()               = 0;
    /*virtual*/ void del(size_t position) /*= 0*/;
    /*virtual*/ void search(QString)      /*= 0*/;
    /*virtual*/ void search(QStringList)  /*= 0*/;

private:

    PropertyGet(qint64, Size, size);
};

#endif // TREE_H
