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
using std::swap; using std::copy;
#include<sstream>
using std::ostringstream;

//
// Node
//
template<typename K, typename V>
struct Node {
  K first;
  V second;
  Node *next = nullptr;
  
  Node() = default;
  Node(K,V);
  Node(const Node&);
  bool operator==(const Node&) const;
  friend ostream& operator<<(ostream &out, const Node &n){ //update this/////
    string str = "";
    str = n.first + ":" + std::to_string(n.second);
    return out << str;
  }
};

//WRITE NODE FUNCTIONS HERE

template<typename K, typename V>
Node<K,V>::Node(K frst, V scd) { //constructor for node.
    first = frst;
    second = scd;
}


template<typename K, typename V>
bool Node<K,V>::operator==(const Node& n) const { //node operator == to compare objects
    return this.first == n.first;
}


//
// BiMap
// 
template<typename K, typename V>
class BiMap{
 private:
  Node<K,V>* ordered_by_keys_head_ = nullptr;
  Node<K,V>* ordered_by_keys_tail_ = nullptr;
  
  Node<K,V>* ordered_by_vals_head_ = nullptr;
  Node<K,V>* ordered_by_vals_tail_ = nullptr;
 
  size_t sz_ = 0;
  
  Node<K,V>* find_key(K);
  Node<K,V>* find_value(V);
  
 public:
  BiMap()=default;
  BiMap(initializer_list< Node<K,V> >);
  //
  BiMap (const BiMap&);
  BiMap operator=(BiMap);
  ~BiMap();
  size_t size();
  K remove_val(V value); 
  V remove_key(K key); 
  bool add(K,V);
  V value_from_key(K);
  K key_from_value(V);
  bool update(K,V);  
  int compare(BiMap&);
  BiMap merge (BiMap&);

  friend ostream& operator<<(ostream &out, const BiMap &bm){ //done?
    ostringstream oss;
    unsigned int i = 0;
    for(auto ptr = bm.ordered_by_keys_head_; ptr != nullptr; ptr = ptr->next) {
        if(bm.sz_-1 > i) { //as long as it is not the last element, add a comma
            oss << *ptr << ", ";
        }
        else {
            oss << *ptr;
        }
	    i++;
    }
    string s = oss.str();
    return out << s; 
  }  
};

//WRITE BiMap FUNCTIONS HERE

template<typename K, typename V>
BiMap<K,V>::BiMap(initializer_list< Node<K,V> > n) { //constructor that sets size
    for(auto it = n.begin(); it!=n.end(); it++) { //loops through intitializer list and keeps adding
        add(it->first, it->second);
    }   
}

template<typename K, typename V> //done.
BiMap<K,V>::BiMap(const BiMap<K,V> &sl){ //copy function. Basically adds everything to the object you want to copy too
    if (sl.ordered_by_keys_head_ == nullptr){ //if it was null obj, then update the head and tail to be null.
	ordered_by_keys_head_ = nullptr;
    ordered_by_keys_tail_ = nullptr;
    }
    else{
	ordered_by_keys_head_ = new Node<K,V>(sl.ordered_by_keys_head_->first, sl.ordered_by_keys_head_->second);
	ordered_by_keys_tail_ = ordered_by_keys_head_;
	ordered_by_vals_head_ = new Node<K,V>(sl.ordered_by_vals_head_->first, sl.ordered_by_vals_head_->second);
	ordered_by_vals_tail_ = ordered_by_vals_head_;    
    Node<K,V>* sl_ptr = sl.ordered_by_keys_head_->next;
    Node<K,V>* sl_ptr2 = sl.ordered_by_vals_head_->next;
	Node<K,V>* new_node;
    Node<K,V>* new_node2;
	while (sl_ptr != nullptr && sl_ptr2 != nullptr){
	    new_node = new Node<K,V>(sl_ptr->first, sl_ptr->second);
        new_node2 = new Node<K,V>(sl_ptr2->first, sl_ptr2->second);
	    ordered_by_keys_tail_->next = new_node;
        ordered_by_vals_tail_->next = new_node2;
	    sl_ptr = sl_ptr->next;
        sl_ptr2 = sl_ptr2->next;
	    ordered_by_keys_tail_ = new_node;
        ordered_by_vals_tail_ = new_node2;
	}
    }
}



