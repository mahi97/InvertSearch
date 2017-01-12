#include "dataStructures/tst.h"

TST::TST() : Tree(){
    root = NULL;
    name = "TST";
}

void TST::insert(Data *_data) {
    TSTNode* paroot = NULL;
    qDebug () << _data->key;
    insert(_data, root, paroot, 0);
}

void TST::remove(QString _file) {
    remove(_file, root, root, 0);
}

void TST::insert(Data *_data, TSTNode *& _node, TSTNode*& _par, size_t cursor) {
    if (_node == NULL) {
        _node = makeNode(_data, cursor);
    }

    if (_data->key.toLower().at(cursor) > _node->key) {
        insert(_data, _node->gt, _node, cursor);

    } else if (_data->key.toLower().at(cursor) < _node->key) {
        insert(_data, _node->lt, _node, cursor);

    } else {
        if (cursor + 1 < _data->key.size()) {
            insert(_data, _node->eq, _node, cursor + 1);

        } else {
            if (_node->values.size() == 0) {
                wordsCount++;

            }
            _node->isEnd = true;
            _node->values.insert(_data);
            _node->key_ = _data->key;

        }
    }


    findBF(_node);
    qDebug() << _node->key << " --- " << _node->balanceFactor;
    adjustTreeNode(_node, _par);

}

void TST::adjustTreeNode(TSTNode *& _node, TSTNode *& _par) {
    if (_node == NULL) return;



    bool shift[2]{false, false}; // False = Left, True = Right
    if (_node->balanceFactor > 1) {
        shift[0] = false;
        shift[1] = (_node->lt->balanceFactor < 0); // it can't be 0

    } else if (_node->balanceFactor < -1) {
        shift[0] = true;
        shift[1] = (_node->gt->balanceFactor < 0); // it can't be 0

    } else {
        return;

    }

    if (shift[0] & shift[1])          {        // RR shift
        shiftTree(_node    , _par , shift[0]); // TRUE

    } else if (!shift[0] & !shift[1]) {        // LL shift
        shiftTree(_node    , _par , shift[0]); // FALSE

    } else if (shift[0] & !shift[1])  {        // RL shift
        shiftTree(_node->gt, _node, shift[1]); // FALSE
        shiftTree(_node    , _par , shift[0]); // TRUE

    } else if (!shift[0] & shift[1])  {        // LR shift
        shiftTree(_node->lt, _node, shift[1]); // TRUE
        shiftTree(_node    , _par , shift[0]); // FALSE

    }


}

void TST::shiftTree(TSTNode *& _node, TSTNode *& _par, bool _shiftToLeft) {
    if (_node == NULL) return;

    bool changeRoot = false;
    if (_par == NULL) {
        _par = new TSTNode();
        _par->lt = _node;
        changeRoot = true;
    }
    TSTNode* tNode = _node;

//    TSTNode*& tParChild = ((_par -> lt == _node) ? _par -> lt : _par -> eq);
//    tParChild = ((_par -> gt == _node) ? _par -> gt : tParChild);
    int c{};
    if (_par -> lt == _node) {
        c = -1;
    } else if (_par -> gt == _node) {
        c =  1;
    } else {
        c =  0;
    }

    if (_shiftToLeft) {
        if (c == -1) {
            _par       -> lt = tNode       -> gt;
            tNode      -> gt = tNode -> gt -> lt;
            _par -> lt -> lt = tNode;

        } else if (c == 1) {
            _par       -> gt = tNode       -> gt;
            tNode      -> gt = tNode -> gt -> lt;
            _par -> gt -> lt = tNode;

        } else {
            _par       -> eq = tNode       -> gt;
            tNode      -> gt = tNode -> gt -> lt;
            _par -> eq -> lt = tNode;

        }


    } else {
        if (c == -1) {
            _par       -> lt = tNode       -> lt;
            tNode      -> lt = tNode -> lt -> gt;
            _par -> lt -> gt = tNode;

        } else if (c == 1) {
            _par       -> gt = tNode       -> lt;
            tNode      -> lt = tNode -> lt -> gt;
            _par -> gt -> gt = tNode;

        } else {
            _par       -> eq = tNode       -> lt;
            tNode      -> lt = tNode -> lt -> gt;
            _par -> eq -> gt = tNode;

        }

    }

    if (changeRoot) {
        if (c == -1) {
            root = _par -> lt;

        } else if (c == 1) {
            root = _par -> gt;

        } else {
            _par = _par -> eq;

        }
    }

    int bf = rFindBF(_node);
    qDebug() << bf;
}

void TST::findBF(TSTNode *&_node) {
    if (_node->lt == NULL
    &&  _node->gt == NULL) {
        _node->balanceFactor = 0;

    } else if (_node->lt == NULL) {
        _node->balanceFactor = (-1)
                             - abs(_node->gt->balanceFactor);

    } else if (_node->gt == NULL) {
        _node->balanceFactor = abs(_node->lt->balanceFactor)
                             - (-1);

    } else {
        _node->balanceFactor = abs(_node->lt->balanceFactor)
                             - abs(_node->gt->balanceFactor);

    }
}

int TST::rFindBF(TSTNode *&_node) {
    if (_node == NULL) return -1;
    rFindBF(_node -> eq);
    _node -> balanceFactor = rFindBF(_node -> lt)
                           - rFindBF(_node -> gt);
    return abs(_node->balanceFactor);
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

QStringList TST::show() {
    QStringList tList;
    return show(root, tList);
}

LinkedList* TST::search(QString _word) {
    LinkedList* list = new LinkedList;
    search(_word, 0, list, root);
    if (list->size() == 0) list = NULL;

    return list;
}

void TST::search(QString _word,int _index , LinkedList* &_list, TSTNode*_node) {
    if (_node == NULL || _index >= _word.size()) return;

    if (_word == _node->key_) {
        _list = &_node->values;
        return;
    } else if (_word[_index] < _node->key) {
        search(_word, _index, _list, _node->lt);

    } else if (_word[_index] == _node->key) {
        search(_word, ++_index, _list, _node->eq);

    } else {
        search(_word, _index, _list, _node->gt);

    }
}

void TST::remove(QString _file,
                 TSTNode *& _node,
                 TSTNode *& _parent,
                 int _link) {

    if (_node == NULL) return;
    remove(_file, _node->lt, _node,  -1);
    remove(_file, _node->eq, _node,   0);
    remove(_file, _node->gt, _node,   1);
    if (_node->isEnd) {
        if (_node->values.remove(_file) == 0) {
            del(_node, _parent, _link);
        }
    }


}

void TST::del(TSTNode * _node, TSTNode * _parent, int _link) {
    wordsCount--;
    _node->isEnd = false;
    _node->key_ = "";
    if (_node -> gt == NULL
    &&  _node -> eq == NULL
    &&  _node -> lt == NULL) {

        if (_link == -1) {
            _parent -> lt = NULL;
        } else if (_link == 0) {
            _parent -> eq = NULL;
        } else if (_link == 1) {
            _parent -> gt = NULL;
        } else {
            qWarning() << "TST (DELETE) -> Wrong Linking ";
        }

        delete _node;

    }
}

QStringList TST::show(TSTNode *_node, QStringList& _list) {
    if (_node == NULL) return _list;
    show(_node->lt, _list);

    if (_node->isEnd) {
        QStringList buffer;
        QString files;
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
        files = QString("|%1 -> ").arg(_node->key_) + files;
        _list.append(files);
    }
    show(_node->eq, _list);
    show(_node->gt, _list);

    return _list;
}
