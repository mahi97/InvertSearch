#include "searchthread.h"

SearchThread *search;

SearchThread::SearchThread(QObject* parent)
    : QThread(parent) {
    tree = NULL;

    QFile stop(":/stop");
    stop.open(QIODevice::ReadOnly);
    stopWord = QString(stop.readAll()).split("\n");
    stop.close();

}

void SearchThread::build(QByteArray _data,
                         unsigned int _lineNum,
                         QString _filename) {

    QStringList temp = QString(_data).split(" ");
    for (size_t i{0}; i < temp.size(); i++) {
        if (!stopWord.contains(temp[i])) {
            tree->insert(makeData(temp[i], i, _lineNum, _filename));

        }
    }

}

Data* SearchThread::makeData(const QString &_word,
                             unsigned int _wordNum,
                             unsigned int _lineNum,
                             const QString &_file) {
    Data* data = new Data();
    data->key = _word;
    data->wordNum = _wordNum;
    data->lineNum = _lineNum;
    data->file = _file;
    return data;

}


/* SLOTS */
void SearchThread::slt_chooseTree(ETree _tree) {
    treeEnum = _tree;
    if (tree != NULL)
        delete tree;
    switch (treeEnum) {
    case ETree::BST:
        tree = new BST();
        break;
    case ETree::TST:
        tree = new TST();
        break;
    case ETree::Trie:
        tree = new Trie();
        break;
    default:
        break;
    }

}

void SearchThread::slt_buildFile(BuildMaterial _toBuild) {
    QFile file(_toBuild.file);
    file.open(QIODevice::ReadOnly);
    unsigned int lineNum{0};
    while(file.canReadLine()) {
        build(file.readLine(), lineNum, _toBuild.name);
    }
    qDebug() << file.fileName() << " --> "<< file.readLine();
    file.close();
}
