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

void LinkedList::append(LinkedList *_llist) {
    size_t size = _llist->size();
    if (size) {
        head->next = _llist->getFirst();
        m_size++;
        while (size) {
            head = head->next;
            size--;
            m_size++;
        }
    }
}

size_t LinkedList::size() {
    return m_size;
}

QList<Data*> LinkedList::toQList() {
    QList<Data*> tList;
    if (first == NULL) return tList;
    tList.append(first->data);
    if (head == NULL) return tList;

    Node* tNode = first;
    for (size_t i{0}; i < m_size ; i++) {
        if (tNode->next == NULL) break;
        tList.append(tNode->next->data);
        tNode = tNode->next;
    }
    return tList;
}

LinkedList::Node* LinkedList::getFirst() const {
    return first;
}
