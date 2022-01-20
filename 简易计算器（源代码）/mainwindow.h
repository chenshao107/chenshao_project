#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QChar>
#include <string>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QUrl>
#include "num_button.h"
#include <QStack>
#include <iostream>
#include <QMessageBox>
#include <QPainter>
#include <string>
#include <mydialog.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



    void input(QByteArray);

    //检查括号合法性
    QStack<QChar> bracket;

    //括号不匹配的提示窗口
    MyDialog BracketError;


private:
    Ui::MainWindow *ui;
};




QString calcu(QString);
#endif // MAINWINDOW_H
