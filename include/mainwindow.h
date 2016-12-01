#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>
#include <QTextEdit>
#include <QThread>

#include "tabdockwidget.h"
#include "terminaldockwidget.h"
#include "monitor.h"
#include "base.h"
#include "trees.h"
#include "searchthread.h"


class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:

    void initWidget(Monitor* _monitor);
    void initWidget(TabDockWidget* _tab);
    void initWidget(TerminalDockWidget *_terminal);


};

#endif // MAINWINDOW_H
