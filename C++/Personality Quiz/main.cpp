/*
 * File name: main.cpp
 * Author: Ayesha Quadri Syeda
 * Purpose: Creating a Personality quiz app
 * Due Date: 7/3/2022
 */

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "driver.h"

using namespace std;

// Struct to hold people names
struct People {
  int id;
  string type;
};

// Function to pasrse the personality factor from the letter
void parseFactor(string factor, string &a, string &b) {
  size_t pos = factor.find(':');
  a = factor.substr(0, pos);
  b = factor.substr(pos + 1);
}

// Function to parse a line in the file into separate pieces of information
void parseQuestion(string q, Question &line) {
  stringstream ss(q);
  getline(ss, line.questionText, '.');
  while (!ss.eof()) {
    string f, a, b;
    getline(ss, f, ' ');
    parseFactor(f, a, b);
    stringstream s(b);
    int c;
    s >> c;
    if (a[0]) {
      line.factors[a[0]] = c;
    }
  }
}

// Function to load the personality questions from "questions.txt"
void loadQuestion(set<Question> &questions) {
  ifstream file("questions.txt");
  if (file.is_open()) {
    while (!file.eof()) {
      if (!file.fail()) {
        string q;
        Question line;
        getline(file, q, '\n');
        if (!q.empty()) {
          parseQuestion(q, line);
          questions.insert(line);
        }
      }
    }
  }
}

// Function to pick and display questions
void questionPrompt(set<Question> &questions, map<Question, int> &scores) {
  cout << "How much do you agree with this statement?" << endl;
  Question q = randomQuestionFrom(questions);
  cout << "\"" << q.questionText << ".\"" << endl << endl;
  cout << "1. Strongly disagree" << endl;
  cout << "2. Disagree" << endl;
  cout << "3. Neutral" << endl;
  cout << "4. Agree" << endl;
  cout << "5. Strongly agree" << endl << endl;
  cout << "Enter your answer here (1-5): ";
  int answer;
  cin >> answer;
  cout << endl;
  scores[q] = answer;
}

// Function to create the names of personality types
void createtype(string type, int id, vector<People> &p) {
  People t;
  t.type = type;
  t.id = id;
  p.push_back(t);
}

// Calls the function createtype and sends the valid information
void peopleType(vector<People> &p) {
  createtype("BabyAnimals", 1, p);
  createtype("Brooklyn99", 2, p);
  createtype("Disney", 3, p);
  createtype("Hogwarts", 4, p);
  createtype("MyersBriggs", 5, p);
  createtype("SesameStreet", 6, p);
  createtype("StarWars", 7, p);
  createtype("Vegetables", 8, p);
  createtype("mine", 9, p);
}

// Prints the different types of personality names
void printType(vector<People> &p) {
  for (auto a : p) {
    cout << a.id << ". " << a.type << endl;
  }
  cout << "0. To end program." << endl << endl;
}

// Function separates the different data in a given string for Person struct
void parsePeople(string q, Person &line) {
  stringstream ss(q);
  getline(ss, line.name, '.');
  while (!ss.eof()) {
    string f, a, b;
    getline(ss, f, ' ');
    parseFactor(f, a, b);
    stringstream s(b);
    int c;
    s >> c;
    if (a[0]) {
      line.scores[a[0]] = c;
    }
  }
}

// Function Loads the People files
void loadPeople(string filename, set<Person> &people) {
  ifstream file(filename);
  if (file.is_open()) {
    while (!file.eof()) {
      if (!file.fail()) {
        string q;
        Person line;
        getline(file, q, '\n');
        if (!q.empty()) {
          parsePeople(q, line);
          people.insert(line);
        }
      }
    }
  }
}

// Function creates and holds the different types of personality files
void files(vector<string> &files) {
  files.push_back("BabyAnimals.people");
  files.push_back("Brooklyn99.people");
  files.push_back("Disney.people");
  files.push_back("Hogwarts.people");
  files.push_back("MyersBriggs.people");
  files.push_back("SesameStreet.people");
  files.push_back("StarWars.people");
  files.push_back("Vegetables.people");
  files.push_back("mine.people");
}
int main() {
  set<Question> questions;
  map<Question, int> scores;
  vector<string> f;
  vector<People> p;
  map<char, int> s;
  int num = 0;
  loadQuestion(questions);

  cout << "Welcome to the Personality Quiz!" << endl << endl;
  cout << "Choose number of questions: ";
  cin >> num;
  cout << endl;
  for (int i = 0; i < num; i++) {
    questionPrompt(questions, scores);
  }

  s = scoresFrom(scores);
  peopleType(p);
  printType(p);
  files(f); 
  cin >> num;

  while (num != 0) {
    cout << "Choose test number (1-9, or 0 to end): ";
    set<Person> people;
    loadPeople(f.at(num - 1), people);
    Person match = mostSimilarTo(s, people);
    cout << "You got " << match.name << "!" << endl << endl;
    printType(p);
    cin >> num;
  }
  cout << "Choose test number (1-9, or 0 to end): Goodbye!";
  return 0;
}
