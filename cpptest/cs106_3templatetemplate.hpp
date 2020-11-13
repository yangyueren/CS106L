//
// Created by yryang on 2020/4/22.
//

#ifndef CPPTEST_CS106_3TEMPLATETEMPLATE_HPP
#define CPPTEST_CS106_3TEMPLATETEMPLATE_HPP

#include <vector>
#include <iostream>
using namespace std;

template <typename U>
class BaseContainer{
public:
    BaseContainer(){

    }
    ~BaseContainer(){

    }
    vector<U> v;
};

template <typename T, template <typename U>
        class Container>
class Vect{
public:
    Vect(){

    }
    ~Vect(){

    }
    Container<T> c;
    vector<T> v;
};
void test_templatetemplate(){
    Vect<int, BaseContainer> a;
    a.c.v.push_back(23);
    cout << a.c.v.front() << endl;
}

#endif //CPPTEST_CS106_3TEMPLATETEMPLATE_HPP
