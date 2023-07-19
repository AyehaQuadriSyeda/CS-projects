/*
 * File name : bar.h
 * Purpose ; Declare and define the Bar class
 * Author: Ayesha Quadri Syeda
 * Due Date: 7/10/2022
 */

#include "myrandom.h" // used in autograder, do not remove
#include <iostream>
#include <string>
using namespace std;

//
// Bar
//
class Bar {
private:
  // Private member variables for a Bar object
  // NOTE: You should not be allocating memory on the heap for this class.
  string name;
  int value;
  string category;

public:
  // default constructor:
  Bar() {
    name = "";
    value = 0;
    category = "";
  }

  //
  // a second constructor:
  //
  // Parameter passed in constructor Bar object.
  //
  Bar(string name, int value, string category) {
    this->name = name;
    this->value = value;
    this->category = category;
  }

  // destructor:
  virtual ~Bar() {}

  // getName: getter for name
  string getName() { return name; }

  // getValue: getter for value
  int getValue() { return value; }

  // getCategory: getter for category
  string getCategory() { return category; }

  // operators
  // checks if the calling object is less than the parameter object
  bool operator<(const Bar &other) const {
    if (this->value < other.value) {
      return true;
    } else
      return false;
  }

  // checks if the calling object is less than or equal to the parameter object
  bool operator<=(const Bar &other) const {
    if (*this < other || value == other.value) {
      return true;
    } else
      return false;
  }

  // checks if the calling object is more than the parameter object
  bool operator>(const Bar &other) const {
    if (this->value > other.value) {
      return true;
    } else
      return false;
  }

  // checks if the calling object is more than or equal to the parameter object
  bool operator>=(const Bar &other) const {
    if (*this > other || value == other.value) {
      return true;
    } else
      return false;
  }
};
