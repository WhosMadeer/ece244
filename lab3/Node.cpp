//
//  Node.cpp
//  Lab 3 The Resistor Network Program
// Author: Mahir Khandaker
// Date: 10/09/2024

#include "Node.h"

Node::Node() {
    numRes = 0;
    resIDArray = new int[MAX_RESISTORS_PER_NODE];

    voltage = 0
    voltageIsSet = false;
}

bool Node::canAddResistor() {
    return numRes < MAX_RESISTORS_PER_NODE;
}

void Node::addResistor(int rIndex) {
    resIDArray[numRes + 1] = rIndex;
    numRes++;
}

double Node::getVoltage(){
    return voltage;
}

void Node::setVoltage(double voltage_){
    voltage = voltage_
    voltageIsSet = true;
}

void Node::setVoltageInternally(double voltage_){
    voltage = voltage_
}

bool Node::isVoltageSet(){
    return isVoltageSet;
}

int Node::getNumRes() {
    return numRes;
}

int* Node::getResIDArray(){
    return resIDArray;
}