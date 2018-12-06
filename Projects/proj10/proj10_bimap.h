#pragma once

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
using std::sort; using std::lower_bound; using std::swap; using std::copy;
#include<sstream>
using std::ostringstream;
// add any other includes you might need!


template<typename K, typename V>
struct Node {
public:
  K first;
  V second;
  // constructors
  Node() = default;
  Node(K, V);
  // the rest
  bool operator<(const Node&) const;
  bool operator==(const Node&) const;
  friend ostream& operator<<(ostream &out, const Node &n) {
      string str = "";
      str = n.first + ":" + std::to_string(n.second);
    return out << str;
  }
};

//WRITE NODE function members HERE

template<typename K, typename V>
Node<K,V>::Node(K frst, V scd) { //constructor for node.
    first = frst;
    second = scd;
}

template<typename K, typename V>
bool Node<K,V>::operator==(const Node& n) const { //node operator == to compare objects
    return this.first == n.first;
}

template<typename K, typename V> 
bool Node<K,V>::operator<(const Node& n) const { //node operator < that compares 2 objects
    return this.first < n.first;
}


template<typename K, typename V>
class BiMap {
private:
  Node<K, V>* ordered_by_keys_; //Arys
  Node<K, V>* ordered_by_vals_;
  size_t last_;
  size_t capacity_;
  // private function members
  Node<K, V>* find_key(K key);
  Node<K, V>* find_value(V value);
  void grow();
  
public:
  // constructors
  BiMap(int sz = 2);
  BiMap(initializer_list< Node<K, V> >);
  // rule of three stuff
  BiMap(const BiMap&);
  BiMap operator=(BiMap);
  ~BiMap();
  // the rest
  size_t size();
  V value_from_key(K);
  K key_from_value(V);
  bool update(K, V);
  K remove_val(V value); 
  V remove_key(K key); 
  bool add(K, V);
  int compare(BiMap &);
  friend ostream& operator<<(ostream &out, const BiMap &bm) {
       string str = "";
       for(unsigned int i = 0; i < bm.last_; i++) {
            str += bm.ordered_by_keys_[i].first + ":" + std::to_string(bm.ordered_by_keys_[i].second) ;
            if(i != bm.last_-1) {
                str+= ", ";
            }
        }
       return out << str;   
  }
};

//WRITE BiMap function members HERE
template<typename K, typename V>
BiMap<K,V>::BiMap(int sz) { //constructor that sets size
    capacity_ = sz; //set all data members
    last_ = 0;
    ordered_by_keys_= new Node<K,V>[capacity_]{};
    ordered_by_vals_= new Node<K,V>[capacity_]{}; //capacity_ largest it can be before it gotta grow

}
template<typename K, typename V> //constructor 2 that has initializer list when created
BiMap<K,V>::BiMap(initializer_list< Node<K, V> > n) {
    capacity_ = std::distance(n.begin(), n.end()); //getting the capacity of intializer list
    last_ = 0;
    ordered_by_keys_= new Node<K,V>[capacity_]{};
    ordered_by_vals_= new Node<K,V>[capacity_]{};
    for(auto it = n.begin(); it!=n.end(); it++) { //loops through intitializer list and keeps adding
        add(it->first, it->second);
    }    
}

template<typename K, typename V>
BiMap<K,V>::BiMap(const BiMap<K,V> &s){ //copy function. Basically adds everything to the object you want to copy too
    capacity_ = s.capacity_;
    last_ = s.last_;
    ordered_by_keys_= new Node<K,V>[s.capacity_];
    ordered_by_vals_= new Node<K,V>[s.capacity_];
    copy(s.ordered_by_keys_, s.ordered_by_keys_+s.capacity_, ordered_by_keys_);
    copy(s.ordered_by_vals_, s.ordered_by_vals_+s.capacity_, ordered_by_vals_);
    
}



template<typename K, typename V>
Node<K,V>* BiMap<K,V>::find_key(K key) { //lower bound used here to find the key
  auto result = std::lower_bound(ordered_by_keys_,
                          ordered_by_keys_ + last_, key,
                          [](auto p, auto key) { return p.first < key; });
    return result;

}
template<typename K, typename V>
Node<K,V>* BiMap<K,V>::find_value(V val) { //lower bound used here to find the val

  auto result = std::lower_bound(ordered_by_vals_,
                          ordered_by_vals_ + last_, val,
                          [](auto p, auto val) { return p.second < val; });
    return result;

}

