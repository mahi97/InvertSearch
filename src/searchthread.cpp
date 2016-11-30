#include "searchthread.h"

SearchThread *search;

SearchThread::SearchThread(QObject* parent)
    : QThread(parent) {
    tree = NULL;

    QFile stop(":/stop");
    stop.open(QIODevice::ReadOnly);
    QString stopString = stop.readAll();
    stop.close();

    QStringList signList;
    signList << ".\n"
             << ","
             << "."
             << "'s"
             << ""
             << "\n"
             << "nt"
             << "?\n"
             << ";"
             << ":"
             << "--"
             << "?"
             << "-"
             << "$"
             << ")";


    stopWord = stopString.split("\r\n");
    stopWord.append(signList);
    qDebug() << this->thread();

    file = new QFile;

}

void SearchThread::run() {
    while(true) {
        if (files.size()) {
            file->setFileName(files.front());
            files.pop_front();
            file->open(QIODevice::ReadOnly);
            unsigned int lineNum{0};
            QByteArray in = file->readLine();
            while(!in.isNull()) {

                QStringList temp = file->fileName().split(QDir::separator());
                build(in, lineNum, temp.back());
                in = file->readLine();
            }
            emit sig_buildFinished();
//            qDebug() << file->fileName();
            file->close();
        } else {
            qDebug() << "hey";
            sleep(1);
        }
    }
//    exec();
}

void SearchThread::build(QByteArray _data,
                         unsigned int _lineNum,
                         QString _filename) {

    QStringList temp = QString(_data).split(" ");
    for (size_t i{0}; i < temp.size(); i++) {
        if (!stopWord.contains(temp[i].toLower())
                && !temp[i].isEmpty()) {
            tree->insert(makeData(temp[i], i, _lineNum, _filename));
        }
    }

}

Data* SearchThread::makeData(const QString &_word,
                             unsigned int _wordNum,
                             unsigned int _lineNum,
                             const QString &_file) {
    //    qDebug() << _word;
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

void SearchThread::slt_buildFile(QString _file) {
    doSearch = true;
    files.append(_file);
}
