#ifndef STACK_H
#define STACK_H

#include "base.h"

class Stack : public QVector<QString> {
public:
    inline void push(const QString& _str) {QVector<QString>::append(_str);}
    inline QString pop() {QString s = this->data()[this->size() - 1];
                           this->resize(this->size() -1);
                           return s;}

    const QString& top() const {return this->data()[this->size() - 1];}
    inline QString top() {this->detach();
                          return this->data()[this->size() - 1];}

};


#endif // STACK_H