template<typename K, typename V>
BiMap<K,V>::~BiMap(){ //deletes to avoid leaking. Works like a charm.
    delete [] ordered_by_keys_;
    delete [] ordered_by_vals_;
}

template<typename K, typename V>
BiMap<K,V> BiMap<K,V>::operator=(BiMap s){ //operator that swaps some memory allocations
    // just did the swap here
    swap(this->capacity_, s.capacity_);
    swap(this->last_, s.last_);
    swap(this->ordered_by_keys_, s.ordered_by_keys_);
    swap(this->ordered_by_vals_, s.ordered_by_vals_);
    return *this;
}


template<typename K, typename V>
size_t BiMap<K,V>::size() { //just returns the size
    return last_;
}


template<typename K, typename V>

bool BiMap<K,V>::add(K key, V val) { 

    Node<K,V>* elek = find_key(key); //finds key
    Node<K,V>* elev = find_value(val); //finds val
    int frontlast = 0;
    int frontlast2 = 0;
    if(elek->first != key && elev->second != val && elek != nullptr && elev != nullptr) { //if its not equal to nullptr and key not already in it, then it goes in
        if(last_==0) { //add one element, then compare from there.
            ordered_by_keys_[0] = {key, val};
            ordered_by_vals_[0] = {key, val};
            last_ += 1; //last increments when you add a node element.
        }
        else { //if last isn't 0, then proceed to try to order the function
            Node<K,V> *new_ary; //front ary
            Node<K,V> *new_ary2; //back end ary
            /////
            //so basically, these ary's are set for keys and vals. new_ary is the old ary up to the insert point. We insert, then new_ary 2 is the back end, the old array, all the way until the end.
            //the new_ary3 and new_ary4 function the same way, but they are for the order by values.
            Node<K,V> *new_ary3;
            Node<K,V> *new_ary4;
            ///result is for order by keys, result 2 for order by vals
            //since you cannot just merge two arrays together, i created a result where I added both new_ary and new_ary2 to result.
            Node<K,V> *result;
            Node<K,V> *result2;
            new_ary = new Node<K,V>[capacity_]{};
            new_ary2 = new Node<K,V>[capacity_]{};
            /////////////VALS////////////
            new_ary3 = new Node<K,V>[capacity_]{};
            new_ary4 = new Node<K,V>[capacity_]{};

            for(unsigned int i = 0; i < last_; i++) {
                if(ordered_by_keys_[i].first > key) { //ORDER KEYS
                    copy(ordered_by_keys_, ordered_by_keys_+i, new_ary); //copy old array up until the insert point
                    new_ary[i] = {key,val}; //insert the key,val
                    frontlast = i+1; //front last is the end of the new_ary
                    copy(ordered_by_keys_+i, ordered_by_keys_ + capacity_, new_ary2); //back end of old array copied and put into new_ary2
                    last_ += 1; //last increments once insert new element
                    capacity_ +=1; //capacity also increments
                    result = new Node<K,V>[capacity_]{};  
                    break;
                }              
                if (i == last_-1) { //if no key is bigger, then we reach end and dont need back end ary.
                    copy(ordered_by_keys_, ordered_by_keys_+last_, new_ary);
                    new_ary[last_] = {key,val};
                    frontlast = i+2;
                    capacity_ +=2;
                    result = new Node<K,V>[capacity_]{}; 
                    last_ += 1; //last increments by 1 again
                    break;
                }
            }
//////////////////////////////////////////////////////////////////////////////
            for(unsigned int i = 0; i < last_; i++) { //this is ordering for values, same function as above, just read above comments.
                if(ordered_by_vals_[i].second > val) { //ORDER VALUES   
                    copy(ordered_by_vals_, ordered_by_vals_+i, new_ary3);
                    new_ary3[i] = {key,val};
                    frontlast2 = i+1;
                    copy(ordered_by_vals_+i, ordered_by_vals_ + last_-1, new_ary4);
                    result2 = new Node<K,V>[capacity_]{};  
                    break;
                }               
                if (i == last_-1) {
                    copy(ordered_by_vals_, ordered_by_vals_+last_-1, new_ary3);
                    new_ary3[last_-1] = {key,val};
                    frontlast2 = i+1;
                    result2 = new Node<K,V>[capacity_]{};
                    break;
                }
            }


            int t = 0;
            //these for loops go through the front end and back end array and add them to result.
            //I had to do it this way b/c i couldn't just add arrays together
            for (unsigned int i = 0; i<sizeof(new_ary); i++) {
                if(i == frontlast ) {
                    break;
                }
                else {
                    result[i] = new_ary[i];
                    t++;
                }
            }
            for (unsigned int i = 0; i<sizeof(new_ary2); i++) {
                if(i == last_-1) {
                    break;
                }
                else{
                    result[t] = new_ary2[i];
                    t++;
                }
            }
            swap(result, ordered_by_keys_);
            delete [] result; 
            delete [] new_ary; //deletes the memory allocations so no leaking
            delete [] new_ary2;
        //////////////////////////////////////////////////////////////////////////
       //Same function as the stuff above, just read comments above. This is for the values for proper ordering
            int tt = 0;
            for (unsigned int i = 0; i<sizeof(new_ary3); i++) {
                if(i == frontlast2) {
                    break;
                }
                else {
                    result2[i] = new_ary3[i];
                    tt++;
                }
            }
            
            for (unsigned int i = 0; i<sizeof(new_ary4); i++) {
                if(i == last_-1) {
                    break;
                }
                else{
                    result2[tt] = new_ary4[i];
                    tt++;
                }
            }
            swap(result2, ordered_by_vals_);
            delete [] result2; 
            delete [] new_ary3;
            delete [] new_ary4; 
        }
    }
    else {
        return false; //if nullptr or key found, return false
    } 
    return true;
}

