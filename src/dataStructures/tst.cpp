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

QStringList TST::show() {
    wordsCount = 0;
    QStringList tList;
    return show(root, tList);
}

QStringList TST::show(TSTNode *_node, QStringList& _list) {
    if (_node == NULL) return _list;
    show(_node->lt, _list);

    if (_node->isEnd) {
        wordsCount++;
        QStringList buffer;
        QString files;
        Q_FOREACH(Data* data, _node->values.toQList()) {
            if (!buffer.contains(data->file)) {
                files.append(data->file);
                files.append(", ");
                buffer.append(data->file);
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
