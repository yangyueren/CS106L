//
// Created by yryang on 2020/11/14.
//
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

bool HasHexLetters(int num) {
    stringstream converter;
    converter << hex << num;
    string hex_s;
    converter >> hex_s;
    cout << "hex string is " << hex_s << endl;
    stringstream ss;
    ss << hex_s;
    int t;
    char remains;
    if(ss >> t){
        if(ss >> remains){
            return true;
        }else{
            return false;
        }
    }
    return ss.fail();

}
int main(){
    cout << boolalpha << HasHexLetters(17);
    return 0;
}