template<typename K, typename V>
void BiMap<K,V>::grow() { //grows the capacity of arrays
    Node<K,V> *new_ary;
    Node<K,V> *new_ary2;

    if (capacity_ == 0){ //copied from the example code and modified.
        new_ary = new Node<K,V>[1]{};
        capacity_ = 1;
        // ary_ empty, just assign
        ordered_by_keys_ = new_ary;
        ordered_by_vals_ = new_ary;
        std::swap(new_ary, ordered_by_keys_);
        std::swap(new_ary, ordered_by_vals_);
        delete[] new_ary;
    }
    else{ //doubles the capacity of the function
        // use {} to init to default
        new_ary = new Node<K,V>[capacity_ * 2]{};
        new_ary2 = new Node<K,V>[capacity_ * 2]{};
        copy(ordered_by_keys_, ordered_by_keys_+capacity_, new_ary);
        copy(ordered_by_vals_, ordered_by_vals_+capacity_, new_ary2);
        capacity_ *= 2;
        // stl swap, not Stack swap
        std::swap (new_ary, ordered_by_keys_);
        std::swap (new_ary2, ordered_by_vals_);
        delete [] new_ary; //new_ary ptng to old ary mem so now old.
        delete [] new_ary2;

    }
}

template<typename K, typename V>
K BiMap<K,V>::key_from_value(V value) { //finds the value and returns the key if found, otherwise default it.
    K key = K();
    for(auto i= ordered_by_keys_; i != ordered_by_keys_ + last_; i++) {
        if(i->second == value) { //if value is found, return the key
            key = i->first;
            break;
        }
    }
    return key; //empty string if not found.
}

template<typename K, typename V>
V BiMap<K,V>::value_from_key(K key) { //finds the key and returns the value if found, otherwise default it.
    V value = V();
    for(auto i= ordered_by_keys_; i != ordered_by_keys_ + last_; i++) {
        if(i->first== key) { //if value is found, return the key
            value = i->second;
            break;
        }
    }
    return value; //empty string if not found.
}

