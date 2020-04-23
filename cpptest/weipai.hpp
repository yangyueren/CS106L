//
// Created by yryang on 2020/2/21.
//

#ifndef CPPTEST_WEIPAI_HPP
#define CPPTEST_WEIPAI_HPP

#include "iostream"
#include "list"
#include "vector"
using namespace std;

//委派构造函数
//编译器会阻止调用this->Info
//但是可以用new(this)Info(); 使用placement new强制在本
//对象地址上进行调用类的构造函数
class Info{
public:
    Info(){
        InitRest();
    }
    Info(int a){
        new(this) Info();
        this->a = a;
    }
    void  InitRest(){
        b = 1;
    }
    int a;
    int b;
};

//委派构造的一个很实际的应用就是使用构造模板函数产生目标构造函数
class TDConstructed{
    template <typename T>
    TDConstructed(T first, T last):l(first, last){}
    list<int> l;

    TDConstructed(vector<int> & v):TDConstructed(v.begin(), v.end()){}
    //同理可以实现queue的 deque的
};


#endif //CPPTEST_WEIPAI_HPP
