#ifndef MONITOR_H
#define MONITOR_H

#include "base.h"
#include "QTextEdit"

class Monitor : public QTextEdit {
public:
    Monitor(QWidget* parent);
private:
};

extern Monitor* monitor;

#endif // MONITOR_H
