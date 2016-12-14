#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "base.h"

class LinkedList {

    struct Node {
        Node() {
            data = NULL;
            next = NULL;
        }

        Data* data;
        Node* next;
    };

public:

    LinkedList();

    void insert(Data* _node);
    void append(LinkedList* _llist);
    int remove(Data* _node);
    size_t size();
    QList<Data> toQList();
    LinkedList::Node* getFirst() const;
    LinkedList::Node* getHead() const;

private:
    size_t m_size;
    Node* first;
    Node* head;

};


#endif // LINKEDLIST_H
