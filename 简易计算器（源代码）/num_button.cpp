#include "num_button.h"

Num_Button::Num_Button(QWidget* p):QPushButton(p)
{


}
void Num_Button::setchar(QByteArray ch){
    c=ch;
};
