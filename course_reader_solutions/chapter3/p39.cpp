//
// Created by yryang on 2020/11/13.
//

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

void DrawTriangle(int height, char c){
    int width = 2 * (height-1) + 1;
    for (int i = 0; i < height; ++i) {
        int c_num = 2 * i+1;
        int before = (width - c_num) / 2;
        cout << setfill(' ') << setw(before) << "" << setfill(c) << setw(c_num) << "" << endl;
    }
}

int main(){
    DrawTriangle(3, '*');

    return 0;
}