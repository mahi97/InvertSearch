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

int LinkedList::remove(Data* _node) {
    if (_node == NULL
            || (first == NULL && head == NULL)) return m_size;

    Node* cursor = first;
    Node* last = NULL;
    if (m_size == 1) {
        if (cursor->data = _node) {
            first = NULL;
            head  = NULL;
            m_size = 0;
            delete cursor;
        }

    } else {

        for (size_t i{};i < m_size; i++) {
            if (cursor == NULL) break;
            if (*(cursor->data) == *_node) {
                m_size--;
                if (i == 0) {
                    first = first -> next;
                    delete cursor;
                    break;
                } else if (i == m_size - 1) {
                    head = last;
                    delete cursor;
                    break;
                } else {
                    last -> next = cursor -> next;
                    delete cursor;
                    break;
                }

            } else {
                last = cursor;
                cursor = cursor->next;
            }
        }
    }
    return m_size;
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
