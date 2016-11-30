#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    search = new SearchThread(this);
    search->start(QThread::HighestPriority);


    tabDock = new TabDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, tabDock);
    initWidget(tabDock);
    terminal = new TerminalDockWidget(this);
    initWidget(terminal);
    addDockWidget(Qt::BottomDockWidgetArea, terminal);

    monitor = new QTextEdit(this);
    initWidget(monitor);
    setCentralWidget(monitor);

    QLabel* lll = new QLabel("Hello Mahi :D", statusBar());
    statusBar()->addWidget(lll);


    /* Tree */
    tree = new Tree();
    for (size_t i{0}; i < 10; i++) {
        Node* tempNode = new Node();
        tempNode->key = QString("Key : %1").arg(i);
        for (size_t j{}; j < 5;j++) {
            tempNode->files.append(QString("File %1,%2").arg(i).arg(j));
        }
        tree->insert(tempNode);
    }

    tree->show();


    /* Final */
//    this->showMaximized();
    this->setWindowTitle(QString("DS Project (%1)").arg(QString(REVNUM)));
}

MainWindow::~MainWindow() {

}

void MainWindow::initWidget(QTextEdit *_monitor) {
    _monitor->setMinimumSize(QSize(500, 500));
}

void MainWindow::initWidget(TabDockWidget *_tab) {
    _tab->setMinimumSize(QSize(300, 500));
    _tab->setMaximumSize(QSize(500, 700));
}

void MainWindow::initWidget(TerminalDockWidget *_terminal) {
    _terminal->setMinimumSize(QSize(800, 200));
}
