//
// Created by yryang on 2020/4/10.
//

#ifndef CPPTEST_CS106_1SEARCH_HPP
#define CPPTEST_CS106_1SEARCH_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;



void test_search(){
    string link = "<p><b>Stephen King</b> is a <a href=\"/wiki/New_Zealand\" title=\"New Zealand\">New Zealand</a> <a href=\"/wiki/Conservation_movement\" title=\"Conservation movement\">conservationist</a>.</p>";
    string wiki = "href=\"/wiki/";
    string wikiend = "\"";
    auto ans_be = link.begin();
    while(ans_be != link.end()){
        ans_be = search(ans_be, link.end(), wiki.begin(), wiki.end());
        if(ans_be == link.end()) break;
        ans_be = ans_be +  + wiki.size();
        auto ans_end = find(ans_be, link.end(), wikiend[0]);
//        auto ans_end = search(ans_be, link.end(), wikiend.begin(), wikiend.end());
        string ans = link.substr(ans_be-link.begin(), ans_end-ans_be);
        cout << ans << endl;
    }
    string a = "jk";
    string b = "jk";
    auto c = a==b;
    cout <<c ;
}

#endif //CPPTEST_CS106_1SEARCH_HPP
