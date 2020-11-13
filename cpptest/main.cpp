#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;

#include "derived.hpp"
#include "weipai.hpp"

#include <vector>
#include "string"
#include "initialize_list_y.hpp"
#include "rvalue.hpp"
#include "constexpression.hpp"
#include "bitset"
#include "getInteger.hpp"
#include "smart_pointer.hpp"
#include "move_operator.hpp"
#include "leetcode1.hpp"
#include "mutex_usage.hpp"
#include "explicit_usage.hpp"
#include "regex_usage.hpp"
#include "cs106_1search.hpp"
#include <unordered_map>
#include "cs106_2operator.hpp"
#include "cs106_3template.hpp"
#include "cs106_3templatetemplate.hpp"
#include "cs106_4inherit.hpp"

class Node1{
public:
    Node1(){
        cout << "cons" << endl;
    }
    ~Node1(){
        cout << "del" << endl;
    }
};
int main(){
    unique_ptr<Node1> p(new Node1());
    p = nullptr;
    cout << "jj" << endl;
    return 0;
}
