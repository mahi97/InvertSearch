#ifndef MONITOR_H
#define MONITOR_H

#include "base.h"
#include "QPlainTextEdit"

class Monitor : public QPlainTextEdit {
public:
    Monitor(QWidget* parent);
private:
};

extern Monitor* monitor;

#endif // MONITOR_H
