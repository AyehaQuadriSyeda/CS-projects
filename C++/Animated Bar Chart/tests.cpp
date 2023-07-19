#include "barchartanimate.h"
#include <iostream>
using namespace std;

// tests the default constructor
bool testBarDefaultConstructor() {
  Bar b;
  if (b.getName() != "") {
    cout << "testBarDefaultConstructor: getName failed" << endl;
    return false;
  } else if (b.getValue() != 0) {
    cout << "testBarDefaultConstructor: getValue failed" << endl;
    return false;
  } else if (b.getCategory() != "") {
    cout << "testBarDefaultConstructor: getCategory failed" << endl;
    return false;
  }
  cout << "testBarDefaultConstructor: all passed!" << endl;
  return true;
}

// tests the parameter constructor
bool testBarParamConstructor() {
  Bar b("Chicago", 9234324, "US");
  if (b.getName() != "Chicago") {
    cout << "testBarParamConstructor: getName failed" << endl;
    return false;
  } else if (b.getValue() != 9234324) {
    cout << "testBarParamConstructor: getValue failed" << endl;
    return false;
  } else if (b.getCategory() != "US") {
    cout << "testBarParamConstructor: getCategory failed" << endl;
    return false;
  }
  cout << "testBarParamConstructor: all passed!" << endl;
  return true;
}

// tests the less than operator
bool testBarLessthanoperator() {
  Bar a("Chicago", 9234324, "US");
  Bar b("Newark", 489314, "US");
  bool result;

  // test if it correctly returns true
  result = b < a;
  if (!result) {
    cout << "testBarLessthanoperator: < failed" << endl;
    return false;
  }
  cout << "testBarLessthanoperator: < passed!" << endl;
  return true;

  // test if it correctly returns false
  result = a < b;
  if (result) {
    cout << "testBarLessthanoperator: < failed" << endl;
    return false;
  }
  cout << "testBarLessthanoperator: < passed!" << endl;
  return true;
}

// tests the less than or equal to operator
bool testBarLessthanorequalto() {
  Bar a("Chicago", 9234324, "US");
  Bar b("Newark", 489314, "US");
  bool result;

  // test if it correctly returns true
  result = b <= a;
  if (!result) {
    cout << "testBarLessthanorequalto: < failed" << endl;
    return false;
  }
  cout << "testBarLessthanorequalto: < passed!" << endl;
  return true;

  // test if it correctly returns false
  result = a <= b;
  if (result) {
    cout << "testBarLessthanorequalto: < failed" << endl;
    return false;
  }
  cout << "testBarLessthanorequalto: < passed!" << endl;
  return true;
}

// test more than operator
bool testBarMorethanoperator() {
  Bar a("Chicago", 9234324, "US");
  Bar b("Newark", 489314, "US");
  bool result;

  // test if it correctly returns true
  result = a > b;
  if (!result) {
    cout << "testBarMorethanoperator: < failed" << endl;
    return false;
  }
  cout << "testBarMorethanoperator: < passed!" << endl;
  return true;

  // test if it correctly returns false
  result = b > a;
  if (result) {
    cout << "testBarMorethanoperator: < failed" << endl;
    return false;
  }
  cout << "testBarMorethanoperator: < passed!" << endl;
  return true;
}

// test more than or equal to operator
bool testBarMorethanequalto() {
  Bar a("Chicago", 9234324, "US");
  Bar b("Newark", 489314, "US");
  bool result;

  // test if it correctly returns true
  result = a >= b;
  if (!result) {
    cout << "testBarMorethanorequalto: < failed" << endl;
    return false;
  }
  cout << "testBarMorethanorequalto: < passed!" << endl;
  return true;

  // test if it correctly returns false
  result = b > a;
  if (result) {
    cout << "testBarMorethanorequalto: < failed" << endl;
    return false;
  }
  cout << "testBarMorethanorequalto: < passed!" << endl;
  return true;
}

