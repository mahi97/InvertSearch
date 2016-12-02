#include "tabdockwidget.h"

TabDockWidget* tabDock;

TabDockWidget::TabDockWidget(QWidget *parent)
    : QDockWidget(parent) {
    w = new QWidget(this);
    QVBoxLayout *control = new QVBoxLayout(w);
    fileViewer = new QListView(this);
    model = new QStandardItemModel(this);
    fileViewer->setModel(model);
    dataStructs << "-- Select a Tree --"
                << "Binary Search Tree (BST)"
                << "Ternary Search Tree (TST)"
                << "Trie";

    fillLayout(control);

    w->setLayout(control);
    setWidget(w);

    signalCounter = 0;

    // Conecctions
    connect(btnBrowse, SIGNAL(clicked(bool)), this, SLOT(slt_browse()));
    connect(btnBuild , SIGNAL(clicked(bool)), this, SLOT(slt_build()));
    connect(cmbDataStrct, SIGNAL(currentIndexChanged(QString)), this, SLOT(slt_changeTree(QString)));
    connect(this, SIGNAL(sig_changeTree(ETree)), search, SLOT(slt_chooseTree(ETree)));
    connect(this, SIGNAL(sig_fileToBuild(File*)), search, SLOT(slt_buildFile(File*)), Qt::QueuedConnection);
    connect(search, SIGNAL(sig_buildFinished()), this, SLOT(slt_buildComplete()), Qt::QueuedConnection);
    connect(btnReset, SIGNAL(clicked(bool)), this, SLOT(slt_reset()));
    connect(lineEditDirectory, SIGNAL(editingFinished()), this, SLOT(slt_textEdit()));
    connect(search, SIGNAL(sig_summery(Summery*)), this, SLOT(slt_reset()), Qt::QueuedConnection);
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

void TabDockWidget::slt_browse() {
    QString tempDir;
    QFileDialog fd;
    tempDir = fd.getExistingDirectory(this,
                                      "Please choose a Folder",
                                      "",
                                      QFileDialog::ShowDirsOnly);
    if (tempDir.size() >= 3) {
        directory = tempDir;
        lineEditDirectory->setText(tempDir);
        slt_open();
    }
}

void TabDockWidget::slt_textEdit() {
    QFileInfo fi = QFileInfo(lineEditDirectory->text());
    if (fi.exists() && fi.isDir()) {
        directory = fi.absolutePath();\
        slt_open();
    } else {
        QMessageBox::warning(this,
                             "Folder not Found",
                             "Please enter a existing FOLDER name",
                             QMessageBox::Ok);
    }
}

void TabDockWidget::slt_open() {
    qDebug() << "Open --> " << directory;
    files.clear();
    names.clear();
    paths.clear();
    model->clear();
    QDirIterator it(directory);
    while (it.hasNext()) {
        QString temp = it.next();
        if (temp.endsWith(".txt")) {
            slt_add(temp);
        }
    }

}

void TabDockWidget::slt_add(QString _file) {

    QStringList temp;
    temp = _file.split(QDir::separator());
    File* tFile = new File;
    tFile->name = temp.back();
    tFile->path = _file;
    names.append(tFile->name);
    paths.append(tFile->path);
    files.append(tFile);
    QStandardItem *item = new QStandardItem(temp.back());
    model->appendRow(item);
}

void TabDockWidget::slt_update(QString _name) {
    File* tFile;
    Q_FOREACH(File* file, files) {
        if (file->name == _name) {
            tFile = file;
            break;
        }
    }

    emit sig_fileToBuild(tFile);
    signalCounter++;
}

void TabDockWidget::slt_build() {
    btnBuild->setEnabled(false);
    cmbDataStrct->setEnabled(false);
    Q_FOREACH(File* file, files) {
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

void TabDockWidget::slt_del(QString _name) {
    for(size_t i{}; i < files.size(); i++) {
        if (_name == files[i]->name) {
            for(size_t j{}; j < model->rowCount();j++) {
                if (model->item(j)->text() == files[i]->name) {
                    model->removeRow(j);
                }
            }
            files.removeAt(i);
            names.removeAt(i);
            paths.removeAt(i);
            break;
        }
    }
}

void TabDockWidget::slt_reset() {
    qDebug() << "Gotcha";
}
