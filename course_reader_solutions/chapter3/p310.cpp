//
// Created by yryang on 2020/11/14.
//


#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

ifstream &OpenFile(ifstream& f){
    cout << "Please input the file name you want to open: " << endl;
    string fileName;
    while (getline(cin, fileName, '\n')){
        cout << "[Before open] f.fail is " << boolalpha << f.fail() << endl;
        f.open(fileName.c_str());
        cout << "[After open] f.fail is " << boolalpha << f.fail() << endl;
        if (f.fail()){
            cout << "Opening file " << fileName << " failed." << endl;
            f.clear();
        }else{
            return f;
        }
    }
}

int main(){
    ifstream f;
    OpenFile(f);
    return 0;
}