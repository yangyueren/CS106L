//
// Created by yryang on 2020/2/21.
//

#ifndef CPPTEST_INITIALIZE_LIST_Y_HPP
#define CPPTEST_INITIALIZE_LIST_Y_HPP


#include <vector>
#include "string"

using namespace std;
//initializer_list
class People{
public:
    People(initializer_list<pair<string, int>> l){
        auto i = l.begin();
        for(; i!=l.end(); ++i){
            data.push_back(*i);
        }
    }
    vector<pair<string, int>> data;
};

//  People people{{"lihua", 1}, {"ming", 2}};
//  for(auto i=people.data.begin(); i!=people.data.end(); ++i){
//      cout << i->first << i->second <<endl;
//  }
#endif //CPPTEST_INITIALIZE_LIST_Y_HPP
