#include "terminaldockwidget.h"

TerminalDockWidget::TerminalDockWidget(QWidget *parent)
    : QDockWidget(parent)
{
    repl = new ReplWidget(this);
    setWidget(repl);

    connect(repl, SIGNAL(command(QString)),
            this, SLOT(procces(QString)));
    connect(this, SIGNAL(resualtReady(QString)),
            repl, SLOT(result(QString)));
}

void TerminalDockWidget::procces(QString _commad) {
    QStringList comList = _commad.split(" ");
    comList.removeAll(" ");

    if (comList.size()) {
        QString cmd = comList[0];
        comList.removeAt(0);
        if (cmd == "add") {
            proccesAdd(comList);
        } else if (cmd == "del") {
            proccesDel(comList);
        } else if (cmd == "update") {
            proccesUpdt(comList);
        } else if (cmd == "list") {
            proccesList(comList);
        } else if (cmd == "search") {
            proccesSrch(comList);
        } else {
            emit resualtReady("err : command not found!" + _commad);
        }
        return;
    }
    emit resualtReady("err : command not found!!!");

}

void TerminalDockWidget::proccesAdd(const QStringList & _cmds) {
    if (_cmds.size()) {
    } else {
        emit resualtReady("usage : add <document_name_in_current_folder>");
    }
}

void TerminalDockWidget::proccesDel(const QStringList & _cmds) {

}

void TerminalDockWidget::proccesUpdt(const QStringList & _cmds) {

}

void TerminalDockWidget::proccesList(const QStringList & _cmds) {

}

void TerminalDockWidget::proccesSrch(const QStringList & _cmds) {

}