template<typename K, typename V> //done.
BiMap<K,V> BiMap<K,V>::operator=(BiMap sl){ //operator that swaps some memory allocations
    swap(ordered_by_keys_head_, sl.ordered_by_keys_head_);
    swap(ordered_by_vals_head_, sl.ordered_by_vals_head_);
    swap(ordered_by_keys_tail_, sl.ordered_by_keys_tail_);
    swap(ordered_by_vals_tail_, sl.ordered_by_vals_tail_);
    swap(sz_, sl.sz_);
    return *this;
}

template<typename K, typename V> //something wrong with this function
BiMap<K,V>::~BiMap(){ //deletes to avoid leaking. Works like a charm.
    delete ordered_by_keys_head_; //bye bye
    delete ordered_by_vals_head_; 
    ordered_by_keys_head_ = nullptr; //setting them back to nullptr, probably a little extra but thats just me.
    ordered_by_vals_head_ = nullptr;
    ordered_by_keys_tail_ = nullptr;
    ordered_by_vals_tail_ = nullptr;
}
template<typename K, typename V>
size_t BiMap<K,V>::size() { //just returns the size
    return sz_;
}

template<typename K, typename V>
Node<K,V>* BiMap<K,V>::find_key(K key) {
for(auto ptr = ordered_by_keys_head_; ptr != nullptr; ptr = ptr -> next) {
    if(ptr->first == key) { //find key? return that key!
        return ptr;
    }
}
return nullptr; // didnt find key? retuurn nullptr!
}

template<typename K, typename V>
Node<K,V>* BiMap<K,V>::find_value(V val) { //same thing as above but finding the val
for(auto ptr = ordered_by_vals_head_; ptr != nullptr; ptr = ptr -> next) {
    if(ptr->second == val) {
        return ptr;
    }
}
return nullptr;
}


