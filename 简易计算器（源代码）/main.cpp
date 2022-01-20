#include "mainwindow.h"

#include <QApplication>
#include <QtDebug>
#include <QString>
#include <QByteArray>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
