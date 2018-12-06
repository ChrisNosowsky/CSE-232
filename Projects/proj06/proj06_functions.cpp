#include<vector>
using std::vector;
#include<string>
using std::string;
#include "proj06_functions.h"
#include <iomanip>
#include <sstream>
#include <fstream>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <cmath>
#include <math.h>
using std::cout;
using std::cin;
using std::runtime_error;
using std::ifstream;
using std::to_string;

vector<vector<int>> read_file (const string &fname) { //reads file to make sure requested file exists. Also converts all chars to ints and appends to a vector int
    vector<int> row;
    vector<vector<int>> result;
    string line;
    ifstream myfile; //decalres myfile stream
    myfile.open(fname); //open file name
    if (myfile.is_open()) {
        while (getline(myfile,line)) { //while a line exists in myfile
            int lsize = line.size();
            for (int i = 0; i < lsize; i++) {
                if(line[i] != ' ') { //checks for spaces
                    int digit = line[i] - 48; //used 48 since it's 0 in ascii
                    row.push_back(digit);
                }
            }
            if (row.size() > 0) {
                result.push_back(row); //appends the vector row to the vector result
            }
            row.clear(); //clears row vector so it resets vector to empty for each row
        }
        myfile.close(); //close file
    }
    else {
        throw runtime_error(""); //throws error if file cannot open.
    }
    return result;
}

vector<int> get_row(const vector<vector<int>> &v, int row) {
    vector<int> result;
    for (auto val : v[row]) { //for every val in the argument row, get the val's for the row and return it
        result.push_back(val);
    }
    return result;
}

vector<int> get_column(const vector<vector<int>> &v, int col) {
    vector<int> result;
    int c = 0;
    for(auto row : v) { //for every row, get the argument column
        result.push_back(v[c][col]); //c is the row index
        c += 1;
    }
    return result;
}

int col_to_int(const vector<vector<int>> &v, size_t col) {
    int cols = col;
    vector<int> columns = get_column(v, cols);
    int col_size = columns.size() -2; //set this to 6 because this is the largest deci value(2^6 = 64) 
    int tester = 0;
    int result = 0;
    for(auto val : columns) {
        if(tester == 0) { //this is just so it skips the first element
            tester = 1;
        }
        else { //if not first element
            if (val != 0) { //if the val is 1, then that means we can count it towards the decimal sum
                result += pow (2, col_size); // 2^6, 2^5, 2^4,...
                col_size -= 1;
            }
            else {
                col_size -= 1;
            }
        }
    }
    return result;
}

string get_time(const vector<vector<int>> &v) { //Wanted to use printf for this for the formatting, but mimir wasn't passing.
    int minute = col_to_int(v,1);
    int hour = col_to_int(v,4);
    string result = "";
    string minute_s = "";
    string hour_s = "";
    if (minute < 10) { //testing for single digit. If single, add 0 in front. Otherwise, just convert to string.
        minute_s = "0" + to_string(minute);
    }
    else {
        minute_s = to_string(minute);
    }
    if(hour < 10) {
        hour_s = "0" + to_string(hour);
    }
    else {
        hour_s = to_string(hour);
    }
    result = hour_s + ":" + minute_s;
    return result;
}

string get_date(const vector<vector<int>> &v) { //Wanted to use printf for this for the formatting, but mimir wasn't passing.
    int day = col_to_int(v,5);
    int month = col_to_int(v,6);
    int year = col_to_int(v,7);
    string month_s = "";
    string day_s = "";
    string result = "";
    string year_s = "";
    if(month < 10) { //if single digit, then convert to string with 0 in front
        month_s = "0" + to_string(month);
    }
    else { //if double digit, just convert to string
        month_s = to_string(month);
    }
    if(day < 10) {
        day_s = "0" + to_string(day);
    }
    else{
        day_s = to_string(day);
    }
    if(year < 10) {
        year_s = "0" + to_string(year);
    }
    else {
        year_s = to_string(year);
    }
    result = month_s + "/" + day_s + "/" + "20" + year_s; //adds all the strings togther in the correct format.
    return result;
}

string get_serial(const vector<vector<int>> &v) {
    int four = col_to_int(v,10); //gets the values of all the serial number pairs
    int three = col_to_int(v,11);
    int two = col_to_int(v,12);
    int one = col_to_int(v,13);
    string result = "";
    string one_s = "";
    string two_s = "";
    string three_s = "";
    string four_s = "";
    if(one < 10) { //if single digit, add 0 in front and convert to string.
        one_s = "0" + to_string(one);
    }
    else {
        one_s = to_string(one);
    }
    if(two < 10) { //same as above
        two_s = "0" + to_string(two);
    }
    else {
        two_s = to_string(two);
    }
    if(three < 10) {
        three_s = "0" + to_string(three);
    }
    else {
        three_s = to_string(three);
    }
    if(four < 10) {
        four_s = "0" + to_string(four);
    }
    else {
        four_s = to_string(four);
    }
    result = one_s + two_s + three_s + four_s;
    return result;
}
string check_column_parity(const vector<vector<int>> &v, int col) {
    vector<int> col_bits = get_column(v,col);
    int tester = 0;
    int count = 0;
    int parity = 0;
    string tf = "";
    string result = "";
    for (auto val : col_bits) { //for every value in the column, we are testing to see if the val is one or zero
        if(tester == 0) { //tester only used to skip first line since that's the parity column. We ignore that.
            tester = 1;
        }
        else {
            if(val == 1) { //if the bit is 1, increase count. Count is the total 1's.
                count += 1;
            }
        }
    }
    if(count % 2 == 0) { //Checks to see if the total 1's count is even or odd. If even, set the parity value to 1. Otherwise, parity 0 for odd
        parity = 1;
    }
    else {
        parity = 0;
    }
    if ((count % 2 == 0 && parity == 1) || (count % 2 != 0 && parity == 0)) { //if the count is even and parity is one(it should be) the bool value will be true.
        tf = "true"; //this would always happen?
    }
    else {
        tf = "false";
    }
    result = to_string(parity) + ":" + to_string(count) + ":" + tf; //format return
    return result;
}

string check_row_parity(const vector<vector<int>> &v, int row) { //this works exactly like the check_column_parity
    vector<int> row_bits = get_row(v,row); //this is pretty much the only difference in this function compared to the check_column one
    int tester = 0;
    int count = 0;
    int parity = 0;
    string result = "";
    string tf = "";
    for (auto val : row_bits) {
        if(tester == 0) {
            tester = 1;
        }
        else {
            if(val == 1) {
                count += 1;
            }
        }
    }
    if(count % 2 == 0) {
        parity = 1;
    }
    else {
        parity = 0;
    }
    if ((count % 2 == 0 && parity == 1) || (count % 2 != 0 && parity == 0)) {
        tf = "true";
    }
    else {
        tf = "false";
    }
    result = to_string(parity) + ":" + to_string(count) + ":" + tf;
    return result;
}
