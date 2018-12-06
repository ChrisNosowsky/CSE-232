#include "proj08.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using std::string;
using std::cout;
using std::cin;
using std::ifstream;
using std::vector;
using std::to_string;
using std::stoi;
using std::endl;

Painter::Painter(const string &filname) { //opens filename, reads every line in file, maps to the lines_.

    ifstream myfile;
    myfile.open(filname);
    string line;
    int i = 1;
    while(getline(myfile,line)) {
      lines_[i] = line;
      i++;
    }
}

void Painter::CreateCanvas() { // finds the commands and calls the functions
  int ii = 1;
  for(auto i = lines_.begin(); i!=lines_.end(); ++i) { //for every key in the map
    string values = ""; //All initializers
    string value1 = "";
    string value2 = "";
    string value3 = "";
    string value4 = "";
    int pos = 0;
    int f_pos = 0;
    int l_pos = 0;
    if(lines_[ii].find("SetDim") == 0) { //prob could have just used i since i is the key
      pos = lines_[ii].find("SetDim"); //dont really need i dont think
      values = lines_[ii].substr(pos+7); //adjust for each if statement
      f_pos = values.find(' ');
      value1 = values.substr(0, f_pos);
      value2 = values.substr(f_pos+1);
      SetDim(ii, stoi(value1), stoi(value2));
    }

    else if(lines_[ii].find("SetPenPosition") == 0) { //bunch of substrings
      pos = lines_[ii].find("SetPenPosition");
      values = lines_[ii].substr(pos+15); //15 because of setpenposition size + whitespace to get vals
      f_pos = values.find(' '); 
      value1 = values.substr(0, f_pos);
      value2 = values.substr(f_pos+1); 
      SetPenPosition(ii, stoi(value1), stoi(value2));
    }
    else if(lines_[ii].find("SetPenSymbol") == 0) { //finds the command
      pos = lines_[ii].find("SetPenSymbol");
      values = lines_[ii].substr(pos+13);
      SetPenSymbol(ii, stoi(values)); //takes the value and converts from string to integer
    }
    else if(lines_[ii].find("Draw") == 0) { //find the command for draw
      pos = lines_[ii].find("Draw");
      Draw();
    }
    else if(lines_[ii].find("Move") == 0) { //find the command move
      pos = lines_[ii].find("Move"); //didnt really need this i don't think since it will always be 0.
      values = lines_[ii].substr(pos+5);
      Move(stoi(values));
    }
    else if(lines_[ii].find("Turn") == 0) {
      pos = lines_[ii].find("Turn");
      values = lines_[ii].substr(pos+5);
      Turn(stoi(values));      
    }
    else if(lines_[ii].find("Repeat") == 0) {
      values = lines_[ii].substr(pos+7);
      f_pos = values.find(' ');
      value1 = values.substr(0, f_pos);
      value2 = values.substr(f_pos+1); //#-#
      l_pos = value2.find('-');
      value3 = value2.substr(0,l_pos);
      value4 = value2.substr(l_pos+1);
      Repeat(ii, stoi(value1), stoi(value3), stoi(value4));     
    }
    else { //else if none of the commands are found
      if((lines_[ii].find("#") != 0) && (lines_[ii].empty() == false)) { //if it's not a hashtag in beginning and the line isn't empty, then error it.
        error_log_.push_back("error on line " + to_string(ii) + ": unable to parse \"" + lines_[ii] + "\"");
      }
    }
    ii++; //after testing to see if we find every special word in the line, go to next line num.
  }
}

void Painter::SetDim(int linen, int xd, int yd) {
  if((xd >= 10 && xd <= 80) && (yd >= 10 && yd <= 80)) { //if  the row and columns are greater then 10 but less then 80.
    rows_ = {xd}; 
    columns_ = {yd};
    canvas_ = std::vector<std::string>(rows_,std::string(columns_,' ')); //updates the canvas 
  }
  else { //error log here
    if(xd <= 10 || xd >= 80) { //if it's out of bounds for the rows
      error_log_.push_back("error on line " + to_string(linen) + ": Row Dimension out of bounds");
    }
    else { //if its out of bounds for the columns
      error_log_.push_back("error on line " + to_string(linen) + ": Column Dimension out of bounds");
    }
  }
}

void Painter::SetPenPosition(int linen, int xd, int yd) {
  if((xd >= 0 && yd >= 0) && (xd <= rows_ && yd <= columns_)) {
    pen_position_.first = xd; //first being the x
    pen_position_.second = yd; //second being the y
  }
  else { //error log here
    error_log_.push_back("error on line " + to_string(linen) + ": Pen cannot be placed on canvas at position " + to_string(xd) + " " + to_string(yd));
  }
}

void Painter::SetPenSymbol(int linen, int symb) {
  char c;
  if(symb >= 32 && symb <= 126) {
    c = symb; //converting int to char;
    pen_symbol_ = c;
  }
  else { //error log here
    error_log_.push_back("error on line " + to_string(linen) + ": Invalid Pen Symbol " + to_string(symb));
  }
}

