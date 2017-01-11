#include "dataStructures/tst.h"

TST::TST() : Tree(){
    root = NULL;
    name = "TST";
}

void TST::insert(Data *_data) {
    insert(_data, root, 0);
}

void TST::remove(QString _file) {
    remove(_file, root, root, 0);
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
            if (_node->values.size() == 0) {
                wordsCount++;
            }
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
    // TODO : why remove for every one
    remove(_file, _node->lt, _node,  -1);
    remove(_file, _node->eq, _node,  0);
    remove(_file, _node->gt, _node,  1);
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
