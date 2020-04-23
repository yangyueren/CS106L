//
// Created by yryang on 2020/4/7.
//

#ifndef CPPTEST_REGEX_USAGE_HPP
#define CPPTEST_REGEX_USAGE_HPP

#include <iostream>
#include <iomanip>
#include <regex>
#include <string>
#include <vector>
using namespace std;

bool matchEmail(string email){
    smatch result; //存放结果
    regex pattern("^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+$");
    auto re = regex_match(email, result, pattern);
    cout << email << setw(5) << re << endl;
    return re;
}
vector<string > splitString(string str){
    vector<string> return_string;
    smatch result;
    regex pattern("\\b(\\w+)\\b");
    string::const_iterator iter_begin = str.begin();
    string::const_iterator iter_end = str.end();
    //regex_search needs iter_begin and iter_end, but regex_match doesn't.
    while (regex_search(iter_begin, iter_end, result, pattern)){
        return_string.push_back(result[1]);
        iter_begin = result[1].second;
    }
    for(auto i : return_string){
        cout << i <<endl;
    }
    return return_string;
}
void test_regex(){
    string email = "kdj32882@zju.edu.cn";
    matchEmail(email);
    string sp = "  my hat is on the tree.";
    splitString(sp);
}


#endif //CPPTEST_REGEX_USAGE_HPP