//tests tje default constructor
bool testBarChartDefaultConstructor() {
  BarChart bc;
  if (bc.getFrame() != "") {
    cout << "testBarChartDefaultConstructor: getFrame failed" << endl;
    return false;
  } else if (bc.getSize() != 0) {
    cout << "testBarChartDefaultConstructor: getFrame failed" << endl;
    return false;
  }
  cout << "testBarChartDefaultConstructor: all passed!" << endl;
  return true;
}

//tests the parameterized constructor
bool testBarChartParameterConstructor() {
  BarChart bc(10);
  if (bc.getFrame() != "") {
    cout << "testBarChartParameterConstructor: getFrame failed" << endl;
    return false;
  } else if (bc.getSize() != 0) {
    cout << "testBarChartParameterConstructor: getFrame failed" << endl;
    return false;
  }
  cout << "testBarChartParameterConstructor: all passed!" << endl;
  return true;
}

//tests the copy constructor
bool testBarChartCopyConstructor() {
  BarChart bc(10);
  BarChart bcCopy(bc);

  if (bcCopy.getFrame() != bc.getFrame()) {
    cout << "testBarChartCopyConstructor: getFrame failed" << endl;
    return false;
  } else if (bcCopy.getSize() != bc.getSize()) {
    cout << "testBarChartCopyConstructor: getSize failed" << endl;
    return false;
  }
  cout << "testBarChartCopyConstructor: all passed!" << endl;
  return true;
}

//tests the copy operator
bool testBarChartCopyOperator() {
  BarChart bcCopy;
  BarChart bc(10);
  bcCopy = bc;
  if (bcCopy.getFrame() != bc.getFrame()) {
    cout << "testBarChartCopyOperator: getFrame failed" << endl;
    return false;
  } else if (bcCopy.getSize() != bc.getSize()) {
    cout << "testBarChartCopyOperator: getSize failed" << endl;
    return false;
  }
  cout << "testBarChartCopyOperator: all passed!" << endl;
  return true;
}

//tests the clear function
bool testBarChartclear() {
  BarChart bc(10);
  bc.clear();
  if (bc.getFrame() != "") {
    cout << "testBarChartclear: getFrame failed" << endl;
    return false;
  } else if (bc.getSize() != 0) {
    cout << "testBarChartclear: getFrame failed" << endl;
    return false;
  }
  cout << "testBarChartclear: all passed!" << endl;
  return true;
}

//tests the setFrame function
bool testBarChartSetFrame() {
  BarChart bc(10);
  bc.setFrame("2000");
  if (bc.getFrame() != "2000") {
    cout << "testBarChartSetFrame: setFrame() failed" << endl;
    return false;
  }
  cout << "testBarchartSetFrame: setFrame() passed!" << endl;
  return true;
}

//tests the addBar function
bool testBarChartaddBar() {
  BarChart bc(2);
  bc.addBar("Chicago", 1020, "US");
  bc.addBar("NYC", 1300, "US");
  if (bc.getSize() != 2) {
    cout << "testBarChartaddBar: in limit failed" << endl;
    return false;
  } else if (bc.addBar("Paris", 1200, "France")) {
    cout << "testBarChartaddBar: out of limit failed" << endl;
    return false;
  }
  cout << "testBarChartaddBar: all passed!" << endl;
  return true;
}

//tests the [] operator for BarChart
bool testBarChartOperator() {
  BarChart bc(3);
  bc.addBar("Chicago", 1020, "US");
  bc.addBar("NYC", 1300, "US");
  bc.addBar("Paris", 1200, "France");
  if (bc[0].getName() != "Chicago" && bc[1].getName() != "NYC" &&
      bc[2].getName() != "Paris") {
    cout << "testBarChartOperator: getName failed" << endl;
    return false;
  }
  if (bc[0].getValue() != 1020 && bc[1].getValue() != 1300 &&
      bc[2].getValue() != 1200) {
    cout << "testBarChartOperator: getValue failed" << endl;
    return false;
  }
  if (bc[0].getCategory() != "US" && bc[1].getCategory() != "US" &&
      bc[2].getCategory() != "France") {
    cout << "testBarChartOperator: getCategory failed" << endl;
    return false;
  }
  cout << "testBarChartOperator: all passed!" << endl;
  return true;
}

