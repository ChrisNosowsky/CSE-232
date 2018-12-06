#include <algorithm>
#include <fstream>
#include <set>
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::cin;
using std::set;
#include "proj07_functions.h"
#include <sstream>
#include <fstream>
using std::ifstream;
using std::tolower;
using std::swap;



void deletes (const string &word, set<string> &result) {
    int wsize = word.size();
    string a = word; //initializes a to be set to word
    for(int i=0; i < wsize; i++) {
        a = word; //after every loop, resets to the original
        a.erase(i,1); //erases at that index the character
        result.insert(a); //appends to result
    }
}

void replaces (const string &word, set<string> &result) {
    int wsize = word.size();
    const string alpha = "abcdefghijklmnopqrstuvwxyz";
    string a = word;
    int aa = alpha.size();
    char t;
    string s;
    for (int i = 0; i < wsize; i++) {
        a = word;
        for(int c =0; c< aa; c++) {
            a = word; //after every loop, resets to the original
            t = alpha[c]; 
            s = t; //converting char to string
            a.replace(i,1,s); //replace the letter at that index, every alphabet letter
            result.insert(a);
        }
    }
}

void transposes (const string &word, set<string> &result) {
    int wsize = word.size(); 
    string a = word;
    for (int i = 0; i < wsize-1; i++) {
        a = word; //resets back to original after every loop
        swap(a[i], a[i+1]); //used swap to swap the places and the next index
        result.insert(a);
    }
}
void inserts (const string &word, set<string> &result) {
    int wsize = word.size();
    const string alpha = "abcdefghijklmnopqrstuvwxyz"; //all letters in alphabet
    int aa = alpha.size();
    string a = word;
    for(int i = 0; i < wsize+1; i++) {
        a = word; //resets back to original after every loop
        for (int c = 0; c < aa; c++) {
            a = word;
            a = a.substr(0,i) + alpha[c] + a.substr(i); //insert all alphabets at every index
            result.insert(a);
        }
    }
}

void read_words (string fname, set<string> &result) {
    ifstream myfile;
    myfile.open(fname); //opens the file
    string line;
    string lline;
    while(getline(myfile, line)) { //every line in the file, while it exists
        lline = ""; //resets lline every loop
        for (auto c : line) { //for every character in the line
            if(isalpha(c)) { //if the character is a letter in the alphabet
                lline += tolower(c); //lowercase the character
            }
        }
        result.insert(lline);
    }
}

void find_completions (const string &w, const set<string> &word_list, set<string> &result) {
    for (auto word: word_list) { //for every word in the wordlist
        if (word.find(w) == 0) { //if the string is found at 0, meaning it is a pre-fix
            result.insert(word);
        }

    }
}


void find_corrections(const string &word, set<string> &result) { //goes through all the functions calculating possibilities
    deletes(word, result);
    replaces(word, result);
    transposes(word, result);
    inserts(word, result);
}



void find_2step_corrections(const string &word, set<string> &result) {
    set<string> second_result;
    set<string> first_result;
    find_corrections(word, first_result); //first run through the possibilities
    for(auto &element : first_result) { //for every element in first result
        find_corrections(element, second_result); //second level possibilities
        for (auto &element : second_result) { //goes through every element in the second level and appends to the result
            result.insert(element);
        }
        second_result.clear(); //clears the second_result set every loop to reduce amount of looping on the innner for loop. Speeds up function
    }
}

void find_reasonable_corrections(const set<string> &possibles, const set<string> &word_list, set<string> &result) { //dpn't understand why this isn't running in mimir??? I tested the set and it prints out the correct words every time, but mimir says nothing outputs?!?    
    for (auto word: possibles) { //for every word in possibilities
        for(auto wordd : word_list) { //for every word in word_list
            if((wordd.find(word) == 0) && (word.find(wordd) == 0)) { 
                result.insert(wordd);
            }
        }    
    }
}

