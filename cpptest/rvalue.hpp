//
// Created by yryang on 2020/2/21.
//

#ifndef CPPTEST_RVALUE_HPP
#define CPPTEST_RVALUE_HPP

#include "iostream"
using namespace std;


// perfect forward
void RunCode(int &&m){
    cout << "r value ref" <<endl;
}
void RunCode(int &m){
    cout << "l value ref" <<endl;
}void RunCode(const int &&m){
    cout << "const r value ref" <<endl;
}void RunCode(const int &m){
    cout << "const l value ref" <<endl;
}
template <typename T>
void PerfectForward(T &&t){
    RunCode(forward<T>(t));
}

//int a;
//int b;
//const int c = 1;
//const int d = 0;
//PerfectForward(a);
//PerfectForward(move(b));
//PerfectForward(c);
//PerfectForward(move(d));

class HasPrtMem{
public:
    HasPrtMem():d(new int(10)){
        cout << "construct: " << ++n_cstr <<endl;
    }
    HasPrtMem(const HasPrtMem& h):d(new int(*h.d)){
        cout << "copy construct: " << ++n_cptr <<endl;
    }
    HasPrtMem(HasPrtMem &&h):d(h.d){
        cout << "move construct: " << ++n_mvtr <<endl;
        cout << *h.d <<endl;
        h.d = nullptr;
    }
    ~HasPrtMem(){
        free(d);
        cout << "destruct: " << ++n_dstr <<endl;
    }
    int *d;
    static int n_cstr;
    static int n_dstr;
    static int n_cptr;
    static int n_mvtr;
};
int HasPrtMem::n_cstr = 0;
int HasPrtMem::n_cptr = 0;
int HasPrtMem::n_dstr = 0;
int HasPrtMem::n_mvtr = 0;

HasPrtMem getTemp() {
     return static_cast<HasPrtMem&&>(HasPrtMem());
 }


//    const HasPrtMem&&  hasPrtMem = getTemp();
//    hasPrtMem.d = nullptr;


struct Test
{
    HasPrtMem mo;
    const HasPrtMem & getMyObj() const & { return mo; }   // c
    HasPrtMem && getMyObj() &&{ return std::move(mo); }           // d
};
/*
 * 返回值是右值引用，需要返回的是一个非局部变量
 *
 *
 * 如果有这样一种情况：你写的类会大量出现对临时对象的使用（如上面例子中的e行），那么你可以考虑写d行（
 * 这样写的好处是：执行e行时，会调用MyObj的移动赋值运算符）；
 * 与此同时，如果你写了d行而没有写c行，那么f行就会报错－－－因为f行里的t是左值（lvalue），
 * 由于Test中只提供了右值调用getMyObj的函数（d行），所以会报错。如果想让f行通过编译，必须写c行。
 * 注意：这里可以返回右值引用而不会像上面那个func2报错的原因是mo在这里并不是函数getMyObj内的栈数据，
 * 这也就是为什么这个函数return的时候必须调用std::move的原因。

 */
void test_r(){
    HasPrtMem aa = Test().getMyObj();   // e
    Test t;
    HasPrtMem bb = t.getMyObj();    // f
    bb.d = nullptr;
}


#endif //CPPTEST_RVALUE_HPP
