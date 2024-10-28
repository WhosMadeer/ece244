//
//  main.cpp
//  Lab 3 The Resistor Network Program
//
//  Created by Nathan Hung on 2024-09-11.
//  Modified by Salma Emara on 2024-09-30
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Node.h"
#include "Resistor.h"

using namespace std;

Resistor** resistors =
nullptr;  // Pointer that should point to an array of Resistor pointers
Node* nodes = nullptr;  // pointer that should hold address to an array of Nodes
int maxNodeNumber = 0;  // maximum number of nodes as set in the command line
int maxResistors = 0;  // maximum number of resistors as set in the command line
int resistorsCount = 0;  // count the number of resistors

string errorArray[10] = {
    "invalid command",                                  // 0
    "invalid argument",                                 // 1
    "negative resistance",                              // 2
    "node value is out of permitted range",             // 3
    "resistor name cannot be keyword \"all\"",          // 4
    "both terminals of resistor connect to same node",  // 5
    "too few arguments",                                // 6
    "resistor name not found",                          // 7
    "resistor name already exists	"                     // 8
};

// Function Prototypes
bool getInteger(stringstream& ss, int& x);
bool getString(stringstream& ss, string& s);
bool getDouble(stringstream& ss, double& s);

void handleMaxVal(stringstream& ss);
void handleInsertR(stringstream& ss);
void handleModifyR(stringstream& ss);
void handlePrintR(stringstream& ss);
void handleDeleteR(stringstream& ss);
void handleSetV(stringstream& ss);


// helper functions
void handleInput(stringstream& ss);
int countParameters(stringstream& ss);

void createNewArrays();
void deleteArrays();


int main() {
  string line;
  cout << ">>> ";
  cout.flush();
  while (!cin.eof()) {
    getline(cin, line);
    stringstream ss(line);
    if (ss.fail() || cin.eof()) { // * check if ss failed before calling other functions
      ss.clear();
      ss.ignore(1000, ' ');
    }
    else {
      cout << fixed << setprecision(2);
      handleInput(ss);
      cout << ">>> ";
      cout.flush();
    }
  }

  deleteArrays();
  return 0;
}

// Function Implemenetation
bool getInteger(stringstream& ss, int& x) { // * returns true if successful
  ss >> x;
  if (ss.fail()) {
    ss.clear();
    ss.ignore(1000, '\n');
    return false;
  }
  return true;
}

bool getString(stringstream& ss, string& s) { // * returns true if successful
  ss >> s;
  if (ss.fail()) {
    ss.clear();
    ss.ignore(1000, '\n');
    return false;
  }
  return true;
}

bool getDouble(stringstream& ss, double& s) { // * returns true if successful
  ss >> s;
  if (ss.fail()) {
    ss.clear();
    ss.ignore(1000, ' ');
    return false;
  }
  return true;
}


void handleInput(stringstream& ss) { // error validation done
  string cmd;
  if (!getString(ss, cmd)) {
    ss.clear();
    cout << "Error: " << errorArray[0] << endl;
  }
  else {
    string validInputs[7] = {
      "maxVal",
      "insertR",
      "modifyR",
      "printR",
      "deleteR",
      "setV",
      "solve"
    };


    if (cmd == validInputs[0]) {
      handleMaxVal(ss);
    }
    else if (cmd == validInputs[1]) {
      handleInsertR(ss);
    }
    else if (cmd == validInputs[2]) {
      handleModifyR(ss);
    }
    else if (cmd == validInputs[3]) {
      handlePrintR(ss);
    }
    else if (cmd == validInputs[4]) {
      handleDeleteR(ss);
    }
    else if (cmd == validInputs[5]) {
      handleSetV(ss);
    }
    else if (cmd == validInputs[6]) {
      // TODO: Create solve function
    }
    else {
      cout << "Error: " << errorArray[0] << endl;
    }
  }
}


int countParameters(stringstream& ss) {
  int count = 0;
  stringstream temp(ss.str());

  string word;

  while (temp >> word) {
    count++;
  }

  return count - 1;
}

void handleMaxVal(stringstream& ss) { // error validation done
  deleteArrays();

  int paramsCount = countParameters(ss);

  if (paramsCount != 2) {
    cout << "Error: " << errorArray[6] << endl;
    return;
  }

  if ((getInteger(ss, maxNodeNumber)) == false) {
    cout << "Error: " << errorArray[1] << endl;
    maxNodeNumber = 0;
    return;
  }
  else if ((getInteger(ss, maxResistors)) == false) {
    cout << "Error: " << errorArray[1] << endl;
    maxNodeNumber = 0;
    maxResistors = 0;
    return;
  }
  else {
    createNewArrays();
    cout << "New network: max node number is " << maxNodeNumber << "; max resistors is " << maxResistors << endl;
  }

}

