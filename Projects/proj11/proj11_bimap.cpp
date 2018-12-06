#include<iostream>
using std::ostream; using std::cout; using std::endl;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<algorithm>
using std::swap; using std::copy;
#include<sstream>
using std::ostringstream;
#include "proj11_bimap.h"


int main() {
    BiMap<string,long> bm1({ {"bill",1},{"alan",2},{"abby",3} });
    BiMap<string, long> bm2({ {"alan",4},{"abby", 5},{"john",7} });
    BiMap<string, long> bm3({ {"abby",5}, {"john",2} });

    BiMap<string,long> bm_merge = bm1.merge(bm2);
    ostringstream oss;
    oss << bm_merge;
    string result1 = oss.str();
    string ans1 = "abby:3, alan:2, bill:1, john:7";
    //cout << result1;

    bm_merge = bm2.merge(bm1);
    oss.str("");
    oss << bm_merge;
    string result2 = oss.str();
    string ans2 = "abby:5, alan:4, bill:1, john:7";
    //cout << result2;

    bm_merge = bm3.merge(bm1);
    oss.str("");
    oss << bm_merge;
    string result3 = oss.str();
    string ans3 = "abby:5, bill:1, john:2";
    cout << result3;
}
