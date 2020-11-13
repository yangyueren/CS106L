//
// Created by yryang on 2020/11/13.
//
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

string GetLine(){
    string ret;
    getline(cin, ret, '\n');
    cout << "Got Line " << ret << endl;
    return ret;
}

float GetFloat() {
    float ret;
    while (true){
        stringstream converter;
        converter << GetLine();
        char remain;
        if(converter >> ret){
            if(converter >> remain){
                cout << "Got unexpected char: " << remain << endl;
            }else{
                return ret;
            }
        }


    }

}

int main(){
    float num = GetFloat();
    cout << num << endl;
    return 0;
}
