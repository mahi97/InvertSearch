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
    ~Monitor();
private:
    QColor defaultColor;
public slots:
    void slt_summery(Summery*);
    void slt_show(ShowMaterial*);
    void slt_search(LinkedList*);
};

extern Monitor* monitor;

#endif // MONITOR_H
