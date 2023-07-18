//
//  Project 1 - DNA Profiling
// Name: Ayesha Quadri Syeda
// Due Date: 6/26/2022
// Purpose: Work with function decompostion, file
// opening, command creation, and ourvector
//

#include "ourvector.h"
#include <fstream>
#include <sstream>
#include <string>

/*
* Struct to hold database contents
*/
struct Person {
  string name;
  ourvector<int> values;
  ourvector<char> DNA;
};

/*
* Struct to hold proccessed DNA contents
*/
struct DNA {
  ourvector<char> dna;
  int max;
};
using namespace std;
/*
* The function takes a string containing the line of data to be separated, and a Person object to add to the ourvector, values.
* Separates the names from the STR counts and adds the STR counts to the Person object's values.
*/
void parseline(string line, Person &person) {
  stringstream eachline(line);
  getline(eachline, person.name, ',');
  while (!eachline.eof()) {
    if (!eachline.fail()) {
      string num;
      getline(eachline, num, ',');
      if (isdigit(num[0])) {
        person.values.push_back(stoi(num));
      }
    }
  }
}
/*
* The function takes in a file name, an empty ourvector, people, and returns nothing.
* The function opens the file and save the contents appropriately into the people ourvector.
*/
void load_db(string filename, ourvector<Person> &people) {
  cout << "Loading database...";
  ifstream file(filename);
  string line;
  if (file.is_open()) {
    cout << endl;
    getline(file, line, '\n');
    while (!file.eof()) {
      Person person;
      getline(file, line, '\n');
      parseline(line, person);
      people.push_back(person);
    } // end while loop
  }   // check if open
  else {
    cout << "\nError: unable to open '" << filename << "'" << endl;
  }
} // load_db function end
 /*
* Prints the contents of the loaded database.
*/
void printdatabase(ourvector<Person> people) {
  if (people.size() != 0) {
    cout << "Database loaded: " << endl;
    for (auto p : people) {
      cout << p.name;
      for (int i = 0; i < p.values.size(); i++) {
        cout << " " << p.values[i];
      }
      cout << endl;
    }
    cout << endl;
  } else {
    cout << "No database loaded." << endl;
  }
}
/*
* Prints the loaded DNA 
*/
void printDNA(ourvector<char> dna) {
  if (dna.size() != 0) {
    cout << "DNA loaded: " << endl;
    int i = 0;
    while (i < (dna.size() - 1)) {
      cout << dna[i];
      i++;
    }
    cout << endl;
  } else {
    cout << "No DNA loaded." << endl;
  }
}
/*
* The function takes a file name and empty ourvector and returns nothing.
* It opens the file and copies the contents into the ourvector that was passed by reference.
*/
void load_dna(string filename, ourvector<char> &dna) {
  cout << "Loading DNA..." << endl;
  ifstream file(filename);
  if (file.is_open()) {
    while (!file.eof()) {
      if (!file.fail()) {
        char d;
        file >> d;
        dna.push_back(d);
      }
    }
  } else {
    cout << "Error: unable to open '" << filename << "'" << endl;
  }
}
/*
* Prints the process information
* The function takes DNA information as a paramter and returns nothing.
*/
void printprocess(ourvector<DNA> DNA) {
  if (DNA.size() > 0) {
    cout << "\nDNA processed, STR counts: " << endl;
    for (auto a : DNA) {
      for (int i = 0; i < a.dna.size(); i++) {
        cout << a.dna[i];
      }
      cout << ": " << a.max << endl;
    }
  } else {
    cout << "\nNo DNA has been processed." << endl;
  }
}
/*
* The function takes an empty ourvector by reference, DNA, and and ourvector of char containing loaded DNA, dna, as parameters.
* It checks for the AGATC STR sequence in the loaded DNA
* It does not return anyting, but makes the changes through the parameters passed by reference
*/
void agatc(ourvector<DNA> &DNA, ourvector<char> dna) {

  struct DNA d;
  d.dna.push_back('A');
  d.dna.push_back('G');
  d.dna.push_back('A');
  d.dna.push_back('T');
  d.dna.push_back('C');
  d.max = 0;
  int count = 0;
  int counta = 0;

  for (int i = dna.size() - 1; i > 5; i--) {
    if (dna[i] == 'C' && dna[i - 1] == 'T' && dna[i - 2] == 'A' &&
        dna[i - 3] == 'G' && dna[i - 4] == 'A') {
      counta++;
      if (dna[i - 5] == dna[i] && dna[i - 6] == dna[i - 1] &&
          dna[i - 7] == dna[i - 2] && dna[i - 8] == dna[i - 3] &&
          dna[i - 9] == dna[i - 4]) {
        count++;
      } else if (count > 0) {
        if (count > d.max) {
          d.max = count + 1;
        }
        count = 0;
      } else if (counta >= 1 && count == 0 && d.max == 0) {
        d.max = 1;
      }
    }
    counta = 0;
  }
  DNA.push_back(d);
}
/*
* The function takes an empty ourvector by reference, DNA, and and ourvector of char containing loaded DNA, dna, as parameters.
* It checks for the AATG STR sequence in the loaded DNA
* It does not return anyting, but makes the changes through the parameters passed by reference
*/
void aatg(ourvector<DNA> &DNA, ourvector<char> dna) {
  struct DNA d;
  d.dna.push_back('A');
  d.dna.push_back('A');
  d.dna.push_back('T');
  d.dna.push_back('G');
  d.max = 0;
  int count = 0;
  int counta = 0;

  for (int i = dna.size() - 1; i > 4; i--) {
    if (dna[i] == 'G' && dna[i - 1] == 'T' && dna[i - 2] == 'A' &&
        dna[i - 3] == 'A') {
      counta++;
      if (dna[i - 4] == dna[i] && dna[i - 5] == dna[i - 1] &&
          dna[i - 6] == dna[i - 2] && dna[i - 7] == dna[i - 3]) {
        count++;
      } else if (count > 0) {
        if (count > d.max) {
          d.max = count + 1;
        }
        count = 0;
      } else if (counta >= 1 && count == 0 && d.max == 0) {
        d.max = 1;
      }
    }
    counta = 0;
  }
  DNA.push_back(d);
}
/*
* The function takes an empty ourvector by reference, DNA, and and ourvector of char containing loaded DNA, dna, as parameters.
* It checks for the TATC STR sequence in the loaded DNA
* It does not return anyting, but makes the changes through the parameters passed by reference
*/
void tatc(ourvector<DNA> &DNA, ourvector<char> dna) {
  struct DNA d;
  d.dna.push_back('T');
  d.dna.push_back('A');
  d.dna.push_back('T');
  d.dna.push_back('C');
  d.max = 0;
  int count = 0;
  int counta = 0;

  for (int i = dna.size() - 1; i > 4; i--) {
    if (dna[i] == 'C' && dna[i - 1] == 'T' && dna[i - 2] == 'A' &&
        dna[i - 3] == 'T') {
      counta++;
      if (dna[i - 4] == dna[i] && dna[i - 5] == dna[i - 1] &&
          dna[i - 6] == dna[i - 2] && dna[i - 7] == dna[i - 3]) {
        count++;
      } else if (count > 0) {
        if (count > d.max) {
          d.max = count + 1;
        }
        count = 0;
      } else if (counta >= 1 && count == 0 && d.max == 0) {
        d.max = 1;
      }
    }
    counta = 0;
  }
  DNA.push_back(d);
}
/*
* The function takes an empty ourvector by reference, DNA, and and ourvector of char containing loaded DNA, dna, as parameters.
* It checks for the TTTTTTCT STR sequence in the loaded DNA
* It does not return anyting, but makes the changes through the parameters passed by reference
*/
void ttttttct(ourvector<DNA> &DNA, ourvector<char> dna) {
  struct DNA d;
  d.dna.push_back('T');
  d.dna.push_back('T');
  d.dna.push_back('T');
  d.dna.push_back('T');
  d.dna.push_back('T');
  d.dna.push_back('T');
  d.dna.push_back('C');
  d.dna.push_back('T');
  d.max = 0;
  int count = 0;
  int counta = 0;

  for (int i = dna.size() - 1; i > 8; i--) {
    if ((dna[i] == 'T') && (dna[i - 1] == 'C') && (dna[i - 2] == 'T') &&
        (dna[i - 3] == 'T') && (dna[i - 4] == 'T') && (dna[i - 5] == 'T') &&
        (dna[i - 6] == 'T') && (dna[i - 7] = 'T')) {
      counta++;
      if ((dna[i - 8] == 'T') && (dna[i - 9] == 'C') && (dna[i - 10] == 'T') &&
          (dna[i - 11] == 'T') && (dna[i - 12] == 'T') &&
          (dna[i - 13] == 'T') && (dna[i - 14] == 'T') && (dna[i - 15] = 'T')) {
        count++;
      } else if (count > 0) {
        if (count > d.max) {
          d.max = count + 1;
        }

        count = 0;
      } else if (counta >= 1 && count == 0 && d.max == 0) {
        d.max = 1;
      }
    }
  }
  DNA.push_back(d);
}
/*
* The function takes an empty ourvector by reference, DNA, and and ourvector of char containing loaded DNA, dna, as parameters.
* It checks for the TCTAG STR sequence in the loaded DNA
* It does not return anyting, but makes the changes through the parameters passed by reference
*/
void tctag(ourvector<DNA> &DNA, ourvector<char> dna) {
  struct DNA d;
  d.dna.push_back('T');
  d.dna.push_back('C');
  d.dna.push_back('T');
  d.dna.push_back('A');
  d.dna.push_back('G');
  d.max = 0;
  int count = 0;
  int counta = 0;
  for (int i = dna.size() - 1; i > 5; i--) {
    if ((dna[i] == 'G') && (dna[i - 1] == 'A') && (dna[i - 2] == 'T') &&
        (dna[i - 3] == 'C') && (dna[i - 4] == 'T')) {
      counta++;

      if ((dna[i - 5] == 'G') && (dna[i - 6] == 'A') && (dna[i - 7] == 'T') &&
          (dna[i - 8] == 'C') && (dna[i - 9] == 'T')) {
        count++;
      } else if (count > 0) {
        if (count > d.max) {
          d.max = count + 1;
        }
        count = 0;
      } else if (counta >= 1 && count == 0 && d.max == 0) {
        d.max = 1;
      }
    }
  }
  DNA.push_back(d);
}
/*
* The function takes an empty ourvector by reference, DNA, and and ourvector of char containing loaded DNA, dna, as parameters.
* It checks for the GATA STR sequence in the loaded DNA
* It does not return anyting, but makes the changes through the parameters passed by reference
*/
void gata(ourvector<DNA> &DNA, ourvector<char> dna) {
  struct DNA d;
  d.dna.push_back('G');
  d.dna.push_back('A');
  d.dna.push_back('T');
  d.dna.push_back('A');
  d.max = 0;
  int count = 0;
  int counta = 0;

  for (int i = dna.size() - 1; i > 4; i--) {
    if ((dna[i] == 'A') && (dna[i - 1] == 'T') && (dna[i - 2] == 'A') &&
        (dna[i - 3] == 'G')) {
      counta++;

      if ((dna[i - 4] == 'A') && (dna[i - 5] == 'T') && (dna[i - 6] == 'A') &&
          (dna[i - 7] == 'G')) {
        count++;
      } else if (count > 0) {
        if (count > d.max) {
          d.max = count + 1;
        }
        count = 0;
      } else if (counta >= 1 && count == 0 && d.max == 0) {
        d.max = 1;
      }
    }
  }
  DNA.push_back(d);
}
/*
* The function takes an empty ourvector by reference, DNA, and and ourvector of char containing loaded DNA, dna, as parameters.
* It checks for the GAAA STR sequence in the loaded DNA
* It does not return anyting, but makes the changes through the parameters passed by reference
*/
void gaaa(ourvector<DNA> &DNA, ourvector<char> dna) {
  struct DNA d;
  d.dna.push_back('G');
  d.dna.push_back('A');
  d.dna.push_back('A');
  d.dna.push_back('A');
  d.max = 0;
  int count = 0;
  int counta = 0;

  for (int i = dna.size() - 1; i > 4; i--) {
    if ((dna[i] == 'A') && (dna[i - 1] == 'A') && (dna[i - 2] == 'A') &&
        (dna[i - 3] == 'G')) {
      counta++;

      if ((dna[i - 4] == 'A') && (dna[i - 5] == 'A') && (dna[i - 6] == 'A') &&
          (dna[i - 7] == 'G')) {
        count++;
      } else if (count > 0) {
        if (count > d.max) {
          d.max = count + 1;
        }

        count = 0;
      } else if (counta >= 1 && count == 0 && d.max == 0) {
        d.max = 1;
      }
    }
  }
  DNA.push_back(d);
}
/*
* The function takes an empty ourvector by reference, DNA, and and ourvector of char containing loaded DNA, dna, as parameters.
* It checks for the TCTG STR sequence in the loaded DNA
* It does not return anyting, but makes the changes through the parameters passed by reference
*/
void tctg(ourvector<DNA> &DNA, ourvector<char> dna) {
  struct DNA d;
  d.dna.push_back('T');
  d.dna.push_back('C');
  d.dna.push_back('T');
  d.dna.push_back('G');
  d.max = 0;
  int count = 0;
  int counta = 0;

  for (int i = dna.size() - 1; i > 4; i--) {
    if ((dna[i] == 'G') && (dna[i - 1] == 'T') && (dna[i - 2] == 'C') &&
        (dna[i - 3] == 'T')) {
      counta++;

      if ((dna[i - 4] == 'G') && (dna[i - 5] == 'T') && (dna[i - 6] == 'C') &&
          (dna[i - 7] == 'T')) {
        count++;
      } else if (count > 0) {
        if (count > d.max) {
          d.max = count + 1;
        }
        count = 0;
      } else if (counta >= 1 && count == 0 && d.max == 0) {
        d.max = 1;
      }
    }
  }
  DNA.push_back(d);
}
/*
* processsmall function takes an empty ourvector by reference, DNA, and and ourvector of char containing loaded DNA, dna, as parameters.
* The function calls different DNA sequence functions to check for sequences in the loaded DNA and keep track of the longest continious strands.
* This function is called when the "small.txt" file is used.
* The fucntion does not return anything.
*/
void processsmall(ourvector<DNA> &DNA, ourvector<char> dna) {
  if (dna.size() != 0) {
    cout << "Processing DNA..." << endl;
    agatc(DNA, dna);
    aatg(DNA, dna);
    tatc(DNA, dna);
  } else
    cout << "No DNA loaded." << endl;
}
/*
* processlarge function takes an empty ourvector by reference, DNA, and and ourvector of char containing loaded DNA, dna, as parameters.
* The function calls different DNA sequence functions to check for sequences in the loaded DNA and keep track of the longest continious strands.
* This function is called when the "large.txt" file is used.
* The fucntion does not return anything.
*/
void processlarge(ourvector<DNA> &DNA, ourvector<char> dna) {
  if (dna.size() != 0) {
    cout << "Processing DNA..." << endl;
    agatc(DNA, dna);
    ttttttct(DNA, dna);
    aatg(DNA, dna);
    tctag(DNA, dna);
    gata(DNA, dna);
    tatc(DNA, dna);
    gaaa(DNA, dna);
    tctg(DNA, dna);
  } else
    cout << "No DNA loaded." << endl;
}
/*
* search function takes an ourvector containing DNA information, DNA, and an ourvector containing the people's information, people, as parameters.
* The search function looks through the number of STR counts and matches them with the values that each person has.
* If a match is found, the function returns the name of the person 
* If a match is not found, the function returns "Not Found"
*/
string search(ourvector<DNA> DNA, ourvector<Person> people) {

  cout << "Searching database..." << endl;
  int r = 0;
  ourvector<int> a;
  for (auto d : DNA) {
    a.push_back(d.max);
  }
  for (auto p : people) {
    ourvector<int> b;
    for (int i = 0; i < p.values.size(); i++) {
      b.push_back(p.values[i]);
    }
    if (a.size() == b.size()) {
      for (int i = 0; i < b.size(); i++) {
        if (b[i] == a[i]) {
          r++;
        }
        if (r == b.size()) {
          return p.name;
        }
      }
      r = 0;
    }
    b.clear();
  }
  string result = "Not Found";
  return result;
}

