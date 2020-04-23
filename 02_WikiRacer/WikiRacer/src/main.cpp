
#include <iostream>
#include <iomanip>
#include <unordered_set>
#include <vector>
#include <queue>
#include <unordered_map>
#include "wikiscraper.h"


using std::cout;            using std::endl;
using std::string;          using std::vector;
using std::priority_queue;  using std::unordered_map;
using std::unordered_set;




/*
 * This is the function you will be implementing. It takes
 * two string representing the names of a start_page and
 * end_page and is supposed to return a ladder, represented
 * as a vector<string>, of links that can be followed from
 * start_page to get to the end_page.
 *
 * For the purposes of this algorithm, the "name" of a Wikipedia
 * page is what shows at the end of the URL when you visit that page
 * in your web browser. For ex. the name of the Stanford University
 * Wikipedia page is "Stanford_University" since the URL that shows
 * in your browser when you visit this page is:
 *
 *       https://en.wikipedia.org/wiki/Stanford_University
 */
vector<string> findWikiLadder(const string& start_page, const string& end_page) {
    // TODO: Fill in the findWikiLinks method in wikiscraper.cpp,
    //       then write this  function as per the handout.
    //
    //                Best of luck!
    WikiScraper wikiscraper;

    // the compare function for priority_queue: using the common links to set the priority.
    auto cmp_fn = [&](vector<string> ladder1, vector<string> ladder2){
        string s1 = ladder1.back();
        string s2 = ladder2.back();
        unordered_set<string> end = wikiscraper.getLinkSet(end_page);
        unordered_set<string> l1 = wikiscraper.getLinkSet(s1);
        unordered_set<string> l2 = wikiscraper.getLinkSet(s2);
//        std::cout << "scraped l1 l2 " << s1 << " " << s2 <<endl;
        unordered_set<string> ans1;
        unordered_set<string> ans2;
        std::copy_if(l1.begin(), l1.end(), std::inserter(ans1, ans1.begin()),
                     [&end](const string& ele){return end.count(ele) > 0;});
        std::copy_if(l2.begin(), l2.end(), std::inserter(ans2, ans2.begin()),
                     [&end](const string& ele){return end.count(ele) > 0;});
//        cout << ans1.size() <<endl;
        return ans1.size() < ans2.size();
    };

    std::priority_queue<vector<string>, vector<vector<string> >, decltype (cmp_fn)> ladder_queue(cmp_fn);
    vector<string> start_ladder{start_page};
    ladder_queue.push(start_ladder);
    vector<string> ans;
    unordered_set<string> visited;
    visited.insert(start_page);
    while(!ladder_queue.empty()){
        auto cur_ladder = ladder_queue.top();
        ladder_queue.pop();
        auto cur_page = cur_ladder.back();
        auto start_links = wikiscraper.getLinkSet(cur_page);
        cout << "Has scraped the link: " << cur_page << endl;
        for(auto i : start_links){
            if(visited.find(i) == visited.end()){
                visited.insert(i);
                auto copied_ladder = cur_ladder;
                if(i == end_page){
                    cout << " find: " <<endl;
                    copied_ladder.push_back(i);
                    return copied_ladder;
                }
                copied_ladder.push_back(i);
                ladder_queue.push(copied_ladder);
            }

        }
    }

    return ans;
}



int main() {
//    auto ladder = findWikiLadder("Fruit", "Strawberry");
    auto ladder = findWikiLadder("Milkshake", "Gene");
    cout << endl;

    if(ladder.empty()) {
        cout << "No ladder found!" << endl;
    } else {
        cout << "Ladder found:" << endl;
        cout << "\t";

        // TODO: Print the ladder here!
        for(auto i: ladder){
            cout << i << "  --->  ";
        }
    }

    return 0;
}




