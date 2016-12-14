#include "dataStructures/bst.h"

BST::BST() : Tree(){
    root = NULL;
    name = "BST";
}

void BST::insert(Data* _data) {
    insert(_data, root);
}

void BST::remove(Data * _data) {
    remove(_data, root, root, 0);
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

void BST::remove(Data *_data, BSTNode *& _node, BSTNode *& _parent, bool left) {
    if (_node == NULL) {
        qDebug() << "What";
        return;
    } else if (_data->key.toLower() > _node->key_) {
        remove(_data, _node->rc, _node, false);
    } else if (_data->key.toLower() < _node->key_) {
        remove(_data, _node->lc, _node, true);
    } else {
        if (_node->values.remove(_data) == 0) {
//            del(_node, _parent, left);
        }
    }
}

void BST::del(BSTNode *_node, BSTNode* _parent, bool left) {
    if (_node == root) {
        // TODO : fix this !
        qDebug() << "Please Don't remove root";
        return;
    }
    if (_node->lc == NULL && _node->rc == NULL) { // No Child
        if (left) {
            _parent->lc == NULL;
        } else {
            _parent->rc == NULL;
        }
        delete _node;
    } else if (_node->lc == NULL) { // One Child Left
        if (left) {
            _parent->lc == _node->rc;
        } else {
            _parent->rc == _node->rc;
        }
        delete _node;
    } else if (_node->rc == NULL) { // One Child Right
        if (left) {
            _parent->lc == _node->lc;
        } else {
            _parent->rc == _node->lc;
        }
    } else { // Two Child
        BSTNode* temp = _node->rc;
        BSTNode* tempPar = _node;
        while (temp->lc != NULL) {
            tempPar = temp;
            temp = temp->lc;
        }

        tempPar -> lc    = temp  -> rc;
        temp    -> rc    = _node -> rc;
        temp    -> lc    = _node -> lc;
        delete _node;

    }
}

BSTNode* BST::makeNode(Data *_data) {
    BSTNode* node = new BSTNode();
    node->key_ = _data->key.toLower();
    node->values.insert(_data);
    size++;
    return node;
}

void BST::search(QString _word, LinkedList* &_list, BSTNode *_node) {
    if (_node == NULL) return;
    if (_word == _node->key_) {
        _list = &_node->values;
        return;
    } else if (_word < _node->key_) {
        search(_word, _list, _node->lc);
    } else {
        search(_word, _list, _node->rc);
    }
}
QStringList BST::show() {
    wordsCount = 0;
    QStringList tlist;
    return show(root, tlist);
}

LinkedList* BST::search(QString _word) {
    LinkedList* list = new LinkedList;
    search(_word, list, root);
    if (list->size() == 0) list = NULL;
    return list;
}

QStringList BST::show(BSTNode* _node, QStringList& _list) {
    if (_node == NULL) return _list;
    QString tStr;
    QString files;
    wordsCount++;
    show(_node->lc, _list);

    QStringList buffer;
    Q_FOREACH(Data data, _node->values.toQList()) {
        if (!buffer.contains(data.file)) {
            QString name = data.file;
            name.chop(4);
            files.append(name);
            files.append(", ");
            buffer.append(data.file);
        }
    }
    files.chop(1);

    tStr = QString ("> %1 -> ").arg(_node->key_) + files;
    _list.append(tStr);

    show(_node->rc, _list);
    return _list;
}
