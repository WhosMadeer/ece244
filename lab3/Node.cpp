//
//  Node.cpp
//  Lab 3 The Resistor Network Program
// Author: Mahir Khandaker
// Date: 10/09/2024

#include "Node.h"

Node::Node() {
    numRes = 0; // number of resistors connected to the node
    voltage = 0; // voltage of the node
    voltageIsSet = false; // true if the user sets the voltage
}

bool Node::canAddResistor() {
    return numRes < MAX_RESISTORS_PER_NODE;
}

void Node::addResistor(int rIndex) { // index of the resistor in the array
    resIDArray[numRes] = rIndex;
    numRes = numRes + 1;
}

double Node::getVoltage(){
    return voltage;
}

void Node::setVoltage(double voltage_){
    voltage = voltage_;
    voltageIsSet = true;
}

void Node::setVoltageInternally(double voltage_){
    voltage = voltage_;
}

bool Node::isVoltageSet(){
    return voltageIsSet;
}

int Node::getNumRes() {
    return numRes;
}

int* Node::getResIDArray(){
    return resIDArray;
}