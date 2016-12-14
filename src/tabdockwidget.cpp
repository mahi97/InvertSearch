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
                << "Trie"
                << "Balanced BST"
                << "Balanced TST";


    fillLayout(control);

    w->setLayout(control);
    setWidget(w);

    signalCounter = 0;
    search->directory = &directory;

    // Conecctions
    connect(btnBrowse, SIGNAL(clicked(bool)), this, SLOT(slt_browse()));
    connect(btnBuild , SIGNAL(clicked(bool)), this, SLOT(slt_build()));
    connect(cmbDataStrct, SIGNAL(currentIndexChanged(QString)), this, SLOT(slt_changeTree(QString)));
    connect(this, SIGNAL(sig_changeTree(ETree)), search, SLOT(slt_chooseTree(ETree)));
    connect(this, SIGNAL(sig_fileToBuild(File*)), search, SLOT(slt_buildFile(File*)), Qt::QueuedConnection);
    connect(search, SIGNAL(sig_summery(Summery*)), this, SLOT(slt_buildComplete()), Qt::QueuedConnection);
    connect(btnReset, SIGNAL(clicked(bool)), this, SLOT(slt_reset()));
    connect(lineEditDirectory, SIGNAL(editingFinished()), this, SLOT(slt_textEdit()));
    connect(search, SIGNAL(sig_summery(Summery*)), this, SLOT(slt_reset()), Qt::QueuedConnection);
    connect(search, SIGNAL(sig_searchFinished(SearchResult*)), this, SLOT(slt_showLines(SearchResult*)));
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
        slt_changeTree(cmbDataStrct->currentText());
    }
}

void TabDockWidget::slt_textEdit() {

    QString text = lineEditDirectory->text();
    text = text + ((text.endsWith("/")) ? "" : "/");
    QFileInfo fi = QFileInfo(text);
    if (fi.exists() && fi.isDir()) {
        directory = fi.path();
        slt_open();
    } else {
        QMessageBox::warning(this,
                             "Folder not Found",
                             "Please enter a existing FOLDER name",
                             QMessageBox::Ok);
    }
}

void TabDockWidget::slt_open() {
    files.clear();
    names.clear();
    paths.clear();
    lastFiles.clear();
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
    item->setEditable(false);
    model->appendRow(item);
}

void TabDockWidget::slt_update(QString _file) {
    QStringList temp;
    temp = _file.split(QDir::separator());
    File* tFile = new File;
    tFile->name = temp.back();
    tFile->path = _file;
    names.append(tFile->name);
    paths.append(tFile->path);
    files.append(tFile);
    QStandardItem *item = new QStandardItem(temp.back());
    item->setEditable(false);
    model->appendRow(item);

    emit sig_fileToBuild(tFile);
    signalCounter++;
}

void TabDockWidget::slt_build() {
    //    slt_changeTree(cmbDataStrct->currentText());
    if (files.isEmpty()) {
        QMessageBox::critical(this,
                              "Can't Build",
                              "There's no file to build",
                              QMessageBox::Ok);
        return;
    }

    if (cmbDataStrct->currentIndex() == 0) {
        QMessageBox::critical(this,
                              "Can't Build",
                              "You Should Select a Tree First.",
                              QMessageBox::Ok);
        return;
    }
    Q_FOREACH(File* file, files) {
        if (!lastFiles.contains(file->name)) {
            btnBuild->setEnabled(false);
            cmbDataStrct->setEnabled(false);
            lastFiles.append(file->name);
            emit sig_fileToBuild(file);
            signalCounter++;
        }
    }
    if (signalCounter == 0) {
        monitor->show("Tree is Update, There's Nothing to build", Qt::red);
    }
}

void TabDockWidget::slt_buildComplete() {
    //    signalCounter--;
    //    if (signalCounter == 0) {
    btnBuild->setEnabled(true);
    cmbDataStrct->setEnabled(true);
    //    }
}

void TabDockWidget::slt_changeTree(QString _tree) {

    lastFiles.clear();

    if(_tree == dataStructs[0])
        emit sig_changeTree(ETree::None);
    else if(_tree == dataStructs[1])
        emit sig_changeTree(ETree::BST);
    else if(_tree == dataStructs[2])
        emit sig_changeTree(ETree::TST);
    else if(_tree == dataStructs[3])
        emit sig_changeTree(ETree::Trie);
    else if (_tree == dataStructs[4])
        emit sig_changeTree(ETree::BalancedBST);
    else if (_tree == dataStructs[5])
        emit sig_changeTree(ETree::BalancedTST);
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
            File* tempFile = files[i];
            tempFile->del = true;
            emit sig_fileToBuild(tempFile);
            files.removeAt(i);
            names.removeAt(i);
            paths.removeAt(i);

            break;
        }
    }
}

