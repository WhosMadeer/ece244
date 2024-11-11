#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "Customer.h"
#include "QueueList.h"
#include "Register.h"
#include "RegisterList.h"

using namespace std;

// Function Declarations:

// Set mode of the simulation
string getMode();

// Register
void parseRegisterAction(stringstream& lineStream, string mode);
void openRegister(
  stringstream& lineStream,
  string mode);  // register opens (it is upto customers to join)
void closeRegister(stringstream& lineStream,
  string mode);  // register closes 

// Customer
void addCustomer(stringstream& lineStream,
  string mode);  // customer wants to join


// Helper functions
bool getInt(stringstream& lineStream, int& iValue);
bool getDouble(stringstream& lineStream, double& dValue);
bool foundMoreArgs(stringstream& lineStream);

// Global variables
RegisterList* registerList; // holding the list of registers
QueueList* doneList; // holding the list of customers served
QueueList* singleQueue; // holding customers in a single virtual queue
double expTimeElapsed; // time elapsed since the beginning of the simulation

// List of commands:
// To open a register
// register open <ID> <secPerItem> <setupTime> <timeElapsed>
// To close register
// register close <ID> <timeElapsed>
// To add a customer
// customer <items> <timeElapsed>


// time calculation function
void calcTime(double timeElapsed, string mode);

int main() {
  registerList = new RegisterList();
  doneList = new QueueList();
  singleQueue = new QueueList();
  expTimeElapsed = 0;

  // Set mode by the user
  string mode = getMode();

  string line;
  string command;

  cout << "> ";  // Prompt for input
  getline(cin, line);

  while (!cin.eof()) {
    stringstream lineStream(line);
    lineStream >> command;
    if (command == "register") {
      parseRegisterAction(lineStream, mode);
    }
    else if (command == "customer") {
      addCustomer(lineStream, mode);
    }
    else {
      cout << "Invalid operation" << endl;
    }
    cout << "> ";  // Prompt for input
    getline(cin, line);
  }

  // You have to make sure all dynamically allocated memory is freed 
  // before return 0

  Customer* c = doneList->get_head();
  double maximumWaitTime = 0.0, averageWaitTime = 0.0, sdwt = 0.0;
  double numOfCustomers = 0.0;
  double totalWaitTime = 0.0;

  while (c != NULL) {
    double waitTime = c->get_departureTime() - c->get_arrivalTime();
    // cout << waitTime << endl;
    if (maximumWaitTime < waitTime) {
      maximumWaitTime = waitTime;
    }

    totalWaitTime = totalWaitTime + waitTime;
    numOfCustomers = numOfCustomers + 1.0;

    c = c->get_next();

  }

  averageWaitTime = (double)totalWaitTime / (double)numOfCustomers;

  c = doneList->get_head();

  double sum = 0.0;
  while (c != NULL) {
    double waitTime = c->get_departureTime() - c->get_arrivalTime();

    sum = sum + pow(waitTime - averageWaitTime, 2.0);

    c = c->get_next();

  }

  sdwt = pow(sum / numOfCustomers, 0.5);

  // double mew = 0, sigma = 0, top = 0;
  // double numOfCustomers = 0, maximumWaitTime = 0;

  // while (c != NULL) {
  //   double waitTime = c->get_departureTime() - c->get_arrivalTime();
  //   if (maximumWaitTime < waitTime) {
  //     maximumWaitTime = waitTime;
  //   }
  //   mew = mew + waitTime;
  //   numOfCustomers++;

  //   c = c->get_next();
  // }

  // if (numOfCustomers != 0) {
  //   mew = mew / numOfCustomers;

  //   c = doneList->get_head();

  //   while (c != NULL) {
  //     top = top + c->get_arrivalTime() - mew;
  //     c = c->get_next();
  //   }
  //   top = top * top;
  //   sigma = pow((top / numOfCustomers), 0.5);
  // }


  cout << endl;
  cout << "Finished at time " << expTimeElapsed << endl;
  cout << "Statistics:" << endl;
  cout << "  Maximum wait time: " << maximumWaitTime << endl;
  cout << "  Average wait time: " << averageWaitTime << endl;
  cout << "  Standard Deviation of wait time: " << sdwt << endl;



  delete registerList;
  delete doneList;
  delete singleQueue;
  return 0;
}

string getMode() {
  string mode;
  cout << "Welcome to ECE 244 Grocery Store Queue Simulation!" << endl;
  cout << "Enter \"single\" if you want to simulate a single queue or "
    "\"multiple\" to "
    "simulate multiple queues: \n> ";
  getline(cin, mode);

  if (mode == "single") {
    cout << "Simulating a single queue ..." << endl;
  }
  else if (mode == "multiple") {
    cout << "Simulating multiple queues ..." << endl;
  }

  return mode;
}

void addCustomer(stringstream& lineStream, string mode) {
  int items;
  double timeElapsed;
  if (!getInt(lineStream, items) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments." << endl;
    return;
  }
  // Depending on the mode of the simulation (single or multiple),
  // add the customer to the single queue or to the register with
  // fewest items

  calcTime(timeElapsed, mode);
  Customer* newCustomer = new Customer(expTimeElapsed, items);
  cout << "A customer entered" << endl;

  if (mode == "multiple") {
    Register* minItemsRegister = registerList->get_min_items_register();
    minItemsRegister->get_queue_list()->enqueue(newCustomer);
    cout << "Queued a customer with quickest register " << minItemsRegister->get_ID() << endl;
  }
  if (mode == "single") {
    if (registerList->get_free_register() != NULL) { // * there is a free register for the customer to go to.
      Register* freeRegister = registerList->get_min_items_register();
      freeRegister->get_queue_list()->enqueue(newCustomer);
      cout << "Queued a customer with free register " << freeRegister->get_ID() << endl;
      // if (freeRegister->get_availableTime() > newCustomer->get_arrivalTime()) { // * 
      //   newCustomer->set_arrivalTime(freeRegister->get_availableTime());
      // }
    }
    else {
      singleQueue->enqueue(newCustomer);
      cout << "No free registers" << endl;
    }
  }

}

