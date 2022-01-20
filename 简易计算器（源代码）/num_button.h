#ifndef NUM_BUTTON_H
#define NUM_BUTTON_H

#include <QPushButton>
#include <QChar>

class Num_Button : public QPushButton
{
public:
    Num_Button(QWidget*w);
    void setchar(QByteArray);
    QByteArray c;


};





#endif // NUM_BUTTON_H
