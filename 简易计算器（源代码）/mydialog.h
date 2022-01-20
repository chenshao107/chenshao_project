#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QPainter>

class MyDialog : public QDialog
{
public:
    void paintEvent(QPaintEvent*e)override;
    MyDialog();
};

#endif // MYDIALOG_H
