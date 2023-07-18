/*
 * File name: driver.h
 * Author: Ayesha Quadri Syeda
 * Purpose: Declare and define the different fucntions that can be used in the
 * main.cpp file. Due Date: 7/3/2022
 */

#include "myrandom.h"
#include <math.h>
#include <limits>
#include <map>
#include <set>
#include <string>

using namespace std;

constexpr double lowest_double = std::numeric_limits<double>::lowest();

/* Type: Question
 *
 * Type representing a personality quiz question.
 */
struct Question {
  string questionText;    // Text of the question
  map<char, int> factors;   // Map from factors to +1 or -1
  friend bool operator<(const Question &lhs, const Question &rhs) {
    return lhs.questionText < rhs.questionText;
  }
  friend bool operator==(const Question &lhs, const Question &rhs) {
    return lhs.questionText == rhs.questionText;
  }
  friend bool operator!=(const Question &lhs, const Question &rhs) {
    return lhs.questionText != rhs.questionText;
  }
};

/* Type: Person
 *
 * Type representing a person, used to represent people when determining
 * who's the closest match to the user.
 */
struct Person {
  string name;           // Name of the person
  map<char, int> scores;   // Map from factors to +1 or -1
  friend bool operator<(const Person &lhs, const Person &rhs) {
    return lhs.name < rhs.name;
  }
  friend bool operator==(const Person &lhs, const Person &rhs) {
    return lhs.name == rhs.name;
  }
  friend bool operator!=(const Person &lhs, const Person &rhs) {
    return lhs.name != rhs.name;
  }
};

/* randomElement
 *
 * This function selects, at random, a Question from the inputted questions set
 * and returns the question.  Note, this function does not remove the randomly
 * selected question from the set.
 */
Question randomElement(set<Question> &questions) {
  int ind = randomInteger(0, questions.size() - 1);
  int i = 0;
  for (auto e : questions) {
    if (i == ind) {
      return e;
    }
    i++;
  }
  return {};
}

// The function randomQuestionFrom takes a set of Question structs as a
// parameter, which holds unasked question. Then the function picks a random
// question, removes it from the set, and returns it.
Question randomQuestionFrom(set<Question> &questions) {
  Question e = randomElement(questions);
  if (questions.size() == 0) {
    throw runtime_error("questions set: empty");
  }
  questions.erase(e);
  return e;
}

// The function scoresFrom takes a map with quetions answered and their answer,
// then returns the scores in map format. The function checks for the question
// factors then adds up the appropriate scores.
map<char, int> scoresFrom(map<Question, int> &answers) {
  map<char, int> score;
  for (auto a : answers) {
    for (auto b : a.first.factors) {
      // cout << b.first << ": " << b.second << endl;
      score[b.first] += (b.second * (a.second - 3));
    }
  }
  return score;
}

// The function takes a map of scores as a parameter and returns the normalized
// scores in map format.
map<char, double> normalize(map<char, int> &scores) {
  unsigned int count = 0;
  double norm = 0.0;
  map<char, double> normal;
  for (auto a : scores) {
    norm += (a.second * a.second);
    if (a.second == 0) {
      count++;
    }
  }
  if (count == scores.size()) {
    throw runtime_error("scores : all zeros");
  }
  norm = sqrt(norm);
  for (auto a : scores) {
    normal[a.first] = a.second / norm;
  }
  return normal;
}

// The function cosineSimilarityOf takes two maps a parameters and returns a
// double variable holding the cosine similarity.
double cosineSimilarityOf(const map<char, double> &lhs,
                          const map<char, double> &rhs) {
  double cosine = 0.0;
  for (auto a : lhs) {
    for (auto b : rhs) {
      if (b.first == a.first) {
        cosine += (a.second * b.second);
      }
    }
  }
  return cosine;
}

// Function takes in a map with socres and a set of Person struct and returns a
// Person struct The function normalizes the scores and the set's scores, then
// finds the cosine similarity to conclude which person the user is most like
Person mostSimilarTo(map<char, int> &scores, set<Person> &people) {
  if (people.size() == 0) {
    throw runtime_error("people set : empty");
  }
  Person p;
  map<char, double> s;
  double max = lowest_double;
  s = normalize(scores);

  for (auto a : people) {
    map<char, double> person;
    person = normalize(a.scores);
    double cosine = cosineSimilarityOf(s, person);
    if (cosine > max) {
      max = cosine;
      p = a;
    }
  }
  return p;
}