void TabDockWidget::slt_showLines(SearchResult * _sr) {
    if (_sr->words.size() == 1) {
        Q_FOREACH(Data datum, _sr->result[0]) {
            QFile file(directory + QDir::separator() + datum.file);
            QByteArray ba;
            QString res;
            file.open(QIODevice::ReadOnly);
            for(int i{};i < datum.lineNum; i++) ba = file.readLine();
            if (ba.size() < 5) continue;
            ba.chop(2);
            QStringList split = QString(ba).split(" ");
            if (split.size() < 8) { //Full Sentence
                res = QString(ba);
            } else if (split.size() - datum.wordNum > 3 && datum.wordNum > 3) {
                res.append("... ");
                for(size_t i{datum.wordNum - 3}; i < datum.wordNum + 3;i++) {
                    if (split.at(i) != "\n" && split.at(i) != "\r\n")
                        res.append(split.at(i) + " ");
                }
                res.append(" ...");

            } else if (split.size() - datum.wordNum > 3) { // NO END
                for(size_t i{0}; i < datum.wordNum + 3;i++)
                    if (split.at(i) != "\n" && split.at(i) != "\r\n")
                        res.append(split.at(i) + " ");
                res.append(" ...");
            } else if (datum.wordNum > 3) { // NO START
                res.append("... ");
                for(size_t i{datum.wordNum - 3}; i < split.size();i++)
                    if (split.at(i) != "\n" && split.at(i) != "\r\n")
                        res.append(split.at(i) + " ");
            }
            res = "|" + datum.file + QString(" -> L: %1 ").arg(datum.lineNum) +" "+ res;
            monitor->show(res, Qt::black);
            file.close();
        }
    } else {
        bool delShare = true;
        QList<Data> shared = _sr->result[0];
        QStringList files;
        for (size_t i{1}; i < _sr->words.size(); i++) {
            for (size_t k{}; k < shared.size(); k++) {
                delShare = true;
                for(size_t j{}; j < _sr->result[i].size(); j++) {
                    if (shared[k].file == _sr->result[i][j].file) {
                        if (!files.contains(shared[k].file))
                            files.append(shared[k].file);
                        shared.append(_sr->result[i][j]);
                        _sr->result[i].removeAt(j);
                        delShare = false;
                    }
                }
                if (delShare) {
                    shared.removeAt(k);
                }
            }
        }

        qDebug() << "Share " << shared.size();
        Q_FOREACH(QString file, files) {
            Q_FOREACH(Data datum, shared) {
                if (datum.file == file) {
                    QFile file(directory + QDir::separator() + datum.file);
                    QByteArray ba;
                    QString res;
                    file.open(QIODevice::ReadOnly);
                    for(int i{};i < datum.lineNum; i++) ba = file.readLine();
                    if (ba.size() < 5) continue;
                    ba.chop(2);
                    QStringList split = QString(ba).split(" ");
                    if (split.size() < 8) { //Full Sentence
                        res = QString(ba);
                    } else if (split.size() - datum.wordNum > 3 && datum.wordNum > 3) {
                        res.append("... ");
                        for(size_t i{datum.wordNum - 3}; i < datum.wordNum + 3;i++) {
                            if (split.at(i) != "\n" && split.at(i) != "\r\n")
                                res.append(split.at(i) + " ");
                        }
                        res.append(" ...");

                    } else if (split.size() - datum.wordNum > 3) { // NO END
                        for(size_t i{0}; i < datum.wordNum + 3;i++)
                            if (split.at(i) != "\n" && split.at(i) != "\r\n")
                                res.append(split.at(i) + " ");
                        res.append(" ...");
                    } else if (datum.wordNum > 3) { // NO START
                        res.append("... ");
                        for(size_t i{datum.wordNum - 3}; i < split.size();i++)
                            if (split.at(i) != "\n" && split.at(i) != "\r\n")
                                res.append(split.at(i) + " ");
                    }
                    res = "|" + datum.file + QString(" -> L: %1 ").arg(datum.lineNum) +" "+ res;
                    monitor->show(res, Qt::black);
                    file.close();
                }
            }
        }

    }
}

void TabDockWidget::slt_reset() {
}
