#include "monitor.h"

Monitor* monitor;

Monitor::Monitor(QWidget *parent) : QTextEdit(parent) {

    this->setReadOnly(true);

    connect(search,
            SIGNAL(sig_summery(Summery*)),
            this, SLOT(slt_summery(Summery*)),
            Qt::QueuedConnection);

    connect(search,
            SIGNAL(sig_show(ShowMaterial*)),
            this,
            SLOT(slt_show(ShowMaterial*)),
            Qt::QueuedConnection);

    connect(search,
            SIGNAL(sig_searchFinished(SearchResult*)),
            this,
            SLOT(slt_search(SearchResult*)),
            Qt::QueuedConnection);


    this->setFont(QFont("Monaco"));
    this->defaultColor = Qt::black;

}

Monitor::~Monitor() {
    QFileDialog fd;
    QString str;
    str = fd.getSaveFileName(this, "Save output File");
    if (str.size() > 3) {
        QFile file(str);
        file.open(QIODevice::WriteOnly);
        file.write(this->toHtml().toLatin1());
        file.close();
    }
}

void Monitor::show(QString _str, QColor _color) {
    this->setTextColor(_color);
    this->append(_str);
    this->setTextColor(Qt::black);
}


void Monitor::slt_summery(Summery *_sum) {
    this->setTextColor(Qt::red);
    this->append(" -- BUILD SUMMERY --");
    this->setTextColor(Qt::blue);
    this->append(QString(" Tree Name : ") + _sum->treeName);
    this->setTextColor(Qt::black);
    this->append(QString(" Tree Size       --> %1").arg(_sum->treeSize));
    this->append(QString(" Files Count     --> %1").arg(_sum->filesCount));
    this->append(QString(" Words Count     --> %1").arg(_sum->wordsCount));
    this->append(QString(" Time That Takes --> %1").arg(_sum->timeTakesToBuild));
    this->setTextColor(Qt::red);
    this->append(" -- BUILD SUMMERY ENDS --");
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());
}

void Monitor::slt_show(ShowMaterial * _toShow) {
    this->setTextColor(_toShow->color);
    this->append(_toShow->line);
    this->setTextColor(defaultColor);
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());

}

void Monitor::slt_search(SearchResult* _list) {


    //    _list->result.at(0).


    this->setTextColor(Qt::red);
    this->append(QString("Time Passed : %1").arg(_list->time));
    this->append(" -- SEARCH END -- ");
    this->setTextColor(Qt::black);}
