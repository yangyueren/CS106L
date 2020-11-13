//
// Created by yryang on 2020/11/13.
//
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

string int2string(int num){
    stringstream ss;
    ss << num;
    string ans;
    ss >> ans;
    return ans;
}

int main(){
    int num = 34;
    string ans = int2string(num);
    cout << ans << endl;
    return 0;
}