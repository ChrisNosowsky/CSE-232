#include <iostream>
#include<string>
using std::cout;using std::endl;using std::cin;
using std::string;
using std::tolower;
#include "proj05_functions.h" //import the header

string prepare_plaintext(const string &s) {
    string n_s = s; //new string is set to s for now. Will be modified in the for loop.
    string u_s = "";
    long n = n_s.size();
    for (int i = 0; i < n; i++) { //for every letter in the string we want to put to plaintext
        if (n_s[i] == n_s[i+1]) { //only way if this wouldn't work is if we had something like hellxo
            n_s[i+1] = 'x'; //says that if double letters, then add x
        }
        if ((isalpha(n_s[i])) && (tolower(n_s[i]) != 'j')) { //if the letter is in the alphabet and not j then lets append it to our plaintext string
            u_s.push_back(tolower(n_s[i]));
        }
    }
    if (u_s.size() % 2 != 0) { //tests for odd. If it's not even, then add x to the end to make it even.
        u_s.push_back('x');
    }
    return u_s;
}
const string LETTERS = "abcdefghiklmnopqrstuvwxyz";
string create_encoding(const string &key) {
    long key_len = key.size();
    string u_s =  "";
    long u_s_len = u_s.size();
    long letters_size = LETTERS.size();
    long test = 0; //placeholder.
    for(int i = 0; i < key_len; i++) { //for every letter in the key
        test = 0;
        u_s_len = u_s.size();
        for(int c=0; c<u_s_len; c++) { //this looks through every letter in the new string and checks to see if its equal to the current key char we are looking at. If not equal to anything in the new string, then we can add it. This is to make sure it doesn't add duplicate letters to the key square.
            if(u_s[c] == key[i]) {
                test = 1; //if they do happen to be equal, then the next if statement won't run, which is the statement that adds the letter to our new string.
            }
        }
        if (test == 0) {
            u_s.push_back(key[i]);
        }
    }
    test = 0; //at this point in the code, I have converted the first part of the key to key square form(e.g. desperate is desprat)
    for(int i = 0; i < letters_size; i++) { //this for loop goes through the alphabet exluding j.
        test = 0;
        u_s_len = u_s.size();
        for(int c=0; c<u_s_len; c++) { //this loops through our new string and checks to see if any letters are missing from the alphabet. If so, then append them to the end.
            if (u_s[c] == LETTERS[i]) {
                test = 1;
            }
        }
        if (test == 0) {
            u_s.push_back(LETTERS[i]);
        }
    }
    return u_s;
}



string encode_pair(const string &pr, const string &key) {
    long index_1 = key.find(pr[0]); //These are the basic calculations I need for the function
    long index_2 = key.find(pr[1]);
    long row1 = index_1/5;
    long col1 = index_1 % 5;
    long row2 = index_2/5;
    long col2 = index_2 % 5;
    long n_index1 = 0;
    long n_index2 = 0;
    string result = "";
    string result2 = "";
    string result3 = ""; 
    if(col1 == col2) { //this one tests for same column
        if(row1 == 4) { //if the first index row is 4(last row), then minus 20 to get to top row.
            n_index1 = index_1-20;
        }
        else { //if not row 4, then just add 5 to get to row below
            n_index1 = index_1 + 5;
        }
        if(row2 == 4) { //same as above but testing the second index in the pair now.
            n_index2 = index_2-20;
        }
        else {
            n_index2 = index_2 + 5;
        }
    }
    if(row1 == row2) { //this one tests for same row!
        if(col1 == 4) { //if the first pair index is at column 4, just subtract 4 to get to the first column.
            n_index1 = index_1-4;
        }
        else {
            n_index1 = index_1 + 1; //if not at column 1, then just add 1 to get to the next column over.
        }
        if(col2 == 4) { //same as above byt testing for second pair index
            n_index2 = index_2-4;
        }
        else {
            n_index2 = index_2 + 1;
        }
    }
    if((row1 != row2) && (col1 != col2)) { //this one tests if not same row and col
        long coldif = col1 - col2;
        if(coldif < 0) { //if less than 0 then col1 is more left
            n_index1 = index_1 + (col2 - col1); //col 1 is first pair column, we will add to get to the correct corner. Subtract the difference between the columns to get the distance between two.
            n_index2 = index_2 - (col2 - col1);  // this subtracts from the column difference because this is more right and we need to go more left to get to the correct corner.
        }
        else { //else col1 is more right
            n_index1 = index_1 - (col1 - col2); //this does the exact same thing as above, but reversed.
            n_index2 = index_2 + (col1 - col2);
        }
    }

    result = key[n_index1]; 
    result2 = key[n_index2];
    result3 = result + result2;//this adds the keys together to make the pair encoded.
    return result3;
}



string encode(const string &plaintxt, const string &key) {
    string prepared = prepare_plaintext(plaintxt);
    long pre_size = prepared.size();
    string en_pair = "";
    string result = "";
    for(int i = 0; i < pre_size; i+=2) { //just goes through the plaintext and encodes every 2 letters.
        en_pair = encode_pair(prepared.substr(i,i+2), key);
        result += en_pair;
    }
    return result;
}


string decode_pair(const string &pr, const string &key) { //this function works exactly like the encode_pair except everything is mirrored.
    long index_1 = key.find(pr[0]);
    long index_2 = key.find(pr[1]);
    long row1 = index_1/5;
    long col1 = index_1 % 5;
    long row2 = index_2/5;
    long col2 = index_2 % 5;
    long n_index1 = 0;
    long n_index2 = 0;
    string result = "";
    string result2 = "";
    string result3 = "";
    if(col1 == col2) { //this one tests for same column
        if(row1 == 0) {
            n_index1 = index_1+20;
        }
        else {
            n_index1 = index_1 - 5;
        }
        if(row2 == 0) {
            n_index2 = index_2+20;
        }
        else {
            n_index2 = index_2 - 5;
        }
    }
    if(row1 == row2) { //this one tests for same row!
        if(col1 == 0) {
            n_index1 = index_1+4;
        }
        else {
            n_index1 = index_1 - 1;
        }
        if(col2 == 0) {
            n_index2 = index_2+4;
        }
        else {
            n_index2 = index_2 - 1;
        }
    }
    if((row1 != row2) && (col1 != col2)) { //this one tests if not same row and col
        long coldif = col1 - col2;
        if(coldif < 0) { //if less than 0 then col1 is more left
            n_index1 = index_1 + (col2 - col1);
            n_index2 = index_2 - (col2 - col1); 
        }
        else { //else col1 is more right
            n_index1 = index_1 - (col1 - col2);
            n_index2 = index_2 + (col1 - col2);
        }
    }
    result = key[n_index1];
    result2 = key[n_index2];
    result3 = result + result2;
    return result3;    
}



string decode(const string &encodedtxt, const string &key) { //pretty similar to encode, except you are calling decode_pair instead.
    long e_size = encodedtxt.size();
    string d_pair = "";
    string result = "";
    for(int i = 0; i < e_size; i+=2) {
        d_pair = decode_pair(encodedtxt.substr(i,i+2), key);
        result += d_pair;
    }
    return result;
}
