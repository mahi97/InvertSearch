#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/logo.png");
    pixmap = pixmap.scaled(QApplication::desktop()->availableGeometry().width()/2,
                           QApplication::desktop()->availableGeometry().width()/2,
                           Qt::KeepAspectRatio,
                           Qt::FastTransformation);
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();
    MainWindow w;
    QRect r = w.geometry();
    r.moveCenter(QApplication::desktop()->availableGeometry().center());
    w.setGeometry(r);
    splash.finish(&w);
    w.show();
    return a.exec();
}
