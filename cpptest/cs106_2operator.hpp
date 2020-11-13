//
// Created by yryang on 2020/4/14.
//

#ifndef CPPTEST_CS106_2OPERATOR_HPP
#define CPPTEST_CS106_2OPERATOR_HPP

#include <iostream>
#include <string>
using namespace std;
class StringVec{
public:
    int allocated_size;
    int all_size;
    string *elems;

    StringVec(){
        this->all_size = 20;
        this->allocated_size = 0;
        this->elems = new string[this->all_size];
    }
    StringVec(const StringVec& other){
        this->allocated_size = other.allocated_size;
        this->all_size = other.all_size;
        this->elems = new string[this->all_size];
        std::copy(other.begin(), other.end(), begin());
    }
    ~StringVec(){
        delete [] this->elems;
    }
    StringVec&operator=(const StringVec& other){
        if(this != &other){
            delete [] this->elems;
            this->all_size = other.all_size;
            this->allocated_size = other.allocated_size;
            this->elems = new string[this->all_size];
            std::copy(other.begin(), other.end(), begin());
        }
        return *this;
    }

    void push_back(const string& ele){
        if(this->allocated_size < this->all_size){
            this->elems[this->allocated_size] = ele;
            ++this->allocated_size;
        } else{
            cout << "error" <<endl;
        }
    }
    string* begin() const {
        return this->elems;
    }
    string* end() const {
        return this->elems + this->allocated_size;
    }
};

ostream & operator<<(ostream &os, const StringVec &vec){
    for(int i=0; i<vec.allocated_size; ++i){
        os << vec.elems[i] << " ";
    }
    os << vec.allocated_size << " / " << vec.all_size;
    return os;
}

void test_cs106_operator(){
    StringVec s1;
    s1.push_back("happy");
    StringVec s2 = s1;
    s2.push_back("day");
    cout << s2 <<endl;
    cout << s1 <<endl;
}
#endif //CPPTEST_CS106_2OPERATOR_HPP
