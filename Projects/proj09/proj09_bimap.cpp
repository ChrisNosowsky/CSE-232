#include "proj09_bimap.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
using std::string;
using std::cout;
using std::cin;
using std::ifstream;
using std::vector;
using std::to_string;
using std::stoi;
using std::endl;
using std::make_pair;
//{(1,2),(),()...} so p[0][0]=1
//first vec is on order of keys
//second vec is on order by values

//NOTE: may have to change for loops in member functions to search for p?? maybe not idk.

BiMap::BiMap(initializer_list<pair<string, string>> p) { //done
    for(auto it = p.begin(); it!=p.end(); it++) {
        add(it->first, it->second);
    }
}

vector<pair<string,string>>::iterator BiMap::find_key(string key) { //done
    for(auto it = ordered_by_keys_.begin(); it != ordered_by_keys_.end(); it++) { //wrote this in order to avoid segmentation fault
        if(it->first == key) {
            auto f = ordered_by_keys_.end() +1;
            return f;
        }
    }
    auto id=std::lower_bound(ordered_by_keys_.begin(),ordered_by_keys_.end(),key, //Value to compare
                [](std::pair<string,string> const &x, string k) -> bool      // Lambda
                {
                    return x.first < k; });            
    return id;
}

vector<pair<string,string>>::iterator BiMap::find_value(string value) { //done
    for(auto it = ordered_by_vals_.begin(); it != ordered_by_vals_.end(); it++) {
        if(it->second == value) {
            auto f = ordered_by_vals_.end()+1;
            return f;
        }
    }
    auto id=std::lower_bound(ordered_by_vals_.begin(),ordered_by_vals_.end(),value, //Value to compare
                [](std::pair<string,string> const &y, string val)  ->bool     // Lambda
                { return y.second < val; });             
    return id;
}


size_t BiMap::size() { //done
    size_t c = 0;
    for(auto i=ordered_by_keys_.begin(); i != ordered_by_keys_.end(); i++) { //increases count for every element
        c++;
    }
    return c;
}

string BiMap::key_from_value(string value) { //done
    string key = "";
    for(auto i=ordered_by_keys_.begin(); i != ordered_by_keys_.end(); i++) {
        if(i->second == value) { //if value is found, return the key
            key = i->first;
            break;
        }
    }
    return key; //empty string if not found.
}

string BiMap::value_from_key(string key) { //done
    string value = "";
    for(auto i=ordered_by_keys_.begin(); i != ordered_by_keys_.end(); i++) {
        if(i->first == key) { //if the key is found, return the value
            value = i->second; 
            break;
        }
    }
    return value;   //empty string if not found
}

bool BiMap::update(string key, string val) { //done
    int tester = 0;
    for(auto i=ordered_by_keys_.begin(); i != ordered_by_keys_.end(); i++) { //update key order vector
        if(i->first == key && i->second != val) {
            i->second = val;
            tester = 1;
        }
        else if(i->first == key && i->second == val) {
            tester = 1;
        }
    }
    for(auto i=ordered_by_vals_.begin(); i != ordered_by_vals_.end(); i++) { //update val order vector
        if(i->first == key && i->second != val) {
            i->second = val;
            tester = 1;
        }
        else if(i->first == key && i->second == val) {
            tester = 1;
        }
    } 
    if(tester == 1) {
        return true;
    } 
    else{
        return false; //will only reach this line if key is not ever equal to any keys in pair.
    }         
}

pair<string, string> BiMap::remove (string element) { //done.
    int k = 0;
    int n = 0;
    pair<string, string> prod ("",""); //tester pairs
    pair<string,string> prod2 ("","");
    pair<string,string> prod3 ("","");
    for(auto i=ordered_by_keys_.begin(); i != ordered_by_keys_.end(); i++) { //update key order vector
        if(i->first == element || i->second == element) { // if they are equal to the element
            if(k==0) {
                prod3.first = i->first;
                prod3.second = i->second;
                ordered_by_keys_.erase(i); //erases
                break; //had to do this in order to avoid seg fault
            }

            if(k==1) {
                prod2.first = element;
                prod2.second = element;
                ordered_by_keys_.erase(i);
            }
            k++;
        }
        n++;

    } 
    int r = 0; //how many times we find element
    int s = 0; //index/pos
    for(auto i=ordered_by_vals_.begin(); i != ordered_by_vals_.end(); i++) { //update key order vector
        if(i->first == element || i->second == element) {
            if(r==0) {
                ordered_by_vals_.erase(i);
                break;
            }

            if(r==1) {
                ordered_by_vals_.erase(i);
            }
            r++;
        }
        s++; //index
    }
    
    if(k == 0) { //if the k is equal to zero, then it ran once, return the first and second values of the found element to remove
        return prod3;
    } 
    else if(k==1) {
        return prod;
    }  
    else {
        return prod2;
    }

}
//first
bool BiMap::add(string key, string val) { //done
    auto itr = find_key(key);
    auto itr2 = find_value(val);
    int index = std::distance(ordered_by_keys_.begin(), itr);
    int index2 = std::distance(ordered_by_vals_.begin(), itr2); //distance used to get the index distance
    if((index ==0 || itr != ordered_by_keys_.end()+1)&& (index2 == 0 || itr2!= ordered_by_vals_.end()+1)) { //means cant find
        ordered_by_keys_.insert(itr,make_pair(key,val));
        ordered_by_vals_.insert(itr2,make_pair(key,val));
    }
    else {
        return false;
    }
    return true;

}



int BiMap::compare(BiMap& bi2) {
    int n = 0;
    int n2 = 0;
    int i = 0;
    int t = 0;
    for(auto it = this->ordered_by_keys_.begin(); it!= this->ordered_by_keys_.end(); it++) {
        n++;
    }
    for(auto it = bi2.ordered_by_keys_.begin(); it!= bi2.ordered_by_keys_.end(); it++) {
        n2++;
    }
    if(n > n2) {
        return 1;
    }
    else if(n < n2) {
        return -1;
    }
    else {
        for(auto it = this->ordered_by_keys_.begin(); it!= this->ordered_by_keys_.end(); it++) {
            if(this->ordered_by_keys_[i].first == bi2.ordered_by_keys_[i].first) {
                t = 0;
            }
            else if(this->ordered_by_keys_[i].first > bi2.ordered_by_keys_[i].first) {
                return 1;
            }
            else {
                return -1;
            }
            i++;
    }
    return 0;
}
}

BiMap BiMap::merge(BiMap& bi2) {
    for(auto it = this->ordered_by_keys_.begin(); it!= this->ordered_by_keys_.end(); it++) {
        add(it->first, it->second);
        
        }
    for(auto itr = bi2.ordered_by_keys_.begin(); itr!= bi2.ordered_by_keys_.end(); itr++) {
        add(itr->first, itr->second); 
    }
    BiMap bi3 = *this; //points to this object
    return bi3; //returns new bimap
}


ostream& operator<<(ostream& h, BiMap& bi2) { //ostream operator
    string str = ""; //starter string
    for(auto it = bi2.ordered_by_keys_.begin(); it!= bi2.ordered_by_keys_.end(); it++) {
        if(it == bi2.ordered_by_keys_.end()-1) {
            str += it->first + " : " + it->second; //format
        }
        else{
            str += it->first + " : " + it->second + ", ";
        }
    }
    return h<<str;
}

