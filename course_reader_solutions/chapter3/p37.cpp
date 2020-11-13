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

bool GetBool() {
    string ret;
    while (true){
        stringstream converter;
        converter << GetLine();
        char remain;
        if(converter >> ret && (ret =="true" || ret == "false")){
            if(converter >> remain){
                cout << "Got unexpected char: " << remain << endl;
            }else{
                bool r;
                if(ret =="true") r = true;
                else r = false;
                cout << boolalpha << true << endl;
                return r;
            }
        }
    }
}

int main(){
    GetBool();
    return 0;
}
