#include<iostream>
using std::cout; using std::cin; using std::endl;
#include<iomanip>
using std::setprecision;
#include<string>
using std::string;
// any other includes you think you might need here

// global variable for count -> char code
const string code = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

//
// your functions here
//
string encode_sequence(string seq, char nchar) { //takes a string sequence and encodes it using run-length encoding with the given character
    int num = seq.size();
    int start = 4; //start. Increments in loop until the constant string code letter matches the sequence letter
    int csize = code.size();
    string result = "";
    if (num < 4) {
        return seq;
    }
    else {
        for (int i = 0; i < csize; i++) {
            if (num == start) { //if the sequence size is equal to the number associated with the letter. For example, if the size of sequence is 4 and it equals the start num of 4, then it gets a.
                result += nchar; //appends all the strings to make one large string of the run-length string
                result += code[i];
                result += seq[0];
                break;
            }
            else {
                start += 1;
            }
        }
    }
    return result;
}

string encode (string encode, char nchar) { //encodes a whole string and reduces it down into the run-length encoding
    int esize = encode.size();
    string ecode = "";
    string result = "";
    int len = 1;
    int m = 0;
    for (int i = 0; i < esize; i++) {
        if (encode[i] == encode[i+1]) {
            len += 1;
        }
        else {
            ecode = encode_sequence(encode.substr(m,len), nchar);
            result += ecode;
            m = i+1;
            len = 1;
        }
    }
    return result;
}

string decode_sequence (string decode, char nchar) { //takes a sequence and decodes it to its original form.
    int csize = code.size();
    int s = 4;
    string result = "";
    for(int i = 0; i < csize; i++) {
        if (decode[1] == code[i]) {
            break;
        }
        else {
            s += 1;
        }
    }
    for (int n = 0; n < s; n++) {
        result += decode[2];
    }
    return result;
}

string decode(string decode, char nchar) { //decodes the entire string
    int dsize = decode.size();
    string d = ""; //placeholder
    for (int i = 0; i < dsize; i++) {
        if (decode[i] == nchar) {
           d += decode_sequence(decode.substr(i,3), nchar); //if the string at that index matches the special char we are looking for, then take the 3 character substring and run a decode sequence on it.
           i += 2;
        }
        else { //if the special character isnt found at every 3rd character
            d += decode[i];
        }
    }
    return d;
}

double reduction (string original, string encode) { //gives a ratio to how much we reduced the file size down too.
    double osize = original.size();
    double esize = encode.size();
    double result = esize/osize;
    return result;
}



int main (){
  long test_num;
  cin >> test_num;

  switch(test_num) {

  case 1: {
    string input;
    char sep;
    cin >> input;
    cin >> sep;
    cout << encode_sequence(input, sep);
    break;
  }

  case 2:{
    string input;
    char sep;
    cin >> input;
    cin >> sep;
    cout << encode(input, sep);
    break;
  }

  case 3:{
    string input;
    char sep;
    cin >> input;
    cin >> sep;
    cout << decode_sequence(input, sep);
    break;
  }

  case 4:{
    string input;
    char sep;
    cin >> input;
    cin >> sep;
    cout << decode(input, sep);
    break;
  }

  case 5:{
    string s1,s2;
    cin >> s1;
    cin >> s2;
    cout << setprecision(2);
    cout << reduction(s1,s2);
    break;
  }
    
  } // of switch
}  // of main
