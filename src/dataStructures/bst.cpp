#include "dataStructures/bst.h"

BST::BST() : Tree(){
    root = NULL;
    name = "BST";
}

void BST::insert(Data* _data) {
    insert(_data, root);
}

void BST::insert(Data *_data, BSTNode*& _node) {
    if (_node == NULL) {
        _node = makeNode(_data);
    } else if (_data->key.toLower() > _node->key_) {
        insert(_data, _node->rc);
    } else if (_data->key.toLower() < _node->key_) {
        insert(_data, _node->lc);
    } else {
        _node->values.insert(_data);
    }
}

BSTNode* BST::makeNode(Data *_data) {
    BSTNode* node = new BSTNode();
    node->key_ = _data->key.toLower();
    node->values.insert(_data);
    size++;
    qDebug() << size << node->key_;
    return node;
}

void BST::show() {
    wordsCount = 0;
    show(root);
}

void BST::show(BSTNode* _node) {
    if (_node == NULL) return;
    wordsCount++;
    show(_node->lc);
    qDebug() << _node->key_ << _node->values.size();
    show(_node->rc);
}
