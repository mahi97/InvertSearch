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
#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QLineEdit>
#include <QDirIterator>
#include <QDir>
#include <QStandardItem>
#include <QListWidget>
#include <QApplication>

#include "base.h"
#include "searchthread.h"

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
    QString directory;
    ///////
    QComboBox *cmbDataStrct;
    QPushButton *btnBrowse;
    QPushButton *btnBuild;
    QPushButton *btnReset;
    QPushButton *btnHelp;
    QPushButton *Exit;
    QLineEdit *lineEditDirectory;
    QListWidget *fileViewer;
    QStringList files, names;

    int signalCounter;

public slots:
    void slt_open();
    void slt_update();
    void slt_build();
    void slt_changeTree(QString _tree);
    void slt_buildComplete();


signals:
    void sig_changeTree(ETree);
    void sig_fileToBuild(QString);


};

#endif // TABDOCKWIDGET_H
