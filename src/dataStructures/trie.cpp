#include "dataStructures/trie.h"

Trie::Trie() {
    root = new TrieNode();
    root->c.clear();
    root->key = 'F';
    root->isEnd = false;
    size++;
    name = "Trie";
    balanced = false;
}

void Trie::insert(Data *_data) {

    insert(_data, root, 0);
}

void Trie::remove(QString _file) {
    remove(_file, root, root, 0);
}

void Trie::insert(Data * _data, TrieNode *& _node, size_t cursor) {

    Q_FOREACH(TrieNode* _child, _node->c) {
        if (_child->key == _data->key.toLower().at(cursor)) {
            if (((cursor + 1) < _data->key.size())) {
                insert(_data, _child, ++cursor);
            } else {
                if (_child->values.size() == 0) {
                    wordsCount++;
                }
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

void Trie::remove(QString     _file,
                  TrieNode *& _node,
                  TrieNode *& _parent,
                  int         _link) {

    if (_node == NULL) return;

    int counter{};
    Q_FOREACH (TrieNode* node, _node->c) {
        remove(_file, node, _node, counter);
        counter++;
    }

    if (_node->isEnd) {
        if (_node->values.remove(_file) == 0) {
            del(_node, _parent, _link);
        }
    }
}

void Trie::del(TrieNode * _node, TrieNode * _parent, int _link) {
    wordsCount--;
    _node->isEnd = false;
    _node->key_ = "";

    if (_node->c.isEmpty()) {
        _parent -> c[_link] = NULL;
        delete _node;
    }
}

QStringList Trie::show() {
    QStringList list;
    return show(root, list);
}

LinkedList* Trie::search(QString _word) {
    LinkedList* list = new LinkedList;
    search(_word, 0, list, root);
    if (list->size() == 0) list = NULL;
    return list;
}

void Trie::search(QString _word,
                  int _index,
                  LinkedList* & _list,
                  TrieNode *_node) {
    if (_node == NULL || _index > _word.size()) return;

    if (_word == _node->key_) {
        _list = &_node->values;
        return;
    } else {
        Q_FOREACH(TrieNode* c, _node->c) {
            if (c->key == _word[_index]) {

                search(_word, ++_index, _list, c);
                break;
            }
        }
    }
}

QStringList Trie::show(TrieNode *_node, QStringList& _list) {
    if (_node == NULL) return _list;

    if (_node->isEnd) {
//        wordsCount++;
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
        QString name = _node->key_;
        files = QString("|%1 -> ").arg(name) + files;
        _list.append(files);
    }
    Q_FOREACH(TrieNode* node, _node->c) {
        show(node, _list);
    }
    return _list;
}

TrieNode* Trie::makeNode(Data * _data, size_t cursor) {
    TrieNode* node = new TrieNode();
    node->key = _data->key.toLower().at(cursor);
    node->c.clear();
    node->isEnd = false;
    if ((cursor + 1) >= _data->key.size()) {
        if (node->values.size() == 0) {
            wordsCount++;
        }
        node->isEnd = true;
        node->key_ = _data->key.toLower();
        node->values.insert(_data);
    }
    size++;
    return node;

}
