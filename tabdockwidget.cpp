#include <QLayout>

#include "tabdockwidget.h"

TabDockWidget::TabDockWidget(QWidget *parent)
    : QDockWidget(parent) {
    w = new QWidget(this);
    QVBoxLayout *control = new QVBoxLayout(w);
    dataStructs << "TST" << "BST" << "Trie";

    fillLayout(control);

    w->setLayout(control);
    setWidget(w);
}

TabDockWidget::~TabDockWidget() {

}

void TabDockWidget::fillLayout(QVBoxLayout *_layout) {

    cmbDataStrct = new QComboBox(0);
    btnBrowse = new QPushButton("Browse", this);
    lblDirectory = new QLabel(this);
    QHBoxLayout *browse = new QHBoxLayout;
    browse->addWidget(lblDirectory);
    browse->addWidget(btnBrowse);


    cmbDataStrct->addItems(dataStructs);


    _layout->addLayout(browse);
    _layout->addWidget(cmbDataStrct);
    _layout->setAlignment(browse, Qt::AlignTop);
}
