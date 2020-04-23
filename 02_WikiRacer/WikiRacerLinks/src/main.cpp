#include <iostream>
#include <fstream>
#include <unordered_set>

using std::cout;            using std::endl;
using std::string;          using std::unordered_set;
using std::cerr;

/*
 * Note that you have to pass in the file as a single string
 * into the findWikiLinks function!
 * So we have to turn the passed-in file into a single string...
 * does that sound familiar at all?
 */
unordered_set<string> findWikiLinks(const string& page_html) {
    // TODO: delete this return statement and implement
    // the function!
    std::ifstream input(page_html.c_str());
    if(!input.is_open()){
        cout << "Open file fail";
    }
    unordered_set<string> ans;
    string page;
    string junk = ":";
    while(getline(input, page)){
//        cout << page << endl;
        string wiki = "href=\"/wiki/";
        string wikiend = "\"";
        auto ans_be = page.begin();
        while(ans_be != page.end()){
            ans_be = search(ans_be, page.end(), wiki.begin(), wiki.end());
            if(ans_be == page.end()) break;
            ans_be = ans_be +  + wiki.size();
            auto ans_end = search(ans_be, page.end(), wikiend.begin(), wikiend.end());
            string cur_ans = page.substr(ans_be-page.begin(), ans_end-ans_be);

            if(std::all_of(cur_ans.begin(), cur_ans.end(), [](char i){return i!=':';})){
                ans.insert(cur_ans);
            }

        }
    }

    return ans;
}

int main() {
    /* Note if your file reading isn't working, please go to the
     * projects tab on the panel on the left, and in the run section,
     * uncheck the "Run in terminal" box and re-check it. This
     * should fix things.
     */

    cout << "Enter a file name: ";
    string filename;
    getline(std::cin, filename);
    unordered_set<string> ans = findWikiLinks(filename);
    for(auto i: ans){
        cout << i <<endl;
    }

    // TODO:
    // - create a filestream from the filename, and convert
    //   it into a single string of data
    // - findWikiLinks
    // - print out the links you found, and use the provided
    //   test files under "Other files/res" to check whether
    //   your findWikiLinks function is working correctly!
    //
    // You got this!

    // Write code here

}