void parseRegisterAction(stringstream& lineStream, string mode) {
  string operation;
  lineStream >> operation;
  if (operation == "open") {
    openRegister(lineStream, mode);
  }
  else if (operation == "close") {
    closeRegister(lineStream, mode);
  }
  else {
    cout << "Invalid operation" << endl;
  }
}

void openRegister(stringstream& lineStream, string mode) {
  int ID;
  double secPerItem, setupTime, timeElapsed;
  // convert strings to int and double
  if (!getInt(lineStream, ID) || !getDouble(lineStream, secPerItem) ||
    !getDouble(lineStream, setupTime) ||
    !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }

  // Check if the register is already open
  // If it's open, print an error message
  // Otherwise, open the register
  // If we were simulating a single queue, 
  // and there were customers in line, then 
  // assign a customer to the new register


  if (registerList->foundRegister(ID)) {
    cout << "Error: register " << ID << " is already open" << endl;
  }
  else {
    calcTime(timeElapsed, mode);
    Register* newRegister = new Register(ID, secPerItem, setupTime, expTimeElapsed);
    registerList->enqueue(newRegister);
    cout << "Opened register " << ID << endl;
    if (mode == "single") {
      if (singleQueue->get_head() != nullptr) {
        newRegister->get_queue_list()->enqueue(singleQueue->dequeue());
        cout << "Queued a customer with free register " << ID << endl;
      }
    }
    else {

    }
  }


}

void closeRegister(stringstream& lineStream, string mode) {
  int ID;
  double timeElapsed;
  // convert string to int
  if (!getInt(lineStream, ID) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }
  // Check if the register is open
  // If it is open dequeue it and free it's memory
  // Otherwise, print an error message 


  if (registerList->foundRegister(ID)) {
    // Register *p = registerList->get_head();

    // while (p != NULL && p->get_ID() != ID){
    //   p = p->get_next();
    // }
    calcTime(timeElapsed, mode);

    Register* toDelete = registerList->dequeue(ID);

    delete toDelete;

    cout << "Closed register " << ID << endl;
  }
  else {
    cout << "Error: register " << ID << " is not open" << endl;
  }


}

bool getInt(stringstream& lineStream, int& iValue) {
  // Reads an int from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  iValue = stoi(command);
  return true;
}

bool getDouble(stringstream& lineStream, double& dvalue) {
  // Reads a double from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  dvalue = stod(command);
  return true;
}

bool foundMoreArgs(stringstream& lineStream) {
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  else {
    return true;
  }
}

void calcTime(double timeElapsed, string mode) {
  expTimeElapsed = expTimeElapsed + timeElapsed;


  // Register* r = registerList->calculateMinDepartTimeRegister(expTimeElapsed);

  // while (r != NULL && r->get_queue_list()->get_head() != NULL) {
  //   double customerDepartTime = r->calculateDepartTime();
  //   if (customerDepartTime != -1 && customerDepartTime <= expTimeElapsed) {
  //     r->departCustomer(doneList);
  //     cout << "Departed a customer at register ID " << r->get_ID() << " at " << customerDepartTime << endl;
  //   }
  // }


  // Register* r = registerList->get_head();

  // while (r != NULL) {
  //   double customerDepartTime = r->calculateDepartTime();
  //   if (customerDepartTime != -1 && customerDepartTime <= expTimeElapsed) {
  //     r->departCustomer(doneList);
  //     // cout << customerDepartTime << endl;
  //     cout << "Departed a customer at register ID " << r->get_ID() << " at " << customerDepartTime << endl;
  //   }
  //   r = r->get_next();
  // }


  // TODO: need to change to check until mindepearttime is null

  // ? old code
  // Register* r = NULL;

  // for (int i = 0; i < registerList->get_size(); i++) {
  //   r = registerList->calculateMinDepartTimeRegister(expTimeElapsed);

  //   if (r != NULL && r->get_queue_list()->get_head() != NULL) {
  //     double customerDepartTime = r->calculateDepartTime();
  //     if (customerDepartTime != -1 && customerDepartTime <= expTimeElapsed) {
  //       r->departCustomer(doneList);
  //       cout << "Departed a customer at register ID " << r->get_ID() << " at " << customerDepartTime << endl;
  //     }
  //   }

  // }


  // * new solution that uses a while loop
  Register* r = registerList->calculateMinDepartTimeRegister(expTimeElapsed); // * sets r to be the min register

  while (r != NULL) {
    if (r != NULL && r->get_queue_list()->get_head() != NULL) {
      double customerDepartTime = r->calculateDepartTime();
      if (customerDepartTime != -1 && customerDepartTime <= expTimeElapsed) {
        r->departCustomer(doneList);
        cout << "Departed a customer at register ID " << r->get_ID() << " at " << customerDepartTime << endl;
        if (mode == "single") {
          if (singleQueue->get_head() != nullptr) {
            r->get_queue_list()->enqueue(singleQueue->dequeue());
            cout << "Queued a customer with free register " << r->get_ID() << endl;
          }
        }
      }
    }
    r = registerList->calculateMinDepartTimeRegister(expTimeElapsed);
  }

}