int main() {
  // declaring variables
  ourvector<Person> people;
  ourvector<char> dna;
  ourvector<DNA> DNA;
  string command = "go";
  string filename;
  string dnafile;

  // initial default output
  cout << "Welcome to the DNA Profiling Application." << endl;
  cout << "\nEnter one of the Commands:" << endl;
  cout << "load_db" << endl;
  cout << "display" << endl;
  cout << "load_dna" << endl;
  cout << "process" << endl;
  cout << "search" << endl;
  cout << "debug" << endl;
  cout << "# ==> to Exit" << endl << endl;

  cin >> command;
  cout << endl;
  
  while (command != "#") {
    if (command == "load_db") {

      cout << "Enter File name (small.txt/ large.txt): ";
      cin >> filename;
      people.clear();
      DNA.clear();
      load_db(filename, people);
      
      cout << "\nEnter command or # to exit: ";
      cin >> command;
      
    } else if (command == "display") {

      cout << endl;

      printdatabase(people);
      printDNA(dna);
      printprocess(DNA);

      cout << "\nEnter command or # to exit: ";

      cin >> command;
    } else if (command == "load_dna") {

      cout << "Enter DNA file name (1.txt/2.txt...): ";
      cin >> dnafile;
      dna.clear();
      
      load_dna(dnafile, dna);
      
      cout << "Enter command or # to exit: ";
      cin >> command;

    } else if (command == "process") {

      
      if (filename == "small.txt") {
        processsmall(DNA, dna);
      } else if (filename == "large.txt") {
        processlarge(DNA, dna);
      } else
        cout << "No database loaded." << endl;
      
      cout << "Enter command or # to exit: ";
      cin >> command;

    } else if (command == "search") {
      string result;
      
      if (people.size() != 0 && DNA.size() != 0 && dna.size() != 0) {
        result = search(DNA, people);
        if (result != "Not Found") {
          cout << "Found in database! ";
          cout << "DNA matches: " << result << endl;
        } else if (result == "Not Found") {
          cout << "Not found in database." << endl;
        }
      } else if (people.size() == 0) {
        cout << "No database loaded." << endl;
      } else if (DNA.size() == 0) {
        if (dna.size() == 0) {
          cout << "No DNA loaded." << endl;
        } else {
          cout << "No DNA processed." << endl;
        }
      } else if (dna.size() == 0) {
        cout << "No DNA loaded." << endl;
      }
      
      cout << "Enter command or # to exit: ";
      cin >> command;
    } else if (command == "debug") { // Works through all the commands.
      
      cout << "Enter command or # to exit: Debugging..." << endl;

      // load database
      filename = "small.txt";
      people.clear();
      DNA.clear();
      load_db(filename, people);

      // display
      printdatabase(people);
      printDNA(dna);
      printprocess(DNA);

      // load DNA
      dna.clear();
      dnafile = "1.txt";
      load_dna(dnafile, dna);

      // display
      printdatabase(people);
      printDNA(dna);
      printprocess(DNA);

      // process
      processsmall(DNA, dna);

      // search
      string result;
      if (people.size() != 0 && DNA.size() != 0 && dna.size() != 0) {
        result = search(DNA, people);
        if (result != "Not Found") {
          cout << "Found in database! ";
          cout << "DNA matches: " << result << endl;
        } else if (result == "Not Found") {
          cout << "Not found in database." << endl;
        }
      } else if (people.size() == 0) {
        cout << "No database loaded." << endl;
      } else if (DNA.size() == 0) {
        if (dna.size() == 0) {
          cout << "No DNA loaded." << endl;
        } else {
          cout << "No DNA processed." << endl;
        }
      } else if (dna.size() == 0) {
        cout << "No DNA loaded." << endl;
      }

      // display
      printdatabase(people);
      printDNA(dna);
      printprocess(DNA);

      cin >> command;
    } // end of debug command
  }   // end of while loop

  cout << "Enter command or # to exit: ";

  return 0;
} // end of main()
