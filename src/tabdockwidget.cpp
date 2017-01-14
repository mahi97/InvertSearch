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
                << "Hash";


    fillLayout(control);

    w->setLayout(control);
    setWidget(w);

    signalCounter = 0;
    search->directory = &directory;

    // Conecctions
    connect(btnBrowse        , SIGNAL(clicked(bool)),
            this             , SLOT(slt_browse()));
    connect(btnBuild         , SIGNAL(clicked(bool)),
            this             , SLOT(slt_build()));
    connect(cmbDataStrct     , SIGNAL(currentIndexChanged(QString)),
            this             , SLOT(slt_changeTree(QString)));
    connect(this             , SIGNAL(sig_changeTree(ETree)),
            search           , SLOT(slt_chooseTree(ETree)));
    connect(this             , SIGNAL(sig_fileToBuild(File*)),
            search           , SLOT(slt_buildFile(File*)),
            Qt::QueuedConnection);
    connect(search           , SIGNAL(sig_summery(Summery*)),
            this             , SLOT(slt_buildComplete()),
            Qt::QueuedConnection);

    connect(btnReset         , SIGNAL(clicked(bool)),
            this             , SLOT(slt_reset()));

    connect(lineEditDirectory, SIGNAL(editingFinished()),
            this             , SLOT(slt_textEdit()));

    connect(search           , SIGNAL(sig_searchFinished(SearchResult*)),
            this             , SLOT(slt_showLines(SearchResult*)));
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
        emit sig_changeTree(ETree::Hash);
    else
        emit sig_changeTree(ETree::None);

}

void TabDockWidget::slt_del(QString _name) {
    lastFiles.removeOne(_name);
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
    if (_sr->words.size() == 0) {
        monitor->show("Nothing found", Qt::black);
        return;
    }
    if (_sr->words.size() == 1) {
        Q_FOREACH(Data datum, _sr->result[0]) {
            showDatum(datum);
        }
    } else {
        QList<Data> shared = _sr->result[0];
        QList<bool> sameLine;
        QStringList files;
        for (int i{}; i < shared.size();i++)
            sameLine.append(true);
        bool common = false;
        for (size_t i{1}; i < _sr->words.size(); i++) {
            for (size_t k{}; k < shared.size(); k++) {
                common = false;
                for(size_t j{}; j < _sr->result[i].size(); j++) {
                    if (shared[k].file == _sr->result[i][j].file) {
                        common = true;
                        if (i == _sr->words.size() - 1) {
                            if (!files.contains(shared[k].file)) {
                                files.append(shared[k].file);
                            }
                        }
                    }
                }
                if (!common) {
                    shared.removeAt(k--);
                }
            }
        }

        qDebug() << "Share " << files.size();
        QString result = "|";
        Q_FOREACH(QString file, files) {
            file.chop(4);
            result += file + ", ";
        }
        monitor->show(result, Qt::black);
    }
}

void TabDockWidget::showDatum(const Data& _datum) {
    QFile file(directory + QDir::separator() + _datum.file);
    QByteArray byteArr;
    file.open(QIODevice::ReadOnly);
    for(int i{};i < _datum.lineNum; i++) byteArr = file.readLine();
    byteArr.chop(2);
    showLine(QString(byteArr), _datum);
    file.close();
}

void TabDockWidget::showLine(const QString& _line,
                             const Data&    _datum) {
    QString result;
    QString start{};
    QString end{};
    QStringList split = _line.split(" ");
    if (split.size() < 8) { //Full Sentence
        result = _line;

    } else {
        if (_datum.wordNum > 3) { // START WITH ...
            start = " ... ";
            for(size_t i{0}; i < _datum.wordNum - 3;i++) {
                if (split.first() != "\n" && split.first() != "\r\n") {
                    split.pop_front();
                }
            }
        }
        int sc = split.count() - _datum.wordNum;
        if (sc > 3) { // END WITH ...
            for(int i{split.size()}; i > _datum.wordNum + 3;i--) {
                if (split.last() != "\n" && split.last() != "\r\n") {
                    split.pop_back();
                }
            }
            end = " ... ";
        }

        Q_FOREACH(QString word, split) {
            if (word != "\n" && word != "\r\n") {
                result.append(word + " ");
            }
        }


    }

    result = "|"
            + _datum.file
            + QString(" -> L: %1 ").arg(_datum.lineNum)
            + start
            + result
            + end;

    monitor->show(result, Qt::black);
}

void TabDockWidget::slt_reset() {
    monitor->clear();
}
