#pragma once
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
using std::string;
using std::cout;
using std::cin;
using std::ifstream;
using std::vector;

// the type that you must provide
class Painter {

public:
  // You must porovide these functions with exactly this signature
  // Painter Constructor
  Painter(const std::string &fname);
  
  // this function parses the file, draws the canvas, and logs errors
  void CreateCanvas();

  std::vector<std::string> GetCanvas() const {
    // return the canvas
    /*
    for(auto i = canvas_.begin(); i != canvas_.end(); i++) {
      cout << ",";
      cout << *i;
    }
    */
    return canvas_;
  }

  std::vector<std::string> GetErrorLog() const {
    // return the error log
    /*
    for(auto i = error_log_.begin(); i != error_log_.end(); i++) {
      cout << *i;
    }    
    */
    return error_log_;
  }

private:
  // the private stuff that we won't be testing directly
  // All of these are optional, but are guides to how you can build the class

  // directions (can be represented by ints, but an enum class is cleaner)
  enum class direction { up, down, left, right };
  // store the direction
  direction dir_  = direction::right;

  // number of rows in the canvas
  int rows_ {10};

  // number of columns in the canvas
  int columns_{10};

  // the current pen_symbol
  char pen_symbol_{'#'};

  // pen position can be represented by a pair or 2 different ints, etc
  std::pair<int,int> pen_position_{0,0};

  // the actual canvas vector<string>(rows, columns);
  std::vector<std::string> canvas_ = std::vector<std::string>(rows_,std::string(columns_,' '));

  // the error log
  std::vector<std::string> error_log_;

  // the lines of the .pf file (with line numbers). A vector of strings, where
  // the position represents the line number is also reasonable
  std::map<int, std::string> lines_;

  // These are functions that you will probably find useful to write
  // Note that these functions are up to you; change the names, signature, etc.
  // add functions if you want, of course
  // Whatever works for you

  // Parse a single line. (A good place to record a line error to the log
  // void Parse(int line_num,const std::string& line);

  // reset the dimensions of the canvas
  void SetDim(int line_num, int x_dim, int y_dim);

  // Set the position of the pen
  void SetPenPosition(int line_num, int x_pos, int y_pos);

  // Set the pen symbol
  void SetPenSymbol(int line_num, int pen_symbol);

  // Draw the current symbol at the current position
  void Draw();

  // Move the pen in the direction it is facing n steps
  void Move(int n);

  // Turn the pen 90 degrees clockwise n times
  void Turn(int n);

  // Repeat a range of commands the specified number of times
  void Repeat(int line_num,int n, int start, int end);

};
