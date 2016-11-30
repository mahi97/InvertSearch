#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "base.h"

class LinkedList {

    struct Node {
        Data* data;
        Node* next;
    };

public:

    LinkedList();

    void insert(Data* _node);
    void remove();
    Node* pop();
    Node* at(int _index);
    size_t size();

private:
    size_t m_size;
    Node* first;
    Node* head;

};


#endif // LINKEDLIST_H
