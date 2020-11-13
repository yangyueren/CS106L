//
// Created by yryang on 2020/3/13.
//

#ifndef CPPTEST_SMART_POINTER_HPP
#define CPPTEST_SMART_POINTER_HPP
#include <iostream>
#include <sstream>

using namespace std;

class DogHouse;
class Dog{
public:
    Dog(){

    }
    Dog(const Dog &d){
        cout << "copy construct dog" <<endl;
    }
    shared_ptr<DogHouse> dh;

    ~Dog(){
        cout << "free dog" <<endl;
    }
};

class DogHouse{
public:
    weak_ptr<Dog> dog;
    DogHouse(){

    }
    ~DogHouse(){
        cout << "free doghouse" <<endl;
    }
};

//为了避免形成循环引用，要记得使用weak_ptr
//shared_ptr<Dog> d(new Dog());
// shared_ptr<Dog> d = make_shared<Dog>(new Dog()); //会进行一次拷贝构造函数
void testSmartPointer(){
//    shared_ptr<Dog> d(new Dog());
    shared_ptr<Dog> d = make_shared<Dog>( Dog());
    shared_ptr<DogHouse> dh(new DogHouse());
    d->dh = dh;
    dh->dog = d;
    cout << d.use_count() <<endl;
    cout << dh.use_count() <<endl;
}

// 使用自定义的deleter

void test_unique_ptr(){
    auto del = [](int *p) {
        cout << "delete p " << *p << endl;
        delete [] p;
    };
    std::unique_ptr<int[], void(*)(int *)> p(new int[10], del);
    p.reset(new int[5]);
    p.get()[0] = 5;

    unique_ptr<int[], void(*)(int*)> q = std::move(p);
    cout << q.get()[0] << endl;
}


template <size_t N>
struct Node{
    int num;
    unique_ptr<int> p;
    Node(int n):num(n),p(nullptr) {
        cout << num << endl;
    }

    ~Node(){
        cout << "delete" << num << endl;
    }
};
void test_unique_ptr3(){
    unique_ptr<Node<3>> p(new Node<3>(6));
    p.release(); // release 之后是一个裸指针，不会自动释放资源，所以建议直接将该指针赋值给智能指针
    p.reset(new Node<3>(5));
    cout << p->num << endl;
}

#endif //CPPTEST_SMART_POINTER_HPP
