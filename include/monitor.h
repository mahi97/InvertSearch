#ifndef MONITOR_H
#define MONITOR_H

#include <QTextEdit>
#include <QScrollBar>
#include <QSyntaxHighlighter>

#include "base.h"
#include "searchthread.h"

class Monitor : public QTextEdit {

    Q_OBJECT

public:
    Monitor(QWidget* parent);

private:
    QColor defaultColor;
    QSyntaxHighlighter* synHigh;
public slots:
    void slt_summery(Summery*);
    void slt_show(ShowMaterial*);
};

extern Monitor* monitor;

#endif // MONITOR_H
