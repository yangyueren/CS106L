//
// Created by yryang on 2020/3/21.
//

#ifndef CPPTEST_MOVE_OPERATOR_HPP
#define CPPTEST_MOVE_OPERATOR_HPP

#include <iostream>
using namespace std;

//移动构造 移动赋值
class A{
    int * p;

public:
    A(int value):
            p(new int(value))
    {}

    A(A & a):
            p(new int(*a.p))
    {
        std::cout<<"A copy construct"<<std::endl;
        //如果调用A的复制构造函数，则打印 "copy c"
    }

    A(A && a):
            p(a.p)
    {
        std::cout<<"A move construct"<<std::endl;
        //如果调用A的移动构造函数，则打印 "move c"
        a.p=nullptr;
    }

    A & operator=(A & a){
        std::cout<<"A copy ="<<std::endl;
        //如果调用A的复制赋值运算符，则打印 "copy ="
        p=new int(*a.p);
        return *this;
    }

    A & operator=(A && a){
        std::cout<<"A move ="<<std::endl;
        //要判断move = 不能是自身，否则会释放内存
        assert(&a != this);
        //如果调用A的移动赋值运算符，则打印 "move ="
        p=a.p;
        a.p=nullptr;
        return *this;
    }

    ~A(){
        delete p;
    }

};

class B{
    A a;
public:
    B(int value):
            a(value)
    {}

    B(B && b):
            a(std::move(b.a))
    //这里是一个标志1，标志着原来的我对c++移动构造函数的一个憧憬:
    //我原本以为A有移动构造函数了，那么B的移动构造函数应该会自动
    //调用A的移动构造函数,果然我还是太年轻了。
    {
        cout << "B move construct" <<endl;
    }

    B & operator=(B && b){
        a= std::move(b.a);
        //这又是一个标志2，标志着原来的我对c++移动赋值运算符的一个憧憬
        cout << "B move =" <<endl;
        return *this;
    }
};


/*
int main(){
    B b1(1);
    cout << "b2 begin" <<endl;
    B b2(std::move(b1));
    b2=std::move(b2);
    return 0;
}

output:
b2 begin
A move construct
B move construct
A move =
B move =
 */

#endif //CPPTEST_MOVE_OPERATOR_HPP
