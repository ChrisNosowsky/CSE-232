#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;
#include<string>
using std::string; using std::to_string;
#include<algorithm>
using std::copy; using std::lower_bound;
#include<iterator>
using std::ostream_iterator;
#include<sstream>
using std::ostringstream;

// template on the vector type, more general purpose that way
// T type must be printable for this to work!
template<typename T>
string vector2string(vector<T> v){
  ostringstream oss;
  copy(v.begin(), v.end(), ostream_iterator<string>(oss, ","));
  string result = oss.str();
  // sloppy the comma at the end, get rid of it.
  return result.substr(0, result.size()-1);
}

	
