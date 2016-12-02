#include "dataStructures/trie.h"

Trie::Trie() {
    root = new TrieNode();
    root->c.clear();
    root->key = 'F';
    root->isEnd = false;
}

void Trie::insert(Data *_data) {

    insert(_data, root, 0);
}

void Trie::insert(Data * _data, TrieNode *& _node, size_t cursor) {

    Q_FOREACH(TrieNode* _child, _node->c) {
        if (_child->key == _data->key.toLower().at(cursor)) {
            if (((cursor + 1) < _data->key.size())) {
                insert(_data, _child, ++cursor);
            } else {
                _child->values.insert(_data);
                _child->isEnd = true;
                _child->key_ = _data->key.toLower();
            }
            return;
        }
    }

    TrieNode* tNode = makeNode(_data, cursor);
    _node->c.append(tNode);
    if (!tNode->isEnd) {
        insert(_data, tNode, ++cursor);
    }

}

void Trie::show() {
    show(root);
    qDebug() << size;
}

void Trie::show(TrieNode *_node) {
    if (_node->isEnd) {
        qDebug() << _node->key_ << _node->values.size();
    }
    Q_FOREACH(TrieNode* node, _node->c) {
        show(node);
    }

}

TrieNode* Trie::makeNode(Data * _data, size_t cursor) {
    TrieNode* node = new TrieNode();
    node->key = _data->key.toLower().at(cursor);
    node->c.clear();
    node->isEnd = false;
    if ((cursor + 1) >= _data->key.size()) {
        node->isEnd = true;
        node->key_ = _data->key.toLower();
        node->values.insert(_data);
    }
    size++;
    return node;

}
