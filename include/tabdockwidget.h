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
#include <QStandardItemModel>
#include <QMessageBox>
#include <QListView>
#include <QApplication>
#include <QFileInfo>
#include <QCheckBox>

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
    ///////
    QComboBox *cmbDataStrct;
    QPushButton *btnBrowse;
    QPushButton *btnBuild;
    QPushButton *btnReset;
    QPushButton *btnHelp;
    QPushButton *Exit;
    QLineEdit *lineEditDirectory;
    QListView *fileViewer;
    QStandardItemModel *model;
    QList<File*> files;

    int signalCounter;

    PropertyGet(QString, Directory, directory);
    PropertyGet(QStringList, Names, names);
    PropertyGet(QStringList, Paths, paths);

public slots:
    void slt_open();
    void slt_build();
    void slt_reset();
    void slt_browse();
    void slt_textEdit();
    void slt_buildComplete();
    void slt_add(QString _file);
    void slt_update(QString _file);
    void slt_changeTree(QString _tree);
    void slt_del(QString);


signals:
    void sig_changeTree(ETree);
    void sig_fileToBuild(File*);


};

extern TabDockWidget* tabDock;

#endif // TABDOCKWIDGET_H
