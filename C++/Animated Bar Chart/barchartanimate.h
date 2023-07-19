/*
 * File name : barchartanimate.h
 * Purpose ; Declare and define the BarChartAnimate class
 * Author: Ayesha Quadri Syeda
 * Due Date: 7/10/2022
 */

#include "barchart.h"
#include "myrandom.h" // used in autograder, do not remove
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate {
private:
  //
  // Private member variables for the abstraction.
  // This implementation uses a low-level C array, bars, to store a list of
  // BarCharts.  As a result, you must also keep track of the number of
  // elements stored (size) and the capacity of the array (capacity).
  // This IS dynamic array, so it must expand automatically, as needed.
  //
  BarChart *barcharts; // pointer to a C-style array
  int size;
  int capacity;
  string title;
  string xlabel;
  string source;
  string category;
  map<string, string> colorMap;
  int k;

public:
  // a parameterized constructor:
  // Like the ourvector, the barcharts C-array should be constructed here
  // with a capacity of 4.
  BarChartAnimate(string title, string xlabel, string source) {
    this->title = title;
    this->xlabel = xlabel;
    this->source = source;
    capacity = 4;
    barcharts = new BarChart[capacity];
    size = 0;
    category = "";
    k = 0;
  }

  //
  // destructor:
  //
  // Called automatically by C++ to free the memory associated
  // by BarChartAnimate.
  //
  virtual ~BarChartAnimate() { delete[] barcharts; }

  // addFrame:
  // adds a new BarChart to the BarChartAnimate object from the file stream.
  // if the barcharts has run out of space, double the capacity (see
  // ourvector.h for how to double the capacity).
  // See application.cpp and handout for pre and post conditions.
  void addFrame(ifstream &file) {

    if (size == capacity) {
      int newCapacity = capacity * 2;
      BarChart *newbarcharts = new BarChart[newCapacity];

      // copy the elements from A to the new array:
      for (int i = 0; i < size; ++i) {
        newbarcharts[i] = barcharts[i];
      }

      // now delete A, and update private data members to point to new array
      // and reflect new capacity:
      delete[] barcharts;
      barcharts = newbarcharts;
      capacity = newCapacity;
    }
    string line, frame, name, value, country;
    int num = 0;
    int v = 0;
    int count = 0;

    // get the first two lines
    getline(file, line, '\n');
    file >> num;
    if (num) {
      BarChart bar(num + 1);
      for (int i = 0; i <= num; i++) {
        getline(file, line, '\n');
        stringstream ss(line);
        getline(ss, frame, ',');
        bar.setFrame(frame);
        getline(ss, name, ',');
        getline(ss, country, ',');
        getline(ss, value, ',');
        stringstream s(value);
        s >> v;
        getline(ss, this->category, ',');
        for (auto a : colorMap) {
          if (a.first == this->category) {
            count++;
          }
        }

        if (count == 0) {
          if (k > 6) {
            k = 0;
          }
          colorMap[this->category] = COLORS[k];
          k++;
        }
        count = 0;
        bar.addBar(name, v, this->category);
      }
      barcharts[this->size] = bar;
      this->size++;
    }
  }
  // animate:
  // this function plays each frame stored in barcharts.  In order to see the
  // animation in the terminal, you must pause between each frame.  To do so,
  // type:  usleep(3 * microsecond);
  // Additionally, in order for each frame to print in the same spot in the
  // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
  // in between each frame.
  void animate(ostream &output, int top, int endIter) {
    // int count = 0;
    unsigned int microsecond = 50000;
    if (endIter == -1) {
      endIter = size;
    }
    for (int j = 0; j < endIter; j++) {
      usleep(3 * microsecond);
      output << CLEARCONSOLE;
      output << BLACK << title << endl;
      output << BLACK << source << endl;
      barcharts[j].graph(output, colorMap, top);
      output << BLACK << xlabel << endl;
      output << BLACK << "Frame: " << barcharts[j].getFrame() << endl;
      output << endl;
    }
  }
  void animateframe(ostream &output, int top, int endIter, string frame) {
    // int count = 0;
    unsigned int microsecond = 50000;
    if (endIter == -1) {
      endIter = size;
    }
    for (int j = 0; j < endIter; j++) {
      usleep(3 * microsecond);
      output << CLEARCONSOLE;
      output << BLACK << title << endl;
      output << BLACK << source << endl;
      if (barcharts[j].getFrame() == frame) {
        barcharts[j].graph(output, colorMap, top);
      }
      output << BLACK << xlabel << endl;
      output << BLACK << "Frame: " << frame << endl;
      output << endl;
    }
  }

  //
  // Public member function.
  // Returns the size of the BarChartAnimate object.
  //
  int getSize() { return size; }

  //
  // Public member function.
  // Returns BarChart element in BarChartAnimate.
  // This gives public access to BarChart stored in the BarChartAnimate.
  // If i is out of bounds, throw an out_of_range error message:
  // "BarChartAnimate: i out of bounds"
  //
  BarChart &operator[](int i) {
    if (i >= size || i < 0) {
      throw out_of_range("BarChart: i out of bounds");
    }
    return barcharts[i];
  }
};
