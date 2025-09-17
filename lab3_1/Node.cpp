//
//  Node.cpp
//  Lab 3 The Resistor Network Program
// Author: Isabella Lu
// Date:

#include "Resistor.h"
#include "Node.h"
using namespace std;


Node::Node() { //default constructor
  numRes = 0;
  voltage = 0.0;
  voltageIsSet = false;  
}

bool Node::canAddResistor() { //whether adable?
    return (numRes < MAX_RESISTORS_PER_NODE );
}

void Node::addResistor(int rIndex) {
    resIDArray[numRes] = rIndex;
    numRes++;   
}

double Node::getVoltage(){  // returns voltage
    return voltage;
}
void Node::setVoltage(double voltage_){  // sets voltage and sets voltageIsSet to true
    voltage = voltage_;
    voltageIsSet = true;
}

void Node::setVoltageInternally(double voltage_){ // sets voltage temporarily during iterations for solve command
    voltage = voltage_;
}//%%

bool Node::isVoltageSet(){   // returns voltageIsSet
    return voltageIsSet;
}

int Node::getNumRes(){       // returns numRes
    return numRes;
}
  
int* Node::getResIDArray() {  // returns resIDArray
    return resIDArray;
}