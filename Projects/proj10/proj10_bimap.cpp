#include<vector>
using std::vector;
#include<string>
using std::string;
#include<utility>
using std::pair;
#include "proj10_bimap.h"

int main() {
/*
    BiMap<string,long> bm({ {"bill",1},{"alan",2},{"abby",3} });

    size_t result = bm.size();
    cout << result;
    */
/*
    ////PASS///
    BiMap<string,long> bm;
    bool result;

    result = bm.add("bill", 1);
    cout<< result;
    result = bm.add("bill", 2);
    cout << result;
    result = bm.add("john", 1);
    cout << result;
*/

/*
    /////PASS////
    BiMap<string,long> bm;
    bool bool_result;
    string str_result;
    bool_result = bm.add("bill", 1);
    bool_result = bm.add("alan", 2);
    bool_result = bm.add("fred", 3);
    bool_result = bm.add("fred", 7);
    
    ostringstream oss;
    oss << bm;
    str_result = oss.str();
    cout << str_result;
    //size_t result2 = bm.size();
    //cout << result2; 
   
    //string ans="alan:2, bill:1, fred:3";

*/
/*
    //////PASS////
    BiMap<string,long> bm({ {"bill",1},{"alan",2},{"abby",3}});
    
    ostringstream oss;
    oss << bm;
    string str_result = oss.str();
    cout << str_result;
 */

    BiMap<string,long> bm;
    bool bool_result;
    string str_result;
    bool_result = bm.add("bill", 1);
    bool_result = bm.add("alan", 2);
    bool_result = bm.add("fred", 3);
    bool_result = bm.add("fred", 7);
    //bool_result = bm.add("charlie", 4);
   // bool_result = bm.add("chris", 5);
   // bool_result = bm.add("brad", 10);
    ostringstream oss;
    oss << bm;
    str_result = oss.str();
    string ans="alan:2, bill:1, fred:3";
    cout << str_result;
}
