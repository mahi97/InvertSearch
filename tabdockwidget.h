#ifndef TABDOCKWIDGET_H
#define TABDOCKWIDGET_H

#include <QDockWidget>
#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QLayout>
#include <QComboBox>
#include <QLabel>
#include <QPixmap>
#include <QIcon>

#include "base.h"

class TabDockWidget : public QDockWidget
{

    Q_OBJECT

public:
    TabDockWidget(QWidget* parent);
    ~TabDockWidget();
private:

    void fillLayout(QVBoxLayout *_layout);
    QStringList dataStructs;
    QWidget *w;

    ///////
    QComboBox *cmbDataStrct;
    QPushButton *btnBrowse;
    QPushButton *btnBuild;
    QPushButton *btnReset;
    QPushButton *btnHelp;
    QPushButton *Exit;
    QLabel *lblDirectory;


};

#endif // TABDOCKWIDGET_H
