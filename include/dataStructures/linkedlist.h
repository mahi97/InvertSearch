#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "base.h"

class LinkedList {

    struct Node {
        Data data;
        Node* next;
    };

public:

    LinkedList() {
        first = NULL;
        head = NULL;
    }

    void insert(Data _node);
    void remove();
    Node* pop();
    Node* at(int _index);

private:

    Node* first;
    Node* head;

};


#endif // LINKEDLIST_H
