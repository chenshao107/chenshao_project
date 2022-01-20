#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rational.h"


//std::string MainWindow::Denominatior_Error="1";


//计算表达式，返回答案的Qstring
QString calcu(QString f){
    try{
        rational_num temp=
                rational_num::process_formula(f.toStdString());
        std::string r=std::to_string(temp.value());
        return QString(r.c_str());
    }catch(std::runtime_error &e){
        return QString(e.what());
    }


};



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    this->setWindowTitle("简易计算器");
    ui->temp->setText("0");
    ui->temp->setAlignment(Qt::AlignRight);
//    ui->temp->setAlignment(Qt::AlignCenter);

    BracketError.setWindowTitle(tr("括号不匹配!"));
    QPainter painter(&BracketError);
    QPixmap pix;
    pix.load(":/res/bracket.png");
    painter.drawPixmap(0,0,BracketError.width(),BracketError.height(),pix);
//    QPainter painter(&BracketError);






    //设置数字按钮
    ui->btn_0->setchar("0");
    connect(ui->btn_0,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_0->c);
    });

    ui->btn_1->setchar("1");
    connect(ui->btn_1,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_1->c);
    });

    ui->btn_2->setchar("2");
    connect(ui->btn_2,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_2->c);
    });

    ui->btn_3->setchar("3");
    connect(ui->btn_3,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_3->c);
    });

    ui->btn_4->setchar("4");
    connect(ui->btn_4,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_4->c);
    });

    ui->btn_5->setchar("5");
    connect(ui->btn_5,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_5->c);
    });

    ui->btn_6->setchar("6");
    connect(ui->btn_6,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_6->c);
    });

    ui->btn_7->setchar("7");
    connect(ui->btn_7,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_7->c);
    });

    ui->btn_8->setchar("8");
    connect(ui->btn_8,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_8->c);
    });
    ui->btn_9->setchar("9");
    connect(ui->btn_9,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_9->c);
    });

    ui->btn_dot->setchar(".");
    connect(ui->btn_dot,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_dot->c);
    });
    ui->btn_e->setchar("e");
    connect(ui->btn_e,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_e->c);
    });
    ui->btn_pi->setchar("pi");
    connect(ui->btn_pi,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_pi->c);
    });


    //运算符
    ui->btn_add->setchar("+");
    connect(ui->btn_add,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_add->c);
    });

    ui->btn_sub->setchar("-");
    connect(ui->btn_sub,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_sub->c);
    });
    ui->btn_mult->setchar("*");
    connect(ui->btn_mult,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_mult->c);
    });
    ui->btn_div->setchar("/");
    connect(ui->btn_div,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_div->c);
    });

    ui->btn_left->setchar("(");
    connect(ui->btn_left,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_left->c);
    });
    ui->btn_right->setchar(")");
    connect(ui->btn_right,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_right->c);
    });

    ui->btn_equl->setchar("=");
    connect(ui->btn_equl,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_equl->c);
    });

    //操作符
    ui->btn_clear->setchar("AC");
    connect(ui->btn_clear,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_clear->c);
    });

    ui->btn_bs->setchar("BS");
    connect(ui->btn_bs,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_bs->c);
    });
    ui->btn_factorial->setchar("!");
    connect(ui->btn_factorial,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_factorial->c);
    });
    ui->btn_pow->setchar("^");
    connect(ui->btn_pow,&QPushButton::clicked,this,[=](){
        this->input(ui->btn_pow->c);
    });



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::input(QByteArray s){
    auto *temp=ui->temp;
    auto *formula=ui->formula;

    if(s[0]>='1'&&s[0]<='9'){
        //非0数字或者（）
        QString last=temp->toPlainText();
        if(last!="0")temp->setText(last+s);
        else {temp->setText(s);}
    }
    else
    if(s=="pi"){
        temp->setText("3.141592653589");
    }else
    if(s=="e"){
        temp->setText("2.718281828459");
    }else
    if(s=="BS"){

        //退格符
        if(temp->toPlainText()=="0")return;
        QString a=temp->toPlainText();
        a.erase(a.end()-1,a.end());
        if(a=="")temp->setText("0");
        else temp->setText(a);
    }
    else
    if(s=="AC"){
        //AC键
        if(temp->toPlainText()=="0"){
            formula->clear();
        }else{
            temp->setText("0");
            bracket.clear();
        }
    }
    else
    if(s=="/"||s=="*"||s=="-"||s=="+"||s=="^"){
        //运算符
        QString f=formula->toPlainText();
        if(f!=""&&(f[f.length()-1]==')'||f[f.length()-1]=='!')){
            //已经有个运算数就位
            formula->setText(f+s);
        }else{
            //式子区末尾是个运算符，则修改运算符
            formula->setText(formula->toPlainText()+temp->toPlainText()+s);
            temp->setText("0");
        }
    }else if(s=="0"){
        //0
        if(temp->toPlainText()=="0")return;
        else {
            QString last=temp->toPlainText();
            temp->setText(last+s);
        }
    }else if(s[0]=='('){
        //将左括号压入栈
        bracket.push('(');
        formula->setText(formula->toPlainText()+s);
    }else if(s[0]=='.'){
        if(temp->toPlainText()=="0")
            temp->setText("0.");
        else
            temp->setText(temp->toPlainText()+s);

    }else if(s=="="){
        //等于号

        //检查括号合法性
        if(!bracket.empty())
        {
            BracketError.exec();
            return;
        }
        QString f=formula->toPlainText(),t=temp->toPlainText();
        if(f!="0")//式子区不缺运算数
        {
            QChar last=f[f.length()-1];
            if(last!=')'&&!(last>='0'&&last<='9')&&last!='!')f+= t;
        }

        QString result=calcu(f);
//        if(result==Denominatior_Error){
//            DenominatorError.exec();
//            return;
//        }



        //删去多余小数零
        int i;
        for(i=result.length()-1;result[i]=='0';i--);
        if(result[i]=='.')i--;
        result.erase(result.begin()+i+1,result.end());

        ui->history->append(f+"="+result);
        formula->clear();
        temp->setText("0");

    }else if(s==")"){
        //遇到右括号，就出栈，若栈为空报错
        if(bracket.empty()){
            BracketError.exec();
            return;
        }else bracket.pop();
        formula->setText(formula->toPlainText()+temp->toPlainText()+s);
        bracket.clear();
        temp->setText("0");

    }else if(s=="!"){
        formula->setText(formula->toPlainText()+temp->toPlainText()+s);
        temp->setText("0");
    }



    ui->temp->setAlignment(Qt::AlignRight);
};




