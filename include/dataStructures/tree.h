#ifndef TREE_H
#define TREE_H

#include "base.h"
#include "dataStructures/linkedlist.h"



struct Node {
    QString key_;
    LinkedList values;
};

class Tree
{

public:
    Tree();
    virtual void insert(Data*)        = 0;
    virtual QStringList show()        = 0;
    /*virtual*/ void del(size_t position) /*= 0*/;
    virtual LinkedList search(QString)      = 0;
    /*virtual*/ void search(QStringList)  /*= 0*/;

private:

    Property(bool, Balanced, balanced);
    PropertyGet(int, Size, size);
    PropertyGet(int, WordsCount, wordsCount);
    PropertyGet(QString, Name, name);
};

#endif // TREE_H
