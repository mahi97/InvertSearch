#include "terminaldockwidget.h"

TerminalDockWidget* terminal;

TerminalDockWidget::TerminalDockWidget(QWidget *parent)
    : QDockWidget(parent)
{
    repl = new ReplWidget(this);
    setWidget(repl);

    wordsToSearch = 0;

    connect(repl, SIGNAL(command(QString)),
            this, SLOT(procces(QString)));
    connect(this, SIGNAL(resualtReady(QString)),
            repl, SLOT(result(QString)));
    connect(this, SIGNAL(sig_add(QString)),
            tabDock, SLOT(slt_add(QString)));
    connect(this, SIGNAL(sig_del(QString)),
            tabDock, SLOT(slt_del(QString)));
    connect(this, SIGNAL(sig_showWords()),
            search, SLOT(slt_showWords()),
            Qt::QueuedConnection);
    connect(this, SIGNAL(sig_searchWord(QString)),
            search, SLOT(slt_search(QString)),
            Qt::QueuedConnection);
    connect(search, SIGNAL(sig_searchFinished()),
            this, SLOT(slt_searchFinished()),
            Qt::QueuedConnection);

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
        } else if (cmd == "exit") {
            qApp->exit();
        } else {
            emit resualtReady("err : command not found  ->  " + _commad);
        }
        return;
    }
    emit resualtReady("err : command not found!!!");

}

void TerminalDockWidget::slt_searchFinished() {
    qDebug() << "hoohoho" << wordsToSearch;
    wordsToSearch--;
    if (wordsToSearch == 0) {
        monitor->setTextColor(Qt::red);
        monitor->append(" -- SEARCH END -- ");
        monitor->setTextColor(Qt::black);
    }
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
    if (_cmds.size()) {
        if (_cmds[0].startsWith("-")) {
            qDebug() << _cmds[0];
            if (_cmds[0] == "-w") {
                emit resualtReady("Word will be shown.");
                emit sig_showWords();

            } else if (_cmds[0] == "-l") {
                emit resualtReady("Files in List will be shown.");
                monitor->setTextColor(Qt::red);
                monitor->append(" -- Files That Listed --");
                QStringList buffer;
                Q_FOREACH(QString file, tabDock->getNames()) {
                    monitor->setTextColor(Qt::black);
                    if (file.endsWith(".txt"))
                    buffer.append(file);
                    if (buffer.size() > 5) {
                        monitor->append(QString("%1, %2, %3, %4, %5, %6")
                                        .arg(buffer[0])
                                .arg(buffer[1])
                                .arg(buffer[2])
                                .arg(buffer[3])
                                .arg(buffer[4])
                                .arg(buffer[5]));
                        buffer.clear();
                    }
                }
                monitor->setTextColor(Qt::red);
                monitor->append(" -- Files That Listed END --");


            } else if (_cmds[0] == "-f") {
                emit resualtReady("File in Directory will be shown");
                QDir dir(tabDock->getDirectory());
                QStringList buffer;
                monitor->setTextColor(Qt::red);
                monitor->append(" -- Files That in Directory --");
                Q_FOREACH(QString file, dir.entryList()) {
                    monitor->setTextColor(Qt::black);
                    if (file.endsWith(".txt"))
                    buffer.append(file);
                    if (buffer.size() > 5) {
                        monitor->append(QString("%1, %2, %3, %4, %5, %6")
                                        .arg(buffer[0])
                                .arg(buffer[1])
                                .arg(buffer[2])
                                .arg(buffer[3])
                                .arg(buffer[4])
                                .arg(buffer[5]));
                        buffer.clear();
                    }
                }
                monitor->setTextColor(Qt::red);
                monitor->append(" -- Files in Directory END --");


            } else {
                emit resualtReady("usage : list [-f -w -l]");
            }
        } else {
            emit resualtReady("usage : list [-f -w -l]");
        }
    }
}

void TerminalDockWidget::proccesSrch(const QStringList & _cmds) {
    if (_cmds.size() > 1) {
        if (_cmds[0] == "-w") {
            if (_cmds[1].startsWith("\"") && _cmds[1].endsWith("\"")) {
                QString word = _cmds[1];
                word.chop(1);
                word.remove(0, 1);
                qDebug() << word;
                wordsToSearch++;
                emit sig_searchWord(word);
                emit resualtReady("Start Searching for : " + word);
                monitor->setTextColor(Qt::red);
                monitor->append(" -- SEARCH START -- ");
                monitor->setTextColor(Qt::black);


            } else {
                emit resualtReady("err : put word between `\"` ");
            }
        } else if (_cmds[0] == "-s") {
            QString words = _cmds[1];
            words.chop(1);
            words.remove(0, 1);
            Q_FOREACH(QString word, words.split(" ")) {
                emit sig_searchWord(word);
                wordsToSearch++;
            }
            emit resualtReady("Start Searching for Words ... ");
            monitor->setTextColor(Qt::red);
            monitor->append(" -- SEARCH START -- ");
            monitor->setTextColor(Qt::black);
        } else {
            emit resualtReady("usage : search -w \"word_to_search\"");
            emit resualtReady("      : search -s \"words_to_search_sperated_by_space\"");
        }
    } else {
        emit resualtReady("usage : search -w \"word_to_search\"");
        emit resualtReady("      : search -s \"words_to_search_sperated_by_space\"");
    }
}
