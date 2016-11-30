#ifndef TERMINALDOCKWIDGET_H
#define TERMINALDOCKWIDGET_H

#include <QDockWidget>
#include <QWidget>
#include <QTextEdit>


#include "base.h"
#include "terminal/ReplWidget.h"

class TerminalDockWidget : public QDockWidget
{

    Q_OBJECT

public:
    TerminalDockWidget(QWidget* parent);
    ReplWidget *repl;
private:
    void proccesAdd   (const QStringList &);
    void proccesDel   (const QStringList &);
    void proccesUpdt  (const QStringList &);
    void proccesList  (const QStringList &);
    void proccesSrch  (const QStringList &);

public slots:
    void procces(QString);
signals:
    void resualtReady(QString);
};

#endif // TERMINALDOCKWIDGET_H
