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

    file = new QFile;
    time = new QTime;
    time->start();
    m_filesCount = 0;

}

SearchThread::~SearchThread() {
}

void SearchThread::run() {
    while(true) {
        int fileTime;
        // Build The Tree
        if (files.size()) {
            fileTime = time->elapsed();
            while (files.size()) {

                m_filesCount++;
                proccesFile(files.front());
                files.pop_front();
                emit sig_buildFinished();
            }
            toShow = true;
            fileTime = time->elapsed() - fileTime;

        }

        // Seearch Words or Phrase
        if (words.size()) {
            int wordTime = time->elapsed();
            list.clear();
            wordList.clear();
            qDebug() << time->elapsed() << "<--";

            while (words.size()) {
                searchWord(words.front());
                words.pop_front();
                emit sig_wordFinished();
            }
            SearchResult* sr = new SearchResult(list, wordList);
            qDebug() << time->elapsed();
            sr->time = time->elapsed() - wordTime;
            emit sig_searchFinished(sr);
        }


        // Show resualt or Summery
        if (treeInvert != NULL) {
            if (toShow) {
                toShow = false;
                Summery* summery = new Summery;
                summery->treeName = treeInvert->getName();
                summery->filesCount = m_filesCount;
                summery->timeTakesToBuild = fileTime;
                summery->treeSize = treeInvert->getSize();
                summery->wordsCount = treeInvert->getWordsCount();
                emit sig_summery(summery);
                reset();
            }
        }
        sleep(1);
        if (time->elapsed() > 10000000000) time->restart();

    }
    exec();
}

void SearchThread::buildInvert(const QByteArray& _data,
                               unsigned int _lineNum,
                               const QString& _filename,
                               bool del) {

    QStringList temp = QString(_data).split(" ");
    for (size_t i{0}; i < temp.size(); i++) {
        if (!stopWord.contains(temp[i].toLower())
                && !temp[i].isEmpty()) {
            if (del) {
                qDebug() << "DSAf";
                treeInvert->remove(makeData(temp[i], i, _lineNum, _filename));
            } else {
                treeInvert->insert(makeData(temp[i], i, _lineNum, _filename));
            }
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
    time->restart();
}

void SearchThread::slt_buildFile(File *_file) {
    doSearch = true;
    files.append(_file);
}

void SearchThread::slt_showWords() {
    showM(" -- Word List -- ", Qt::red);

    Q_FOREACH(QString line, treeInvert->show()) {
        showM(line);
        showM("", Qt::blue);

    }

    showM(" -- Word List END -- ", Qt::red);
}

void SearchThread::slt_search(QString _search) {
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

void SearchThread::proccesFile(File *_file) {
    file->setFileName(_file->path);
    QString tName = _file->name;
    bool del = _file->del;
    file->open(QIODevice::ReadOnly);
    unsigned int lineNum{0};
    QByteArray in = file->readLine();
    while(!in.isNull()) {
        lineNum++;
        buildInvert(in, lineNum, tName, del);
        in = file->readLine();
    }
    file->close();
}

void SearchThread::searchWord(QString _search) {
    LinkedList* llist = treeInvert->search(_search);

    if (llist != NULL) {
        wordList.append(_search);
        list.append(llist->toQList());
    }
}