template<typename K, typename V>
bool BiMap<K,V>::update(K key, V val) { //done
    int tester = 0;
    for(auto i= ordered_by_keys_; i != ordered_by_keys_ + last_; i++) { //update key order vector
        if(i->first == key && i->second != val) {
            i->second = val;
            tester = 1;
        }
        else if(i->first == key && i->second == val) {
            tester = 1;
        }
    }
    for(auto i= ordered_by_vals_; i != ordered_by_vals_ + last_; i++) { //update val order vector
        if(i->first == key && i->second != val) {
            i->second = val;
            tester = 1;
        }
        else if(i->first == key && i->second == val) {
            tester = 1;
        }
    } 
    if(tester == 1) { //if indeed we did find a key or value, return true. Otherwise, false.
        return true;
    } 
    else{
        return false; //will only reach this line if key is not ever equal to any keys in pair.
    }         
}

template<typename K, typename V>
int BiMap<K,V>::compare(BiMap<K,V> &bm) {

  // find first mismatch;
  auto diff = std::mismatch( //copied from proj9 soln. Pretty straightforward.
      ordered_by_keys_, ordered_by_keys_ + last_, bm.ordered_by_keys_, bm.ordered_by_keys_ + bm.last_,
      [](auto a, auto b) { return a.first == b.first; });

  return diff.first == ordered_by_keys_ + last_
             ? diff.second == bm.ordered_by_keys_ + bm.last_
                   ? 0  // both vectors are same length and no mismatch
                   : -1 // other is longer, but no mismatch
             : diff.second == bm.ordered_by_keys_ + bm.last_
                   ? 1 // this is longer, but no mismatch
                   : diff.first->first < diff.second->first
                         ? -1
                         : 1; // actual mismatch
  
}













//////////////////////////////ITS LIT/////////////////////////////////////

template<typename K, typename V>
V BiMap<K,V>::remove_key(K key) {
    V val = V();
    int k = 0;
    int v = 0;
    int t = 0;
    int test =0;
    for(auto i= ordered_by_keys_; i != ordered_by_keys_ + last_; i++) {
        if(i->first == key) { //if value is found
            val = i-> second;
            test =1; //whats test? test says that we found the key, and we have removed it. Therefore, minus the last(happens below) by 1
            break;
        }
        k++;
    }
    t = k;
    for(auto i= ordered_by_keys_ + k; i != ordered_by_keys_ + last_; i++) { //this slides elements over
        ordered_by_keys_[t] = ordered_by_keys_[t+1];
        t++;
    }
    ////////////////////////////Vals test below////////////////////
    for(auto i= ordered_by_vals_; i != ordered_by_vals_ + last_; i++) {
        if(i->first == key) { //if value is found
            val = i-> second;
            break;
        }
        v++;
    }
    t = v;
    for(auto i= ordered_by_vals_ + v; i != ordered_by_vals_ + last_; i++) { //slides elements over
        ordered_by_vals_[t] = ordered_by_vals_[t+1];
        t++;
    }

    if(test ==1 ) { //if key or val was indeed removed
        last_-=1;
    }

    return val; //empty string if not found.
}



template<typename K, typename V>
K BiMap<K,V>::remove_val(V value) { //same functionality as the remove key, just removes the value instead
    K key = K();
    int k = 0;
    int t = 0;
    int v = 0;
    int test =0;
    for(auto i= ordered_by_keys_; i != ordered_by_keys_ + last_; i++) {
        if(i->second == value) { //if value is found
            key = i-> first;
            test =1;
            break;
        }
        k++;
    }
    t = k;
    for(auto i= ordered_by_keys_ + k; i != ordered_by_keys_ + last_; i++) {
        ordered_by_keys_[t] = ordered_by_keys_[t+1];
        t++;
    }
    ///////////////////////////////////
    for(auto i= ordered_by_vals_; i != ordered_by_vals_ + last_; i++) {
        if(i->second == value) { //if value is found
            key = i-> first;
            test =1;
            break;
        }
        v++;
    }
    t = v;
    for(auto i= ordered_by_vals_ + v; i != ordered_by_vals_ + last_; i++) {
        ordered_by_vals_[t] = ordered_by_vals_[t+1];
        t++;
    }
    if(test ==1 ) {
        last_-=1;
    }
    return key; //empty string if not found.
}

