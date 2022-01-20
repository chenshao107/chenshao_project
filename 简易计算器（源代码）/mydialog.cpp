#include "mydialog.h"

MyDialog::MyDialog()
{

}
void MyDialog::paintEvent(QPaintEvent*e){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/bracket.png");
    setFixedSize(pix.size());
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    return ;
};
