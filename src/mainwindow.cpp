#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {


    setFocus();

    search = new SearchThread(this);
    search->start(QThread::HighestPriority);

    tabDock = new TabDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, tabDock);
    initWidget(tabDock);
    terminal = new TerminalDockWidget(this);
    initWidget(terminal);
    addDockWidget(Qt::BottomDockWidgetArea, terminal);

    monitor = new Monitor(this);
    initWidget(monitor);
    setCentralWidget(monitor);


    QLabel* lll = new QLabel("Hello Mahi :D", statusBar());
    statusBar()->addWidget(lll);


    /* Final */
//    this->showMaximized();
    this->setWindowTitle(QString("DS Project (%1)").arg(QString(REVNUM)));
}

MainWindow::~MainWindow() {

    search->terminate();
    search->wait();
}

void MainWindow::initWidget(Monitor *_monitor) {
    _monitor->setMinimumSize(QSize(500, 500));
}

void MainWindow::initWidget(TabDockWidget *_tab) {
    _tab->setMinimumSize(QSize(300, 500));
    _tab->setMaximumSize(QSize(500, 700));
}

void MainWindow::initWidget(TerminalDockWidget *_terminal) {
    _terminal->setMinimumSize(QSize(800, 200));
}
