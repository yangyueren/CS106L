//
// Created by yryang on 2020/3/13.
//
#include <iostream>
#include <sstream>
using namespace std;

#ifndef CPPTEST_GETINTEGER_HPP
#define CPPTEST_GETINTEGER_HPP

//
//istringstream iss("blank char");
//string name;
//// white space , '\n' will stop.
//iss >> name;
//cout << iss.str() <<endl;
//cout << name << endl;
//string name2;
//iss >> name2;
//cout << iss.str() <<endl;
//cout << name2 << endl;

int stringToInteger(const string& s){
    istringstream iss(s);
    int val;
    char trash;
    cout << iss.str() <<endl;
    if(!(iss>>val) || iss>>trash)
        throw domain_error("...");
    return val;
}
int getInteger(){
    while (true){
        string line; int result; char trash;
        if(!getline(cin, line)) throw domain_error("...");
        istringstream iss(line);
//        auto pos = iss.tellg() + streamoff(2);
//        iss.seekg(pos);
//        cout << iss.str() <<endl;
//        iss >> trash; // 不是'\n'无法写入trash中，而是getline会skip掉'\n'
//        cout << trash;

        if(iss>>result && !(iss>>trash))  return result;
//        cout << iss.eof() <<endl;
//        iss.clear();
        iss.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
#endif //CPPTEST_GETINTEGER_HPP
