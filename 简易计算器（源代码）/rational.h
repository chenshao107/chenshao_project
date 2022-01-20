//
// Created by chenshao on 2021/10/21.
//

#ifndef CPP_RATIONAL_NUM_H
#define CPP_RATIONAL_NUM_H
#include <string>

#include <iostream>
#include <exception>
#include <string>
#include <map>
#include <stack>
#include <vector>
#include <math.h>

class rational_num {
public:
    long long  numerator, denominator;
    rational_num factorial();

    //返回一个浮点数，为其有理数值
    double value() const {
        return static_cast<double>(numerator) / denominator;
    }

    //构造函数接受两个整形参数，分别赋予分子分母。若分母为0，将抛出异常。
    // 如果分子为0，分母统一化为1，分母的负号移交给分子，方便比较
    rational_num(long long  num, long long  den) : numerator(num), denominator(den) {
        if(!denominator)throw std::runtime_error("Denominator can't be 0!\n");
        if(numerator)
            fraction();
        else
            denominator=1;
    };


    //接受一个字符串的构造函数
    explicit rational_num(const std::string&);

    //返回其倒数。分母合法性由构造函数检查
    rational_num reciprocal() const {
        return {denominator, numerator};
    }
    static rational_num  process_formula(const std::string& f);


private:
    //求出最大公约数
    long long  gcd(long long  a, long long  b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    //分子分母约分
    void fraction(){
        long long  temp=gcd(numerator,denominator);
        numerator/=temp;
        denominator/=temp;
        if(denominator<0) numerator*=(-1),denominator*=(-1);
    }
};

bool operator==(rational_num lhs, rational_num rhs);
bool operator!=(rational_num lhs, rational_num rhs);
bool operator<(rational_num lhs,rational_num rhs);
bool operator>(rational_num lhs,rational_num rhs);
rational_num operator+(rational_num lhs, rational_num rhs);
rational_num operator-(rational_num lhs,rational_num rhs);
rational_num operator*(rational_num lhs,rational_num rhs);
rational_num operator/(rational_num lhs,rational_num rhs);
std::ostream& operator<<(std::ostream& os,rational_num obj);
rational_num operator^(rational_num,rational_num);



#endif //CPP_RATIONAL_NUM_H