template<typename K, typename V>
bool BiMap<K,V>::add(K key, V val) {  //so how i set this up is by searching for the key and val in order by keys. if not found, then we can insert it into the list.
//There are 3 cases I test for. If im inserting in front, just change head. If middle, then you must update the next. If end, then change the tail and update it's next.
    auto fkey = find_key(key);
    auto fval = find_value(val);
    int frontcase = 0;
    int backcase = 0;
    int middlecase = 0;
    int pos = 0; //pos is key here. Tells us where we will insert if it's in the middle.
    
    if(fkey == nullptr && fval == nullptr) { //if we can't find key or value, we are good to add
        for(auto ptr = ordered_by_keys_head_; ptr != nullptr; ptr = ptr -> next) {
            if(ptr->first > key) {//front //if b is greater then a(u want to insr)
                frontcase = 1;
                break;
            }
            if(ptr->first < key)  { //no break here because we must test every case until it reaches end incase it indeed is the last insert.
                pos +=1;
                middlecase = 1;
            }
            if(ptr->first < key && ptr->next == nullptr) {
                middlecase = 0;
                backcase = 1;
                break;
            }
        }
        /////////////TEST CASES BELOW/////////////////
        ////////////FIRST TEST CASE A MUST FOR BOTH KEYS AND VALS/////////
        if(ordered_by_keys_head_ == nullptr) { //if keys is null then val is also null
            Node<K,V>* n = new Node<K,V>(key,val); 
            ordered_by_keys_head_ = n;
            ordered_by_keys_tail_ = n;
        }
//////////////////////////////Front Case Keys////////////////////////////
        if(frontcase == 1 && middlecase == 0) {
            Node<K,V>* n = new Node<K,V>(key,val); 
            //...maybe val
            n->next  = ordered_by_keys_head_;
            ordered_by_keys_head_ = n;
        }
        //////////////////////Middle Case Keys//////////////
        if(middlecase == 1) {
            Node<K,V>* n = new Node<K,V>(key,val);
            Node<K,V>* pre = nullptr;
            Node<K,V>* cur = nullptr; 
            cur = ordered_by_keys_head_;
            for(int i=0; i<pos;i++) {
                pre=cur;
                cur =cur->next;
            } //left off here for tonight////////////////////
            pre->next = n;
            n->next = cur;
        }
        ////////////////Back Case Keys////////////
        if(backcase == 1) {
            Node<K,V>* n = new Node<K,V>(key,val); 
            ordered_by_keys_tail_->next = n;
            ordered_by_keys_tail_ = n;
        }
////////////////////////////////ORDER VALS BELOW/////////////////////////////////////////////////////
        frontcase = 0; //reset these cases for the val tests
        backcase = 0;
        middlecase = 0;
        pos = 0;              
        for(auto ptr = ordered_by_vals_head_; ptr != nullptr; ptr = ptr -> next) {
            if(ptr->second > val) {//front //if b is greater then a(u want to insr)
                frontcase = 1;
                break;
            }
            if(ptr->second < val)  {
                pos +=1;
                middlecase = 1;
            }
            if(ptr->second < val && ptr->next == nullptr) {
                middlecase = 0;
                backcase = 1;
                break;
            }
        }
//////////////////////////////Front Case Vals////////////////////////////
        if(ordered_by_vals_head_ == nullptr) { //if keys is null then val is also null
            Node<K,V>* n = new Node<K,V>(key,val); 
            ordered_by_vals_head_ = n;
            ordered_by_vals_tail_ = n;
        }
        if(frontcase == 1 && middlecase == 0) {
            Node<K,V>* n = new Node<K,V>(key,val); 
            //...maybe val
            n->next  = ordered_by_vals_head_;
            ordered_by_vals_head_ = n;
        }
        //////////////////////Middle Case Valss//////////////
        if(middlecase == 1) {
            Node<K,V>* n = new Node<K,V>(key,val); //only thing im worried about is key,val
            Node<K,V>* pre = nullptr;
            Node<K,V>* cur = nullptr; 
            cur = ordered_by_vals_head_;
            for(int i=0; i<pos;i++) {
                pre=cur;
                cur =cur->next;
            } //left off here for tonight////////////////////
            pre->next = n;
            n->next = cur;
        }
        ////////////////Back Case Vals////////////
        if(backcase == 1) {
            Node<K,V>* n = new Node<K,V>(key,val); 
            ordered_by_vals_tail_->next = n;
            ordered_by_vals_tail_ = n;
        }
        sz_ +=1;
    }
    else {
        return false;
    }
   
    return true;
}



template<typename K, typename V>
K BiMap<K,V>::key_from_value(V value) { //finds the value and returns the key if found, otherwise default it.
    K key = K();
    for(auto ptr = ordered_by_keys_head_; ptr != nullptr; ptr = ptr -> next) {
        if(ptr->second == value) { //if value is found, return the key
            key = ptr->first;
            break;
        }
    }
    return key; //empty string if not found.
}


template<typename K, typename V>
V BiMap<K,V>::value_from_key(K key) { //finds the key and returns the value if found, otherwise default it.
    V value = V();
    for(auto ptr = ordered_by_keys_head_; ptr != nullptr; ptr = ptr -> next) {
        if(ptr->first== key) { //if value is found, return the key
            value = ptr->second;
            break;
        }
    }

    return value; //empty string if not found.
}

