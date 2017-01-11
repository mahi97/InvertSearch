#include "dataStructures/bst.h"

BST::BST() : Tree(){
    root = NULL;
    name = "BST";
}

void BST::insert(Data* _data) {
    BSTNode* paroot = NULL;
    insert(_data, root, paroot);
}

void BST::remove(QString _data) {
    remove(_data, root, root, false);
}

void BST::insert(Data *_data, BSTNode*& _node, BSTNode *&_par) {
    addNode(_data, _node); //call insert inside
    findBF(_node);
    adjustTreeNode(_node, _par);
}

void BST::adjustTreeNode(BSTNode *&_node, BSTNode *&_par) {
    if (_node == NULL) return;
    bool shift[2]{false, false}; // False = Left, True = Right
    if (_node->balanceFactor > 1) {
        shift[0] = false;
        shift[1] = (_node->lc->balanceFactor < 0); // it can't be 0

    } else if (_node->balanceFactor < -1) {
        shift[0] = true;
        shift[1] = (_node->rc->balanceFactor < 0); // it can't be 0

    } else {
        return;

    }

    if (shift[0] & shift[1])          {       // RR shift
        shiftTree(_node    , _par , shift[0]);     // TRUE

    } else if (!shift[0] & !shift[1]) {       // LL shift
        shiftTree(_node    , _par , shift[0]);     // FALSE

    } else if (shift[0] & !shift[1])  {       // RL shift
        shiftTree(_node->rc, _node, shift[1]);     // FALSE
        shiftTree(_node    , _par , shift[0]);     // TRUE

    } else if (!shift[0] & shift[1])  {       // LR shift
        shiftTree(_node->lc, _node, shift[1]);     // FALSE
        shiftTree(_node    , _par , shift[0]);     // TRUE

    }
}

void BST::adjustTree(BSTNode *&_node, BSTNode *&_par) {
    if (_node == NULL || _par == NULL) return;

    adjustTree(_node->lc, _node);
    adjustTree(_node->rc, _node);
    adjustTreeNode(_node, _par);

}

void BST::shiftTree(BSTNode *&_node, BSTNode*& _par, bool shiftToLeft) {
    if (_node == NULL) return;

    if (_par == NULL) {
        _par = new BSTNode();
        _par->lc = _node;
    }
    BSTNode* tNode = _node;
    bool leftChild = (_par->lc == _node);
    if (shiftToLeft) {
        if (leftChild) {

            _par  -> lc       = tNode -> rc;
            tNode -> rc       = tNode -> rc -> lc;
            _par  -> lc -> lc = tNode;

        } else {
            _par  -> rc       = tNode -> rc;
            tNode -> rc       = tNode -> rc -> lc;
            _par  -> rc -> lc = tNode;

        }
    } else {
        if (leftChild) {
            _par  -> lc       = tNode -> lc;
            tNode -> lc       = tNode -> lc -> rc;
            _par  -> lc -> rc = tNode;

        } else {
            _par  -> rc       = tNode -> lc;
            tNode -> lc       = tNode -> lc -> rc;
            _par  -> rc -> rc = tNode;

        }
    }

    int bf = rfindBF(_node);
    qDebug() << bf;
}

void BST::addNode(Data *_data, BSTNode *&_node) {
    if (_node == NULL) {
        _node = makeNode(_data);
    } else if (_data->key.toLower() > _node->key_) {
        insert(_data, _node->rc, _node);
    } else if (_data->key.toLower() < _node->key_) {
        insert(_data, _node->lc, _node);
    } else {
        _node->values.insert(_data);
    }
}

int BST::rfindBF(BSTNode *&_node) {
    if (_node == NULL) return -1;
    _node->balanceFactor = rfindBF(_node -> lc)
            - rfindBF(_node -> rc);
    _node->balanceFactor = rfindBF(_node -> lc)
            - rfindBF(_node -> rc);

    return abs(_node->balanceFactor);

}

void BST::findBF(BSTNode*& _node) {
    if (_node->lc == NULL
            &&  _node->rc == NULL) {
        _node->balanceFactor = 0;

    } else if (_node->lc == NULL) {
        _node->balanceFactor = (-1)
                - abs(_node->rc->balanceFactor);

    } else if (_node->rc == NULL) {
        _node->balanceFactor = abs(_node->lc->balanceFactor)
                - (-1);

    } else {
        _node->balanceFactor = abs(_node->lc->balanceFactor)
                - abs(_node->rc->balanceFactor);

    }
}

void BST::remove(QString _data,
                 BSTNode *& _node,
                 BSTNode *& _parent,
                 bool left) {

    if (_node == NULL) return;
    remove(_data, _node->rc, _node, false);
    remove(_data, _node->lc, _node, true);

    if (_node->values.remove(_data) == 0) {
        del(_node, _parent, left);
    }
}

void BST::del(BSTNode *_node, BSTNode* _parent, bool left) {

    wordsCount--;

    if (_node == root) {
        if (root->lc == NULL
                &&  root->rc == NULL) {
            delete root;
            root = NULL;

        } else if (root->lc == NULL) {
            BSTNode* temp = root->rc;
            delete root;
            root = temp;

        } else if (root->rc == NULL) {
            BSTNode* temp = root->lc;
            delete root;
            root = temp;
        } else {
            BSTNode* temp = root -> rc;
            BSTNode* tempPar = root;
            while (temp->lc != NULL) {
                tempPar = temp;
                temp = temp->lc;
            }

            if (tempPar != root) {
                tempPar -> lc    = temp  -> rc;
                temp    -> rc    = root  -> rc;
                temp    -> lc    = root  -> lc;
            } else {
                temp    -> lc    = root  -> lc;
            }

            delete root;
            root = temp;
        }

        rfindBF(root);
        adjustTree(root, root);

    } else {
        if (_node->lc == NULL && _node->rc == NULL) { // No Child
            if (left) {
                _parent->lc = NULL;
            } else {
                _parent->rc = NULL;
            }
            delete _node;

        } else if (_node->lc == NULL) { // One Child Left
            if (left) {
                _parent->lc = _node->rc;
            } else {
                _parent->rc = _node->rc;
            }
            delete _node;

        } else if (_node->rc == NULL) { // One Child Right
            if (left) {
                _parent->lc = _node->lc;
            } else {
                _parent->rc = _node->lc;
            }
            delete _node;

        } else { // Two Child
            BSTNode* temp = _node->rc;
            BSTNode* tempPar = _node;
            while (temp->lc != NULL) {
                tempPar = temp;
                temp = temp->lc;
            }

            if (tempPar != _node) {
                tempPar -> lc    = temp  -> rc;
                temp    -> rc    = _node -> rc;
                temp    -> lc    = _node -> lc;
            } else {
                temp -> lc = _node -> lc;
            }

            if (left) {
                _parent -> lc = temp;
            } else {
                _parent -> rc = temp;
            }

            delete _node;
        }

        rfindBF(_parent);
        if (left) {
            adjustTree(_parent->lc, _parent);

        } else {
            adjustTree(_parent->rc, _parent);

        }
    }


}

BSTNode* BST::makeNode(Data *_data) {
    BSTNode* node = new BSTNode();
    node->key_ = _data->key.toLower();
    node->values.insert(_data);
    node->balanceFactor = 0;
    size++;
    wordsCount++;
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
