#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

#include <QThread>
#include <QDir>
#include <QFile>

#include "base.h"
#include "trees.h"

enum class ETree {
    None,
    BST,
    TST,
    Trie,
    BalancedBST,
    BalancedTST
};


class SearchThread : public QThread
{

    Q_OBJECT

public:
    SearchThread(QObject *parent);
    ~SearchThread();
    bool doSearch{false};
private:
    ETree treeEnum;
    Tree* treeInvert;
    Tree* treeForward;
    QStringList stopWord;
    QFile* file;
    QList<File*> files;
    QTime *time;
    void run();
    bool toShow{false};
    void buildInvert(const QByteArray &_data, unsigned int _lineNum, const QString &_filename);
    void buildForward(const QByteArray &_data, const QString &_filename);
    Data* makeData(const QString& _word,
                  unsigned int _wordNum,
                  unsigned int _lineNum,
                  const QString& _file);
    void reset();
    int m_filesCount;
    void showM(QString _line, QColor _color = Qt::black);

public slots:
    void slt_chooseTree(ETree);
    void slt_buildFile(File*);
    void slt_showWords();

signals:
    void sig_buildFinished();
    void sig_summery(Summery*);
    void sig_show(ShowMaterial*);
};

extern SearchThread* search;

#endif // SEARCHTHREAD_H
