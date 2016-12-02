#ifndef MONITOR_H
#define MONITOR_H

#include <QTextEdit>
#include <QScrollBar>

#include "base.h"
#include "searchthread.h"

class Monitor : public QTextEdit {

    Q_OBJECT

public:
    Monitor(QWidget* parent);

private:

public slots:
    void slt_summery(Summery*);

};

extern Monitor* monitor;

#endif // MONITOR_H
