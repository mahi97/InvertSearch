#include "dataStructures/bst.h"

BST::BST() : Tree(){
    root = NULL;
    size = 0;
}

void BST::insert(Data* _data) {
    insert(_data, root);
}

void BST::insert(Data *_data, BSTNode*& _node) {
    if (_node == NULL) {
        _node = makeNode(_data);
    } else if (_data->key.toLower() > _node->key) {
        insert(_data, _node->rc);
    } else if (_data->key.toLower() < _node->key) {
        insert(_data, _node->lc);
    } else {
        _node->values.insert(_data);
    }
}

BSTNode* BST::makeNode(Data *_data) {
    BSTNode* node = new BSTNode();
    node->key = _data->key.toLower();
    node->values.insert(_data);
    size++;
    qDebug() << size << node->key;
    return node;
}
