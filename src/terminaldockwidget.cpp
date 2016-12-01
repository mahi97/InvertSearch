#include "terminaldockwidget.h"

TerminalDockWidget* terminal;

TerminalDockWidget::TerminalDockWidget(QWidget *parent)
    : QDockWidget(parent)
{
    repl = new ReplWidget(this);
    setWidget(repl);

    connect(repl, SIGNAL(command(QString)),
            this, SLOT(procces(QString)));
    connect(this, SIGNAL(resualtReady(QString)),
            repl, SLOT(result(QString)));
    connect(this, SIGNAL(sig_add(QString)),
            tabDock, SLOT(slt_add(QString)));
    connect(this, SIGNAL(sig_del(QString)),
            tabDock, SLOT(slt_del(QString)));
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
            emit resualtReady("err : command not found  ->  " + _commad);
        }
        return;
    }
    emit resualtReady("err : command not found!!!");

}

void TerminalDockWidget::proccesAdd(const QStringList & _cmds) {
    if (_cmds.size()) {

        QString dirStr = tabDock->getDirectory();
        QString command = dirStr + QDir::separator() + _cmds[0] + ".txt";
        QDir dir(dirStr);

        if (tabDock->getPaths().contains(command)) {
            emit resualtReady("err : Already exist, you may want to update.");
        } else if (!dir.entryList().contains(_cmds[0] + ".txt")) {
            qDebug() << dir.entryList();
            emit resualtReady("err : document not found.");
        } else {
            emit sig_add(command);
            emit resualtReady(_cmds[0] + " Successfully Added.");
        }
    } else {
        emit resualtReady("usage : add <document_name_in_current_folder>");
    }
}

void TerminalDockWidget::proccesDel(const QStringList & _cmds) {
    if (_cmds.size()) {
        QString name = _cmds[0] + ".txt";
        if (tabDock->getNames().contains(name)) {
            emit sig_del(name);
            emit resualtReady(_cmds[0] + " Successfully removed from list");
        } else {
            emit resualtReady("err : document not found.");
        }
    } else {
        emit resualtReady("usage : del <document_name>");
    }
}

void TerminalDockWidget::proccesUpdt(const QStringList & _cmds) {
    if (_cmds.size()) {
        QString name = _cmds[0] + ".txt";
        if (tabDock->getNames().contains(name)) {
            emit sig_update(name);
            emit resualtReady(_cmds[0] + " Successfully Updated");
        } else {
            emit resualtReady("err : document not found.");
        }
    } else {
        emit resualtReady("usage : update <document_name>");
    }
}

void TerminalDockWidget::proccesList(const QStringList & _cmds) {

}

void TerminalDockWidget::proccesSrch(const QStringList & _cmds) {

}
