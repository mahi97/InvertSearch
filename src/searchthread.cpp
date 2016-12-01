#include "searchthread.h"

SearchThread *search;

SearchThread::SearchThread(QObject* parent)
    : QThread(parent) {
    treeInvert = NULL;

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

SearchThread::~SearchThread() {
    qDebug() << "Die";
}

void SearchThread::run() {
    while(true) {
        if (files.size()) {
            file->setFileName(files.front()->path);
            QString tName = files.front()->name;
            files.pop_front();
            file->open(QIODevice::ReadOnly);
            unsigned int lineNum{0};
            QByteArray in = file->readLine();
            while(!in.isNull()) {
                buildInvert(in, lineNum, tName);
                in = file->readLine();
            }
            emit sig_buildFinished();
            file->close();
            toShow = true;
        } else {
            qDebug() << ".";
            if (toShow) {
                toShow = false;
                treeInvert->show();
            }
            sleep(1);
        }
    }
    exec();
}

void SearchThread::buildInvert(const QByteArray& _data,
                         unsigned int _lineNum,
                         const QString& _filename) {

    QStringList temp = QString(_data).split(" ");
    for (size_t i{0}; i < temp.size(); i++) {
        if (!stopWord.contains(temp[i].toLower())
                && !temp[i].isEmpty()) {
            treeInvert->insert(makeData(temp[i], i, _lineNum, _filename));
        }
    }

}

void SearchThread::buildForward(const QByteArray &_data,
                                const QString &_filename) {


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
    if (treeInvert != NULL)
        delete treeInvert;
    switch (treeEnum) {
    case ETree::BST:
        treeInvert = new BST();
        break;
    case ETree::TST:
        treeInvert = new TST();
        break;
    case ETree::Trie:
        treeInvert = new Trie();
        break;
    default:
        break;
    }

}

void SearchThread::slt_buildFile(File *_file) {
    doSearch = true;
    files.append(_file);
}