template<typename K, typename V>
bool BiMap<K,V>::update(K key, V val) { //done
    int tester = 0;
    for(auto ptr = ordered_by_keys_head_; ptr != nullptr; ptr = ptr -> next) { //update key order
        if(ptr->first == key && ptr->second != val) {
            ptr->second = val;
            tester = 1;
        }
        else if(ptr->first == key && ptr->second == val) {
            tester = 1;
        }
    }
    for(auto ptr = ordered_by_vals_head_; ptr != nullptr; ptr = ptr -> next) { //update val order
        if(ptr->first == key && ptr->second != val) {
            ptr->second = val;
            tester = 1;
        }
        else if(ptr->first == key && ptr->second == val) {
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
V BiMap<K,V>::remove_key(K key) {
    V val = V();
    int test = 0; 
    unsigned int pos = 0;
    for(auto ptr = ordered_by_keys_head_; ptr != nullptr; ptr = ptr -> next) { //this is like add funcion, except we are testing to see if we found the key.
        if(key == ptr->first) {
            val = ptr->second;
            test = 1;
            break;
        }
        pos++;
    }

    ///////////////deletes cases///
    if(pos == 0) { //front delete
        Node<K,V>* n = new Node<K,V>(key,val); 
        n = ordered_by_keys_head_;
        ordered_by_keys_head_ = ordered_by_keys_head_ -> next;
        delete n;
    }
        //////////////////////Middle Case Keys//////////////
    if(pos < sz_-1) {//middle delete //may just be size.
        Node<K,V>* pre = new Node<K,V>(key,val);
        Node<K,V>* cur = new Node<K,V>(key,val); 
        cur = ordered_by_keys_head_;
        for(unsigned int i=0; i<pos;i++) {
            pre=cur;
            cur =cur->next;
        }
        pre->next = cur->next;
    }
        ////////////////Back Case Keys////////////
    if(pos == sz_ -1) { //back delete
        Node<K,V>* cur = new Node<K,V>(key,val);
        Node<K,V>* prev = new Node<K,V>(key,val); 
        cur = ordered_by_keys_head_;
        while (cur->next!=nullptr) {
            prev = cur;
            cur = cur->next;
        }
        ordered_by_keys_tail_ = prev;
        prev->next = nullptr;
    }
/////////////////////////////////////VALS BELOW/////////////////////////////////////////////
    pos = 0;
    for(auto ptr = ordered_by_vals_head_; ptr != nullptr; ptr = ptr -> next) {
        if(key == ptr->first) {
            val = ptr->second;
            break;
        }
        pos++;
    }

    ///////////////deletes cases///
////////////////////////////////////////////////!!ITS LIT FAM!!////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(pos == 0) { //front delete
        Node<K,V>* n = new Node<K,V>(key,val); 
        n = ordered_by_vals_head_;
        ordered_by_vals_head_ = ordered_by_vals_head_ -> next;
        delete n;
    }
        //////////////////////Middle Case Keys//////////////
    if(pos < sz_-1) {//middle delete //may just be size.
        Node<K,V>* pre = new Node<K,V>(key,val);
        Node<K,V>* cur = new Node<K,V>(key,val); 
        cur = ordered_by_vals_head_;
        for(unsigned int i=0; i<pos;i++) {
            pre=cur;
            cur =cur->next;
        }
        pre->next = cur->next;
    }
        ////////////////Back Case Keys////////////
    if(pos == sz_ -1) { //back delete
        Node<K,V>* cur = new Node<K,V>(key,val);
        Node<K,V>* prev = new Node<K,V>(key,val); 
        cur = ordered_by_vals_head_;
        while (cur->next!=nullptr) {
            prev = cur;
            cur = cur->next;
        }
        ordered_by_vals_tail_ = prev;
        prev->next = nullptr;
        delete cur;
    }  
    if(test == 1) { //if we did find a key to remove, then reduce the size by 1.
        sz_-=1;
    }          
    return val; //empty string if not found.
}


template<typename K, typename V>
K BiMap<K,V>::remove_val(V val) { //same thing as function above, except it removes val and returns a key. Same functionality.
    K key = K();
    int test = 0;
    unsigned int pos = 0;
    for(auto ptr = ordered_by_keys_head_; ptr != nullptr; ptr = ptr -> next) {
        if(val == ptr->second) {
            test = 1;
            key = ptr->first;
            break;
        }
        pos++;
    }

    ///////////////deletes cases///
    if(pos == 0) { //front delete
        Node<K,V>* n = new Node<K,V>(key,val); 
        n = ordered_by_keys_head_;
        ordered_by_keys_head_ = ordered_by_keys_head_ -> next;
        delete n;
    }
        //////////////////////Middle Case Keys//////////////
    if(pos < sz_-1) {//middle delete //may just be size.
        Node<K,V>* pre = new Node<K,V>(key,val);
        Node<K,V>* cur = new Node<K,V>(key,val); 
        cur = ordered_by_keys_head_;
        for(int i=0; i<pos;i++) {
            pre=cur;
            cur =cur->next;
        }
        pre->next = cur->next;

    }
        ////////////////Back Case Keys////////////
    if(pos == sz_ -1) { //back delete
        Node<K,V>* cur = new Node<K,V>(key,val);
        Node<K,V>* prev = new Node<K,V>(key,val); 
        cur = ordered_by_keys_head_;
        while (cur->next!=nullptr) {
            prev = cur;
            cur = cur->next;
        }
        ordered_by_keys_tail_ = prev;
        prev->next = nullptr;
        delete cur;
    }   
/////////////////////////////////////VALS BELOW/////////////////////////////////////////////
    pos = 0;
    for(auto ptr = ordered_by_vals_head_; ptr != nullptr; ptr = ptr -> next) {
        if(val == ptr->second) {
            key = ptr->first;
            break;
        }
        pos++;
    }

    ///////////////deletes cases///
    if(pos == 0) { //front delete
        Node<K,V>* n = new Node<K,V>(key,val); 
        n = ordered_by_vals_head_;
        ordered_by_vals_head_ = ordered_by_vals_head_ -> next;
        delete n;
    }
        //////////////////////Middle Case Keys//////////////
    if(pos < sz_-1) {//middle delete //may just be size.
        Node<K,V>* pre = new Node<K,V>(key,val);
        Node<K,V>* cur = new Node<K,V>(key,val); 
        cur = ordered_by_vals_head_;
        for(int i=0; i<pos;i++) {
            pre=cur;
            cur =cur->next;
        }
        pre->next = cur->next;
    }
        ////////////////Back Case Keys////////////
    if(pos == sz_ -1) { //back delete
        Node<K,V>* cur = new Node<K,V>(key,val);
        Node<K,V>* prev = new Node<K,V>(key,val); 
        cur = ordered_by_vals_head_;
        while (cur->next!=nullptr) {
            prev = cur;
            cur = cur->next;
        }
        ordered_by_vals_tail_ = prev;
        prev->next = nullptr;
        delete cur;
    } 

    if(test == 1) {
        sz_-=1;
    }           
    return key; //empty string if not found.
}



template<typename K, typename V>
int BiMap<K,V>::compare(BiMap<K,V> &bm) { //so i guess mismatch doesn't work for linked lists
    auto ptr2 = bm.ordered_by_keys_head_; //this will be updated in our for loop
    for(auto ptr = ordered_by_keys_head_; ptr != nullptr; ptr = ptr -> next) { //so this happens first. Previous projects I had this second.
        if(ptr2 == nullptr) { //if ptr2 does reach end, then break, otherwise segfault.
            break;
        }
        if(ptr->first > ptr2->first) { //if this is bigger then comparison obj, then return 1
            return 1;
        }
        else if (ptr->first < ptr2->first){ //else return -1
            return -1;
        }
        ptr2 = ptr2 -> next;
    }
    if(sz_ > bm.sz_) { //if size is bigger then object comparison size
        return 1;
    }
    else if(sz_ < bm.sz_) {
        return -1;
    }
    else { //if they are exact, then return 0.
        return 0;
    }
}

template<typename K, typename V>
BiMap<K,V> BiMap<K,V>::merge(BiMap& bm) { //just creates a bimap obj and adds every orderbykeys from the two bimap objs we are merging.
    BiMap<K,V> res;
    for(auto ptr = ordered_by_keys_head_; ptr != nullptr; ptr = ptr -> next) {
        res.add(ptr->first, ptr->second);
        
        }
    for(auto ptr = bm.ordered_by_keys_head_; ptr != nullptr; ptr = ptr -> next) {
        res.add(ptr->first, ptr->second); 
    }
    
    return res; //returns new bimap
}