void Painter::Draw() {
  canvas_[pen_position_.first][pen_position_.second] = pen_symbol_; //canvas[row][col]
}

void Painter::Move(int n) {
  
  if(dir_ == direction::right) { //if the direction is right, move the y(col) + move count
    pen_position_.second += n;
  }

  else if(dir_ == direction::left) { //if the direction is left, move the y(col) + move count
    pen_position_.second -= n;
  }

  else if(dir_ == direction::up) { //if the direction up, move the x(row) + move count
    pen_position_.first -= n;
  }

  else if(dir_ == direction::down) { //if the direction down, move the x(row) + move count
    pen_position_.first += n;
  }

  if (pen_position_.second == columns_) { 
    pen_position_.second = 0;
  }

}

void Painter::Turn(int n) {
  if(n % 4 == 1) { //90 degree turn 
    if(dir_ == direction::right) {
      dir_ = direction::down;
    }
    else if(dir_ == direction::left) {
      dir_ = direction::up;
    }
    else if(dir_ == direction::up) {
      dir_ = direction::right;
    }
    else if(dir_ == direction::down) {
      dir_ = direction::left;
    }
  }
  if(n% 4 == 2) { //180 degree turn
    if(dir_ == direction::right) {
      dir_ = direction::left;
    }
    else if(dir_ == direction::left) {
      dir_ = direction::right;
    }
    else if(dir_ == direction::up) {
      dir_ = direction::down;
    }
    else if(dir_ == direction::down) {
      dir_ = direction::up;
    }
  }
  if(n % 4 == 3) { //270 degree turn
    if(dir_ == direction::right) {
      dir_ = direction::up;
    }
    else if(dir_ == direction::left) {
      dir_ = direction::down;
    }
    else if(dir_ == direction::up) {
      dir_ = direction::left;
    }
    else if(dir_ == direction::down) {
      dir_ = direction::right;
    }
  }
}


void Painter::Repeat(int linen, int n, int b, int e) {
  int test1 = 0;
  int test2 = 0;
  for (auto it = lines_.begin(); it != lines_.end(); ++it) {
    if(it->first == b) { //these two if statements test to see if the lines exist
      test1 = 1; //just a tester for the next if statement
    }
    if(it->first == e) {
      test2 = 1;
    }
  }
  if((b < e) && (test1 ==1 && test2 == 1) && (linen < b)) { //if it passes all the tests
    for (int p = 0; p < n; p++) { //how many times to repeat for loop
      for(int i = b; i <= e; i++) { //how many lines to go through. Pretty much runs the through the commands again
            string values = "";
            string value1 = "";
            string value2 = "";
            string value3 = "";
            string value4 = "";
            int pos = 0;
            int f_pos = 0;
            int l_pos = 0;
            if(lines_[i].find("Draw") == 0) {
              pos = lines_[i].find("Draw");
              Draw();
            }
            else if(lines_[i].find("Move") == 0) {
              pos = lines_[i].find("Move");
              values = lines_[i].substr(pos+5);
              Move(stoi(values));
            }
            else if(lines_[i].find("Turn") == 0) {
              pos = lines_[i].find("Turn");
              values = lines_[i].substr(pos+5);
              Turn(stoi(values));      
            }
            else if(lines_[i].find("Repeat") == 0) {
              values = lines_[i].substr(pos+7);
              f_pos = values.find(' ');
              value1 = values.substr(0, f_pos);
              value2 = values.substr(f_pos+1); //#-#
              l_pos = value2.find('-');
              value3 = value2.substr(0,l_pos);
              value4 = value2.substr(l_pos+1);
              Repeat(i, stoi(value1), stoi(value3), stoi(value4));     
            }
      }
    }
  }
  else { //else if it doesn't pass all the error conditions, then append the errors to the error log
    if(b > e) { //if the b is greater then e, then thats backwards and not ascending
      error_log_.push_back("error on line " + to_string(linen) + ": Repeat range must be ascending");
    }
    if(test1 == 0) { //if the b wasn't found
      error_log_.push_back("error on line " + to_string(linen) + ": Line " + to_string(b) + " is not in the file");
    }
    if(test2 == 0) { //if the e wasn't found
      error_log_.push_back("error on line " + to_string(linen) + ": Line " + to_string(e) + " is not in the file");
    }
    if (linen > b) { //if the repeat command is greater then b, infinite loop??
      error_log_.push_back("error on line " + to_string(linen) + ": Repeat command contains itself or refers to previous commands; infinite loop!");
    }
  }
}
/*
int main(int, char**args) {
  
  Painter painter("test73.pf");
  painter.CreateCanvas();
  painter.GetCanvas();
  painter.GetErrorLog();

  Painter painter(args[1]);
  painter.CreateCanvas();

  auto result = painter.GetErrorLog().empty() ? 
                painter.GetCanvas() :
                painter.GetErrorLog();

  for (auto &line : result) 
    std::cout << line << "\n";
}
*/



