#include "dataStructures/hash.h"

Hash::Hash() : Tree() {
    for (size_t i{}; i < SIZE; i++) {
        table[i].key = i;
    }
}

void Hash::insert(Data *_data) {
    unsigned char tKey = hashFunction(_data->key);
    
    for (int i{0}; i < table[tKey].list.size(); i++) {
        if (table[tKey].list.at(i)->key_.toLower() == _data->key.toLower()) {
            table[tKey].list.at(i)->values.insert(_data);
            return;
        }
    }
    HNode* tempNode = makeNode(_data);
    table[tKey].list.append(tempNode);
    wordsCount++;

    qDebug() << tKey;
    qDebug() << table[tKey].list.size();
    for (int i {}; i < table[tKey].list.size(); i++) {
        qDebug () << table[tKey].list.at(i)->key_;
    }
    qDebug() << "``````";

}

HNode* Hash::makeNode(Data* _data) {
    HNode* node = new HNode();
    node->key_ = _data->key.toLower();
    node->values.insert(_data);
    size++;
    return node;
}

void Hash::remove(QString _filename) {
    for (size_t i{}; i < SIZE; i++) {
        for (size_t j{}; j < table[i].list.size(); j++) {
            if (table[i].list[j]->values.remove(_filename) == 0) {
                table[i].list.removeAt(j);
            }
        }
    }
}

unsigned char Hash::hashFunction(QString& _data) {
    QString h = _data;
    return h.toStdString().c_str()[0];
    //    return 0;
}

LinkedList* Hash::search(QString _key) {
    unsigned char tKey = hashFunction(_key);
    for (size_t i {}; i < table[tKey].list.size(); i++) {
        if (table[tKey].list.at(i)->key_ == _key) {
            LinkedList* tList = &table[tKey].list.at(i)->values;
            if (table[tKey].list.at(i)->values.size() == 0) tList = NULL;
            return tList;
        }
    }
}

QStringList Hash::show() {
    QStringList tList;
    for (size_t i {}; i < SIZE; i++) {
        for (size_t j {};j < table[i].list.size(); j++) {
            QStringList buffer;
            QString files;
            QString tStr;
            Q_FOREACH(Data data, table[i].list[j]->values.toQList()) {
                if (!buffer.contains(data.file)) {
                    QString name = data.file;
                    name.chop(4);
                    files.append(name);
                    files.append(", ");
                    buffer.append(data.file);
                }
            }
            files.chop(1);

            tStr = QString ("> %1 -> ").arg(table[i].list[j]->key_) + files;
            tList.append(tStr);
        }
    }
    return tList;
}
