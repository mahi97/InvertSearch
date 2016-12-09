#include "dataStructures/linkedlist.h"

LinkedList::LinkedList() {

    first = NULL;
    head = NULL;
    m_size = 0;

}

void LinkedList::insert(Data *_node) {
    if (_node == NULL) return;
    Node* node = new Node;
    if (first == NULL
     && head  == NULL) {

        first                 = node;
        first -> data         = _node;
        head                  = first;
        head  -> next         = NULL;

    } else {
        head  -> next         = node;
        head  -> next -> data = _node;
        head                  = head -> next;
        head  -> next         = NULL;
    }
    m_size++;
}

void LinkedList::append(LinkedList *_llist) {
    if (_llist           == NULL
     || _llist -> size() == 0) return;

    m_size      += _llist -> size();
    head -> next = _llist -> getFirst();
    head         = _llist -> getHead();
}

size_t LinkedList::size() {
    return m_size;
}

QList<Data> LinkedList::toQList() {
    QList<Data> tList;
    if (first == NULL) return tList;
    Data datum(first->data);

    tList.append(datum);

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

LinkedList::Node* LinkedList::getHead() const {
    return head;
}