//tests the dump function for BarChart
bool testBarChartdump() {
  BarChart bc(3);
  bc.addBar("Chicago", 1020, "US");
  bc.addBar("NYC", 1300, "US");
  bc.addBar("Paris", 1200, "France");
  bc.setFrame("1950");
  bc.dump(cout);
  return true;
}

//tests the BarChart graph function
bool testBarChartgraph() {
  BarChart bc(4);
  bc.addBar("Chicago", 1020, "US");
  bc.addBar("NYC", 1300, "US");
  bc.addBar("Paris", 1200, "France");
  bc.addBar("London", 1000, "UK");
  bc.setFrame("1950");
  const string RED("\033[1;31m");
  const string BLUE("\033[1;34m");
  map<string, string> colorMap;
  colorMap["US"] = RED;
  colorMap["France"] = BLUE;
  bc.graph(cout, colorMap, 4);
  return true;
}

//tests the default parameterized constructor
bool testBarChartAnimateConstructor()
{
  BarChartAnimate bca("The most populus cities", "sources", "population");
  if(bca.getSize() != 0)
  {
    cout << "testBarChartAnimateConstructor: getSize() failed" << endl;
    return false;
  }
  cout << "testBarChartAnimateConstructor: getSize() passed!" << endl;
    
    return true;
}

//tests the addFrame function
bool testBarChartAnimateaddFrame()
{
  string filename = "cities.txt";
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source);
	
	while (!inFile.eof()) {
		bca.addFrame(inFile);
	}
  
  if(bca.getSize() != 519)
  {
    cout << "testBarChartAnimateaddFrame: addFrame failed" << endl;
    return false;
  }
  cout << "testBarChartAnimateaddFrame: addFrame passed!" << endl;
  return true;
}

//tests the animate function
bool testBarChartAnimateanimate()
{
  //create the BarChartAnimate object and record data
  string filename = "cities.txt";
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source);
	
	while (!inFile.eof()) {
		bca.addFrame(inFile);
	}

  //call the animate function
  bca.animate(cout, 12, 1);
  return true;
}

//tests the BarChartAnimate operator
bool testBarChartAnimateoperator()
{
  //Create a BarChartAnimate object and record data
  string filename = "cities.txt";
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source);
	
	while (!inFile.eof()) {
		bca.addFrame(inFile);
	}

  //test for exact values
  if(bca[0][0].getValue() != 672)
  {
    cout << "testBarChartAnimateoperator: getValue failed" << endl;
    return false;
  }else if(bca[0][0].getCategory() != "East Asia")
  {
    cout << "testBarChartAnimateoperator: getCategory failed" << endl;
    return false;
  }else if(bca[0][0].getName() != "Beijing")
  {
    cout << "testBarChartAnimateoperator: getName failed" << endl;
    return false;
  }
  cout << "testBarChartAnimateoperator: all passed!" << endl;
  return true;
}
int main() {

  // testing Bar class
  testBarDefaultConstructor();
  testBarParamConstructor();
  testBarLessthanoperator();
  testBarLessthanorequalto();
  testBarMorethanoperator();
  testBarMorethanequalto();

  // testing BarChart class
  testBarChartDefaultConstructor();
  testBarChartParameterConstructor();
  testBarChartCopyConstructor();
  testBarChartCopyOperator();
  testBarChartclear();
  testBarChartSetFrame();
  testBarChartaddBar();
  testBarChartOperator();
  testBarChartdump();
  testBarChartgraph();

  //testing BarChartAnimate class
  testBarChartAnimateConstructor();
  testBarChartAnimateaddFrame();
  testBarChartAnimateanimate();
  testBarChartAnimateoperator();
  return 0;
}