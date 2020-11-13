//
// Created by yryang on 2020/2/21.
//

#ifndef CPPTEST_DERIVED_HPP
#define CPPTEST_DERIVED_HPP

#include "iostream"
using namespace std;
//const 可以通过 :b(4)初始化
// static必须在类外初始化
class Init{
public:
    Init(int a):a(a){
//        this->b = 2;
//        this->d = 3;
    }
    Init() = default;
    int a;
//    const int b = 0;
    int c = 1;
//    static int d;
    void f(double i){
        cout << "base: " << i << endl;
    }
    //wrong below
//    static int d = 0;
//    static const double e = 1.3;
//    static const char* const f = "e";
};

//int Init::d = 5;

// Derive(int k) = delete;  不能使用这个函数，防止隐式转换; explicit 也可以防止隐式转换，尤其是对copy construct，防止了Init a = b；
class Derive: Init{
public:
    using Init::Init;
    Derive() = default;
    //如果这里不写 using Init::f; Derive类将只有一个f函数，Init的f的不能使用
    void f(int i){
        cout << "derive: " << i <<endl;
    }
    using Init::f;
    int k {111};
};

//derive
//Init init = Init();
//init.f(5.0);
//
//Derive derive(4);
//cout << derive.k <<endl;
//derive.f(4.5);
//derive.f(4);
//
//cout << is_pod<Derive>::value <<endl;

#endif //CPPTEST_DERIVED_HPP
