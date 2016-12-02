#include "dataStructures/tst.h"

TST::TST() : Tree(){
    root = NULL;
    name = "TST";
}

void TST::insert(Data *_data) {
    insert(_data, root, 0);
}

void TST::insert(Data *_data, TSTNode *& _node, size_t cursor) {
    if (_node == NULL) {
        _node = makeNode(_data, cursor);
    }

    if (_data->key.toLower().at(cursor) > _node->key) {
        insert(_data, _node->gt, cursor);
    } else if (_data->key.toLower().at(cursor) < _node->key) {
        insert(_data, _node->lt, cursor);
    } else {
        if (cursor + 1 < _data->key.size()) {
            insert(_data, _node->eq, cursor + 1);
        } else {
            _node->isEnd = true;
            _node->values.insert(_data);
            _node->key_ = _data->key;
        }
    }
}

TSTNode* TST::makeNode(Data* _data, size_t cursor) {
    TSTNode* node = new TSTNode();
    node->key = _data->key.toLower().at(cursor);
    node->isEnd = false;
    node->eq = node->gt = node->lt = NULL;
    node->key_ = "0";
    size++;
    return node;
}

void TST::show() {
    wordsCount = 0;
    show(root);
}

void TST::show(TSTNode *_node) {
    if (_node == NULL) return;
    show(_node->lt);
    if (_node->isEnd) {
        wordsCount++;
        qDebug() << _node->key_  << "FFF" << _node->values.size();
    }
    show(_node->eq);
    show(_node->gt);
}
