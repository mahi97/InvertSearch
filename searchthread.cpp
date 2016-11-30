#include "searchthread.h"

SearchThread *search;

SearchThread::SearchThread(QObject* parent)
    : QThread(parent) {



}

void SearchThread::slt_chooseTree(ETree _tree) {
    tree = _tree;
}
