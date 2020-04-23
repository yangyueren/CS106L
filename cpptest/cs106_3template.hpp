//
// Created by yryang on 2020/4/17.
//

#ifndef CPPTEST_CS106_3TEMPLATE_HPP
#define CPPTEST_CS106_3TEMPLATE_HPP

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template <typename T, typename Container >
class Priority_queue : std::exception{
public:
    Priority_queue() = default;
    ~Priority_queue() = default;
    void push(T val){
        _heap.push_back(val);
        std::push_heap(_heap.begin(), _heap.end());
        ++_count;
    }
    T top(){
        if (_heap.empty()) throw std::domain_error("empty");
        return _heap[0];
    }
    void pop(){
        if (_heap.empty()) throw std::domain_error("empty");
        std::pop_heap(_heap.begin(), _heap.end());
        _heap.pop_back();
    }
    friend ostream &operator<<(ostream& os, const Priority_queue<T, Container> p){
        os << "{";
        for(auto i : p._heap){
            os << i[0] << ",";
        }
        os << "}";
        return os;
    }

private:
    size_t _count;
    Container _heap;
};


template <typename InputIterator, typename DataType>
int count_occurence(const InputIterator& begin, const InputIterator& end, const DataType &val){
    int count = 0;
    for(auto it = begin; it != end; ++it){
        if(*it == val) ++count;
    }
    return count;
}

void test_template(){
    Priority_queue<vector<string>, vector<vector<string> > > p;
    p.push({"j"});
    p.push({"234"});
    p.push({"345"});
    cout << p.top()[0] <<endl;
    p.pop();

    cout << p <<endl;

    vector<int> v{1,2,3,4,5,6,3,4,1};
    cout << count_occurence(v.begin(), v.end(), 3) << endl;
}

#endif //CPPTEST_CS106_3TEMPLATE_HPP
