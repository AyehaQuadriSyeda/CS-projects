/*
 * File name : barchart.h
 * Purpose ; Declare and define the BarChart class
 * Author: Ayesha Quadri Syeda
 * Due Date: 7/10/2022
 */

#include "bar.h"
#include "myrandom.h" // used in autograder, do not remove
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

// Constants used for bar chart animation.  You will primarily
// use these in barchartanimate.h, but you might find some useful here.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";

// Color codes for Mimir (light mode)
const string RED("\033[1;36m");
const string PURPLE("\033[1;32m");
const string BLUE("\033[1;33m");
const string CYAN("\033[1;31m");
const string GREEN("\033[1;35m");
const string GOLD("\033[1;34m");
const string BLACK("\033[1;37m");
const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

// Color codes for Replit (dark mode terminal)
/*const string CYAN("\033[1;36m");
const string GREEN("\033[1;32m");
const string GOLD("\033[1;33m");
const string RED("\033[1;31m");
const string PURPLE("\033[1;35m");
const string BLUE("\033[1;34m");
const string WHITE("\033[1;37m");
const string RESET("\033[0m");
const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE};
*/
// BarChart
//
class BarChart {
private:
  //
  // Private member variables for the abstraction.
  // This implementation uses a low-level C array, bars, to store a list of
  // Bars.  As a result, you must also keep track of the number of elements
  // stored (size) and the capacity of the array (capacity).  This is not a
  // dynamic array, so it does not expand.
  //
  Bar *bars; // pointer to a C-style array
  int capacity;
  int size;
  string frame;

public:
  // default constructor:
  BarChart() {
    this->capacity = 0;
    this->size = 0;
    this->frame = "";
    bars = nullptr;
  }

  // parameterized constructor:
  // Parameter passed in determines memory allocated for bars.
  BarChart(int n) {
    this->capacity = n;
    this->size = 0;
    bars = new Bar[capacity];
    this->frame = "";
  }

  //
  // copy constructor:
  //
  // Called automatically by C++ to create an BarChart that contains
  // a copy of an existing BarChart.  Example: this occurs when passing
  // BarChart as a parameter by value.
  //
  BarChart(const BarChart &other) {

    // assign the appropriate private variables
    this->bars = new Bar[other.capacity];
    this->capacity = other.capacity;
    this->size = other.size;
    this->frame = other.frame;

    // copy array elements
    for (int i = 0; i < other.size; i++) {
      this->bars[i] = other.bars[i];
    }
  }
  //
  // copy operator=
  //
  // Called when you assign one BarChart into another, i.e. this = other;
  //
  BarChart &operator=(const BarChart &other) {
    if (this == &other)
      return *this;

    // delete the previous memory
    delete[] bars;

    // assign the appropriate private variables
    this->bars = new Bar[other.capacity];
    this->capacity = other.capacity;
    this->size = other.size;
    this->frame = other.frame;

    // copy array elements
    for (int i = 0; i < other.size; i++) {
      this->bars[i] = other.bars[i];
    }
    return *this;
  }

  // clear
  // frees memory and resets all private member variables to default values.
  void clear() {
    delete[] bars;
    bars = nullptr;
    size = 0;
    capacity = 0;
    frame = "";
  }

  //
  // destructor:
  //
  // Called automatically by C++ to free the memory associated by the
  // BarChart.
  //
  virtual ~BarChart() { delete[] bars; }

  // setFrame
  void setFrame(string frame) { this->frame = frame; }

  // getFrame()
  // Returns the frame of the BarChart oboject.
  string getFrame() { return frame; }

  // addBar
  // adds a Bar to the BarChart.
  // returns true if successful
  // returns false if there is not room
  bool addBar(string name, int value, string category) {
    // check for capacity
    if (size == capacity) {
      return false;
    }

    // add the bar
    Bar b(name, value, category);
    bars[this->size] = b;
    this->size++;
    return true;
  }

  // getSize()
  // Returns the size (number of bars) of the BarChart object.
  int getSize() { return this->size; }

  // operator[]
  // Returns Bar element in BarChart.
  // This gives public access to Bars stored in the Barchart.
  // If i is out of bounds, throw an out_of_range error message:
  // "BarChart: i out of bounds"
  Bar &operator[](int i) {
    if (i >= size || i < 0) {
      throw out_of_range("BarChart: i out of bounds");
    }
    return bars[i];
  }

  // dump
  // Used for printing the BarChart object.
  // Recommended for debugging purposes.  output is any stream (cout,
  // file stream, or string stream).
  // Format:
  // "frame: 1
  // aname 5 category1
  // bname 4 category2
  // cname 3 category3" <-newline here
  void dump(ostream &output) {

    // output frame
    output << "frame: " << frame << endl;

    // int n = sizeof(*bars)/sizeof(bars[0]);
    sort(bars, bars + size, greater<Bar>());

    // output the bars array
    for (int i = 0; i < size; i++) {
      output << bars[i].getName() << " ";
      output << bars[i].getValue() << " ";
      output << bars[i].getCategory() << endl;
    }
  }

  // graph
  // Used for printing out the bar.
  // output is any stream (cout, file stream, string stream)
  // colorMap maps category -> color
  // top is number of bars you'd like plotted on each frame (top 10? top 12?)
  void graph(ostream &output, map<string, string> &colorMap, int top) {
    int lenMax = 60; // this is number of BOXs that should be printed for the
                     // top bar (max value)
    sort(bars, bars + size, greater<Bar>());

    // iterate through the array
    for (int i = 0; i < top; i++) {
      int count = 0;
      string barstr = "";

      // calculate proportionality to the top bar if not max value
      lenMax =
          int(double(bars[i].getValue()) / (bars[0].getValue() * 1.0) * 60);
      // add the BOX to barstr
      for (int j = 0; j < lenMax; j++) {
        barstr += BOX;
      }

      // if the colorMap is empty
      if (colorMap.empty()) {
        output << BLACK << barstr << " " << bars[i].getName();
        output << " " << bars[i].getValue() << endl;
      } else {
        // iterate through the map to find a category or else print in BLACK
        for (auto &a : colorMap) {
          if (a.first == bars[i].getCategory()) {
            output << a.second << barstr << " " << bars[i].getName();
            output << " " << bars[i].getValue() << endl;
            count++;
          }
        }
        if (count == 0) {
          output << BLACK << barstr << " " << bars[i].getName();
          output << " " << bars[i].getValue() << endl;
        }
        count = 0;
      }
    }
  }
};