void handleInsertR(stringstream& ss) { //
  string name;
  double resistance;
  int nodeArray[2]; // * Node ID is 1 indexed; array is 0 indexed

  int paramsCount = countParameters(ss);

  if (paramsCount != 4) {
    cout << "Error: " << errorArray[6] << endl;
    return;
  }

  if (!getString(ss, name)) {
    cout << "Error: " << errorArray[1] << endl;
    return;
  }
  if (!getDouble(ss, resistance)) {
    cout << "Error: " << errorArray[1] << endl;
    return;
  };
  if (!getInteger(ss, nodeArray[0])) {
    cout << "Error: " << errorArray[1] << endl;
    return;
  }
  if (!getInteger(ss, nodeArray[1])) {
    cout << "Error: " << errorArray[1] << endl;
    return;
  }

  if (resistance < 0.0) {
    cout << "Error: " << errorArray[2];
    return;
  }

  if (name == "all") {
    cout << "Error: " << errorArray[4] << endl;
    return;
  }


  // * checks to see if name is taken
  for (int i = 0; i < resistorsCount; i++) {
    if (name == resistors[i]->getName()) {// pointer to resistor object 
      cout << "Error: " << errorArray[8] << endl;
      return;
    }
  }



  // * if the ID of the node is zero or greater than maxNodeNumber
  if ((nodeArray[0] <= 0) || (nodeArray[1] <= 0) || (nodeArray[0] > maxNodeNumber) || (nodeArray[1] > maxNodeNumber)) {
    cout << "Error: node value is out of permitted range 1 - " << maxNodeNumber << endl;
    return;
  }

  // * checks if nodes are the same
  if (nodeArray[0] == nodeArray[1]) {
    cout << "Error: " << errorArray[5] << endl;
    return;
  }

  // * nodes[1 - 1] is nodes[0] and nodes[maxNodeNumber - 1]
  if (nodes[nodeArray[0] - 1].canAddResistor() && nodes[nodeArray[1] - 1].canAddResistor()) {

    // * Creates a new resistor with node values
    resistors[resistorsCount] = new Resistor(name, resistance, nodeArray);

    // * Tells the node that there is a resistor connected to it 
    nodes[nodeArray[0] - 1].addResistor(resistorsCount);
    nodes[nodeArray[1] - 1].addResistor(resistorsCount);


    // outputs the resistor is connected
    cout << "Inserted: resistor " << name << " " << resistors[resistorsCount]->getResistance() << " Ohms " << nodeArray[0] << " -> " << nodeArray[1] << endl;

    resistorsCount++;
  }
}

void handleModifyR(stringstream& ss) { // error validation done
  string name;
  double resistance, oldResistance;

  if (!getString(ss, name)) {
    cout << "Error: " << errorArray[1] << endl;
  }
  if (!getDouble(ss, resistance)) {
    cout << "Error: " << errorArray[1] << endl;
    return;
  };

  if (resistance < 0.0) {
    cout << "Error: " << errorArray[2] << endl;
    return;
  }

  if (name == "all") {
    cout << "Error: " << errorArray[4] << endl;
    return;
  }

  for (int i = 0; i < resistorsCount; i++) {
    if (name == resistors[i]->getName()) {// pointer to resistor object 
      oldResistance = resistors[i]->getResistance();
      resistors[i]->setResistance(resistance);
      cout << "Modified: resistor " << name << " from " << oldResistance << " Ohms to " << resistance << " Ohms" << endl;
      return;
    }
  }
  cout << "Error: " << errorArray[7] << endl; // * name is not found
}

void handlePrintR(stringstream& ss) { // error validation done
  string name;

  if (!getString(ss, name)) {
    cout << "Error: " << errorArray[1] << endl;
  }

  for (int i = 0; i < resistorsCount; i++) {
    if (name == resistors[i]->getName()) {// pointer to resistor object 
      resistors[i]->print();
      return;
    }
  }
  cout << "Error: " << errorArray[7] << endl;
}

void handleDeleteR(stringstream& ss) { // error validation done
  string args = "";

  if (!getString(ss, args)) {
    cout << "Error: " << errorArray[1] << endl;
  }

  if (args == "all") {
    deleteArrays();
    createNewArrays();
    cout << "Deleted: all resistors" << endl;
  }
  else {
    if (args == "") {
      cout << "Error: " << errorArray[6] << endl;
    }
    else {
      cout << "Error: " << errorArray[1] << endl;
    }
  }
}

void handleSetV(stringstream& ss) {
  int nodeID;
  double voltage;
  if (!getInteger(ss, nodeID)) {
    cout << "Error: " << errorArray[1] << endl;
    return;
  };
  if (!getDouble(ss, voltage)) {
    cout << "Error: " << errorArray[1] << endl;
    return;
  };

  nodes[nodeID - 1].setVoltage(voltage);

  cout << "Set: node " << nodeID << " to " << nodes[nodeID - 1].getVoltage() << " Volts" << endl;
}


void createNewArrays() {
  // * creates new resistors
  resistors = new Resistor * [maxResistors];

  // * creates new nodes
  nodes = new Node[maxNodeNumber];
}


void deleteArrays() {
  // * delete dynamically allociated stuff 

  delete[] nodes;
  nodes = nullptr;


  for (int i = 0; i < resistorsCount; i++) {
    delete resistors[i];
    resistors[i] = nullptr;
  }

  delete[] resistors;
  resistors = nullptr;

  resistorsCount = 0;
  maxNodeNumber = 0;
  maxResistors = 0;

}
