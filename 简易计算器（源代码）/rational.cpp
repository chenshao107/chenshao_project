//
// Created by chenshao on 2021/10/21.
//

#include "rational.h"




using namespace std;

//比较两个有理数是否相等,已考虑分子为0的情况
bool operator==(rational_num lhs, rational_num rhs) {
    return (lhs.numerator == rhs.numerator) && (lhs.denominator == rhs.denominator)&&lhs.numerator;
}

//比较两个有理数是否不等，用==函数构造
bool operator!=(rational_num lhs, rational_num rhs) {
    return !(lhs==rhs);
}


//两个有理数的小于比较
bool operator<(rational_num lhs,rational_num rhs){
    return lhs.numerator*rhs.denominator<rhs.numerator*lhs.denominator;
}

//两个有理数的大于比较，用<函数构造
bool operator>(rational_num lhs,rational_num rhs){
    return !(lhs<rhs)&&(rhs!=lhs);
}

//加法
rational_num operator+(rational_num lhs, rational_num rhs) {
    return {lhs.numerator*rhs.denominator+lhs.denominator*rhs.numerator,lhs.denominator*rhs.denominator};
}
//减法
rational_num operator-(rational_num lhs,rational_num rhs){
    return {lhs.numerator*rhs.denominator-lhs.denominator*rhs.numerator,lhs.denominator*rhs.denominator};
}

//乘法
rational_num operator*(rational_num lhs,rational_num rhs){
    return {lhs.numerator*rhs.numerator,lhs.denominator*rhs.denominator};
}
//除法，用乘法函数和倒数函数构造
rational_num operator/(rational_num lhs,rational_num rhs){
    return lhs*rhs.reciprocal();
}

//流输出
std::ostream& operator<<(std::ostream& os,rational_num obj){
    os<<obj.numerator;
    if(obj.denominator!=1)
        os<<'/'<<obj.denominator;
    return os;
}


//阶乘
rational_num rational_num::factorial(){
    long long  n=numerator/denominator;
    if(n<0){
        throw std::runtime_error("Factorial error!\n");
    }else {
        long long  ret=1;
        while (n) {
            ret*=n;
            --n;
        }
        return rational_num{ret,1};
    }
}


//指数
rational_num operator^(rational_num l,rational_num r){
     double v=pow(l.value(),r.value());
    return rational_num(to_string(v));
};



rational_num::rational_num(const std::string& s):numerator(0),denominator(1) {

    bool dot= false;
    for(char i : s){
        if(i!='.'){
            numerator=numerator*10+(i-'0');
            if(dot){
                denominator*=10;
            }
        }else dot=true;
    }
    this->fraction();
}
rational_num  rational_num::process_formula(const string& f){
    vector<string >element;
    string temp;
    for(char i:f){
        if(isdigit(i)||i=='.') {
            temp.push_back(i);
        }else{
            if(!temp.empty()) {
                element.push_back(temp);
                temp.clear();
            }
            element.emplace_back(1,i);
        }
    }
    if(!temp.empty())element.push_back(temp);

    for(const string& i:element){
        cout<<i<<' ';
    }
    cout<<endl;

    vector<string> postorder_formula;
    stack<char> ostack;


    //建立运算符权值体系
    map<char,long long > weigh;
    weigh['^']=weigh['!']=3;
    weigh['/']=weigh['*']=2;
    weigh['+']=weigh['-']=1;
    weigh['(']=0;



    //生成后缀表达式
    for(string i:element){
        if(isdigit(i[0])){
            //数字直接输出
            postorder_formula.push_back(i);
        }else if(i[0]==')'){
            //右括号直接抛到碰到左括号为止，括号不输出
            while (!ostack.empty()&&ostack.top()!='('){
                postorder_formula.emplace_back(1,ostack.top());
                ostack.pop();
            }
            ostack.pop();

        }else if(i[0]=='('){
            //左括号
            ostack.push('(');

        }else{
            //遇到运算符，抛到栈空或者栈顶元素优先级低于该运算符为止
            while (!ostack.empty()&&weigh[ostack.top()]>=weigh[i[0]]){
                postorder_formula.emplace_back(1,ostack.top());
                ostack.pop();
            }
            ostack.push(i[0]);
        }
    }
    while (!ostack.empty()) {
        postorder_formula.emplace_back(1, ostack.top());
        ostack.pop();
    }

    for(const string& i:postorder_formula){
        cout<<i<<' ';
    }

    stack<rational_num> num;
    for(string i:postorder_formula){
        if(isdigit(i[0])){
            num.push(rational_num(i));
        } else if(i[0]=='!'){
            //一元运算
            rational_num num1=num.top();num.pop();
            num.push(num1.factorial());
        }else{
            //二元运算
            rational_num num1=num.top();num.pop();
            rational_num num2=num.top();num.pop();
            if(i[0]=='+'){
                num.push(num2+num1);
            }else if(i[0]=='-'){
                num.push(num2-num1);
            } else if(i[0]=='*'){
                num.push(num2*num1);
            }else if(i[0]=='/'){
                num.push(num2/num1);
            }else if(i[0]=='^'){
                num.push(num2^num1);
            }
        }
    }
//    cout<<num.top();
    return  num.top();
//    return to_string(num.top().value());
}
