#include "tabdockwidget.h"


TabDockWidget::TabDockWidget(QWidget *parent)
    : QDockWidget(parent) {
    w = new QWidget(this);
    QVBoxLayout *control = new QVBoxLayout(w);
    fileViewer = new QListWidget(this);
    dataStructs << "-- Select a Tree --"
                << "Binary Search Tree (BST)"
                << "Ternary Search Tree (TST)"
                << "Trie";

    fillLayout(control);

    w->setLayout(control);
    setWidget(w);

    signalCounter = 0;

    // Conecctions
    connect(btnBrowse, SIGNAL(clicked(bool)), this, SLOT(slt_open()) );
    connect(btnBuild , SIGNAL(clicked(bool)), this, SLOT(slt_build()));
    connect(cmbDataStrct, SIGNAL(currentIndexChanged(QString)), this, SLOT(slt_changeTree(QString)));
    connect(this, SIGNAL(sig_changeTree(ETree)), search, SLOT(slt_chooseTree(ETree)));
    connect(this, SIGNAL(sig_fileToBuild(QString)), search, SLOT(slt_buildFile(QString)), Qt::QueuedConnection);
    connect(search, SIGNAL(sig_buildFinished()), this, SLOT(slt_buildComplete()), Qt::QueuedConnection);
}

TabDockWidget::~TabDockWidget() {

}

void TabDockWidget::fillLayout(QVBoxLayout *_layout) {

    cmbDataStrct = new QComboBox(0);
    btnBrowse = new QPushButton("Browse", this);
    btnBuild = new QPushButton("Build", this);
    btnHelp = new QPushButton("Help", this);
    btnReset = new QPushButton("Reset", this);
    lineEditDirectory = new QLineEdit(this);
    lineEditDirectory->setReadOnly(true);
    QHBoxLayout *browse = new QHBoxLayout;
    QHBoxLayout *btns = new QHBoxLayout;
    browse->addWidget(lineEditDirectory);
    browse->addWidget(btnBrowse);

    btns->addWidget(btnBuild);
    btns->addWidget(btnReset);
    btns->addWidget(btnHelp);

    cmbDataStrct->addItems(dataStructs);


    _layout->addLayout(browse);
    _layout->addWidget(fileViewer);
    _layout->addWidget(cmbDataStrct);
    _layout->addLayout(btns);
    _layout->setAlignment(browse, Qt::AlignTop);

}

/* SLOTS */

void TabDockWidget::slt_open() {
    qDebug() << "Open";
    QString tempDir;
    QFileDialog fd;
    tempDir = fd.getExistingDirectory(this,
                                      "Please choose a Folder",
                                      "",
                                      QFileDialog::ShowDirsOnly);
    fd.setFocus();
    if (tempDir.size() >= 3) {
        directory = tempDir;
        lineEditDirectory->setText(tempDir);
    }

    slt_update();

}

void TabDockWidget::slt_update() {
    files.clear();
    names.clear();
    QDirIterator it(directory);
    QStringList tempList;
    while (it.hasNext()) {
        QString temp = it.next();
        if (temp.endsWith(".txt")) {
            QStringList ttemp;
            ttemp = temp.split(QDir::separator());
            files << temp;
            names << ttemp.back();
        }
    }

    fileViewer->addItems(names);
}

void TabDockWidget::slt_build() {
    btnBuild->setEnabled(false);
    cmbDataStrct->setEnabled(false);
    Q_FOREACH(QString file, files) {
        emit sig_fileToBuild(file);
        signalCounter++;
    }

}

void TabDockWidget::slt_buildComplete() {
    signalCounter--;
    if (signalCounter == 0) {
        btnBuild->setEnabled(true);
        cmbDataStrct->setEnabled(true);
    }

}

void TabDockWidget::slt_changeTree(QString _tree) {

    if(_tree == dataStructs[0])
        emit sig_changeTree(ETree::None);
    else if(_tree == dataStructs[1])
        emit sig_changeTree(ETree::BST);
    else if(_tree == dataStructs[2])
        emit sig_changeTree(ETree::TST);
    else if(_tree == dataStructs[3])
        emit sig_changeTree(ETree::Trie);
    else
        emit sig_changeTree(ETree::None);

}
