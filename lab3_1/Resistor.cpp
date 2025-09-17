//
//  Resistor.cpp
//  Lab 3 The Resistor Network Program
// Author:
// Date:

#include "Resistor.h"

#include <iomanip>
using namespace std;

/*
Resistor::Resistor() { //default constructor

}
*/

Resistor::Resistor(string name_, double resistance_, int endpoints_[2]) { //second constructor
  this->name = name_;
  this->resistance = resistance_;
  this->endpointNodeIDs[0] = endpoints_[0];
  this->endpointNodeIDs[1] = endpoints_[1];
           }

string Resistor:: getName() { //acosser getname
  return name;
}

double Resistor:: getResistance() {//acosser resistance
  return resistance;
}

void Resistor:: setResistance(double resistance_) { //mutator set
  resistance = resistance_;
}

void Resistor::print() {
  //cout << std::left << std::setw(20) << name << std::right << std::setw(8)
       //<< std::fixed << std::setprecision(2) << resistance << " Ohms "
      // << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl;

  cout << name << " " << std::fixed << std::setprecision(2) 
              << resistance << " Ohms " << endpointNodeIDs[0] << " -> " << endpointNodeIDs[0] << std::endl;
}

int Resistor::getOtherEndpoint(int nodeIndex) { //return another node
  if(endpointNodeIDs[0] == nodeIndex) {
    return (endpointNodeIDs[1]-1);
  }
  if(endpointNodeIDs[1] == nodeIndex) {
    return (endpointNodeIDs[0]-1);
  }
  return -1;
}
