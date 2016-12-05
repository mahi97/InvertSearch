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
    time = new QTime;
    time->start();
    m_filesCount = 0;

}

SearchThread::~SearchThread() {
    qDebug() << "Die";
}

void SearchThread::run() {
    while(true) {
        if (files.size()) {
            m_filesCount++;
            file->setFileName(files.front()->path);
            QString tName = files.front()->name;
            files.pop_front();
            file->open(QIODevice::ReadOnly);
            unsigned int lineNum{0};
            QByteArray in = file->readLine();
            while(!in.isNull()) {
                buildInvert(in, lineNum, tName);
                in = file->readLine();
                lineNum++;
            }
            emit sig_buildFinished();
            file->close();
            toShow = true;
        } else if (words.size()) {
            QString _search = words.front();
            words.pop_front();
            LinkedList list = treeInvert->search(_search);
            showM("|-> " + _search, Qt::green);
            Q_FOREACH(Data* data, list.toQList()) {

                showM(QString("F : %1, L : %2, W : %3").arg(data->file)
                      .arg(data->lineNum).arg(data->wordNum));
            }
            emit sig_searchFinished();
        } else {
            if (treeInvert != NULL)
            if (toShow || treeInvert->getBalanced()) {
                toShow = false;
                treeInvert->show();
                Summery* summery = new Summery;
                summery->treeName = treeInvert->getName();
                summery->filesCount = m_filesCount;
                summery->timeTakesToBuild = time->elapsed();
                summery->treeSize = treeInvert->getSize();
                summery->wordsCount = treeInvert->getWordsCount();
                emit sig_summery(summery);
                reset();
            }
            time->restart();
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
        treeInvert->setBalanced(false);
        break;
    case ETree::TST:
        treeInvert = new TST();
        treeInvert->setBalanced(false);
        break;
    case ETree::Trie:
        treeInvert = new Trie();
        break;
    case ETree::BalancedBST:
        treeInvert = new BST();
        treeInvert->setBalanced(true);
    case ETree::BalancedTST:
        treeInvert = new TST();
        treeInvert->setBalanced(true);
    default:
        break;
    }

}

void SearchThread::slt_buildFile(File *_file) {
    doSearch = true;
    files.append(_file);
}

void SearchThread::slt_showWords() {
    qDebug() << "words";
    showM(" -- Word List -- ", Qt::red);

    Q_FOREACH(QString line, treeInvert->show()) {
        showM("----->>", Qt::blue);
        showM(line);
        showM("<<-----", Qt::blue);

    }

    showM(" -- Word List END -- ", Qt::red);
}

void SearchThread::slt_search(QString _search) {
    qDebug() << "haha";
    showM(_search + " <-- Done.", Qt::cyan);
    words.append(_search);

}

void SearchThread::reset() {
    m_filesCount = 0;
}

void SearchThread::showM(QString _line, QColor _color) {
    ShowMaterial* toShow = new ShowMaterial(_line, _color);
    emit sig_show(toShow);

}
