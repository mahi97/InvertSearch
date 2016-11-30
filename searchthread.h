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
    Trie
};

struct BuildMaterial {
    QString file;
    QString name;
};


class SearchThread : public QThread
{

    Q_OBJECT

public:
    SearchThread(QObject *parent);

private:
    ETree treeEnum;
    Tree* tree;
    QStringList stopWord;

    void build(QByteArray _data, unsigned int _lineNum, QString _filename);
    Data* makeData(const QString& _word,
                  unsigned int _wordNum,
                  unsigned int _lineNum,
                  const QString& _file);
public slots:
    void slt_chooseTree(ETree);
    void slt_buildFile(BuildMaterial);

signals:
    void sig_buildFinished();
};

extern SearchThread* search;

#endif // SEARCHTHREAD_H
