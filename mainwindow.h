#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>
#include <QTextEdit>

#include "tabdockwidget.h"
#include "terminaldockwidget.h"
#include "base.h"


class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:

    void initWidget(QTextEdit* _monitor);
    void initWidget(TabDockWidget* _tab);
    void initWidget(TerminalDockWidget *_terminal);

    TabDockWidget      *tabDock;
    TerminalDockWidget *terminal;
    QTextEdit *monitor;


};

#endif // MAINWINDOW_H
