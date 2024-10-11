//
//  Resistor.cpp
//  Lab 3 The Resistor Network Program
// Author:
// Date:

#include "Resistor.h"

#include <iomanip>

Resistor::Resistor(string name_, double resistance_, int endpoints_[2]){ // endpoints by ID (1 ... n)
  name = name_;
  resistance = resistance_;
  endpointNodeIDs[0] = endpoints_[0];
  endpointNodeIDs[1] = endpoints_[1];
}

string Resistor::getName(){
  return name;
}

double getResistance(){
  return resistance;
}

void Resistor::setResistance(double resistance_){
  resistance = resistance_
}


int Resistor::getOtherEndpoint(int nodeIndex){ // nodeIndex is from 1 to N Node ID
  for (int i = 0; i < 2; i++){
    if (endpointNodeIDs[i] != nodeIndex){
      return endpointNodeIDs[i];
    }
  }
}

void Resistor::print() {
  cout << std::left << std::setw(20) << name << std::right << std::setw(8)
       << std::fixed << std::setprecision(2) << resistance << " Ohms "
       << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl;
}
