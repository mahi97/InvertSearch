#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

#include <QThread>

#include "base.h"

class SearchThread : public QThread
{

    Q_OBJECT

public:
    SearchThread(QObject *parent);

private:
    ETree tree;

public slots:
    void slt_chooseTree(ETree);
};

extern SearchThread* search;

#endif // SEARCHTHREAD_H
