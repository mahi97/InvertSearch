#include "dataStructures/linkedlist.h"

LinkedList::LinkedList() {

    first = NULL;
    head = NULL;

}

void LinkedList::insert(Data *_node) {
    Node* node = new Node;
    if (first == NULL) {
        first = node;
        first->data = _node;
        head = NULL;
    } else if(head == NULL) {
        head = node;
        head->data = _node;
        first->next = head;
        head->next = NULL;
    } else {
        head->next = node;
        head->next->data = _node;
        head = node;
        node->next = NULL;
    }
    m_size++;
}

size_t LinkedList::size() {
    return m_size;
}
