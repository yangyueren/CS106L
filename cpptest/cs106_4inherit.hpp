//
// Created by yryang on 2020/4/17.
//

#ifndef CPPTEST_CS106_4INHERIT_HPP
#define CPPTEST_CS106_4INHERIT_HPP

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
 * public protected private 继承方式的不同
 * 纵向比较：派生类是否可以访问基类的成员。
 * 横向：派生类的对象（实例） 是否可以访问派生类中基类的成员。
 */
class Base{
public:
    Base()= default;
    Base(string name): name(name){}
    virtual ~Base()= default;
    virtual void get_name(){
        cout << "Base: " << name << endl;
    }
    virtual void run() = 0;
//private:
    string name;
};
class Derived: public Base{
public:
    Derived() = default;
    Derived(string name): Base(name){}
    virtual ~Derived() = default;
    virtual void get_name(){
        cout << "Derived: " << this->name << endl;
    }
    virtual void run(){
        cout << "Derived: run" <<endl;
    }
};


#endif //CPPTEST_CS106_4INHERIT_HPP
