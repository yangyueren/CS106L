//
// Created by yryang on 2020/4/7.
//

#ifndef CPPTEST_EXPLICIT_USAGE_HPP
#define CPPTEST_EXPLICIT_USAGE_HPP

#include <iomanip>
#include <iostream>
using namespace std;
class T{
public:
    explicit T(int a){
        this->a = a;
    }
    T(const T& a){
        this->a = a.a;
        cout << "copy cons" << endl;
    }
    void operator=(const T& a){
        this->a = a.a;
        cout << "=" <<endl;
    }
    int a;
};
void explicit_test(){
    char b = '2';
    float c = 2.3;
    T t(c);
    //对于copy construct 是否explicit，如果是explicit，必须用T t1(t)；
    T t1 = t;

    // 没有新的对象生成
    t1 = t;
    cout << t1.a <<endl;
}
#endif //CPPTEST_EXPLICIT_USAGE_HPP
