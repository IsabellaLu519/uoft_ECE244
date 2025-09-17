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

Resistor** resistors = nullptr;  // Pointer that should point to an array of
                                 // Resistor pointers(#resister array)
Node* nodes = nullptr;  // pointer that should hold address to an array of
                        // Nodes(node array)
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

int main() {
  string line;
  
  while (!cin.eof()) { // Read until EOF
    cout << ">>> ";
    cout.flush();
    // TODO: Implement the main function here
    string input;

       
    getline(cin, input);
    input.erase(input.find_last_not_of(" \t\n\r\f\v")+1);
    stringstream ss(input);
        
    string command;
    ss >> command; // Read the command

       if(cin.eof()){
    break;
   }    

    if (command == "maxVal") {
        handleMaxVal(ss);
    }else if (command == "insertR") {
        handleInsertR(ss);
    } else if (command == "modifyR") {
        handleModifyR(ss);
    } else if (command == "deleteR") {
        handleDeleteR(ss);
    } else if (command == "setV") {
        handleSetV(ss);
    } else if (command == "printR") {
        handlePrintR(ss);
    } else if(command !=""){
      cout << "Error: invalid command" << endl;
    } 

    }

   if (resistors !=nullptr) {
    for (int i = 0; i < resistorsCount; i++) {
      if(resistors[i] != nullptr){
          delete resistors[i];
          resistorsCount = 0;
      }
    }
    delete resistors;
   }
      if(nodes != nullptr){
      delete nodes;
      }
   
   
    return 0;

}

// TODO: Implement functions here


bool getInteger(stringstream& ss, int& x) {}

bool getString(stringstream& ss, string& s) {
  if (std::getline(ss, s)) {  // Read a line from the stringstream
    return true;              // Return true if reading was successful
  } else {
    s.clear();     // Clear the string in case of failure
    return false;  // Return false if reading failed
  }
}
bool getDouble(stringstream& ss, double& s);

bool getInteger(stringstream& ss, int& x); 

void handleMaxVal(stringstream& ss) {
  //string command;
  int temNodeNumber, temResistors;

    if (resistors !=nullptr) {
    for (int i = 0; i < resistorsCount; i++) {
      if(resistors[i] != nullptr){
          delete resistors[i];
          resistorsCount = 0;
      }
    }
    delete[] resistors;
   }
      if(nodes != nullptr){
      delete[] nodes;
      }

  if (ss.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }
  
  ss >> temNodeNumber;
    if (ss.fail()) {
      cout << "Error: invalid arguments" << endl;
      return;
    }

     if (ss.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }
  
  ss >> temResistors;
    if (ss.fail()) {
      ss.clear();
      ss.ignore(1000,' ');
      cout << "Error: invalid argument" << endl;
      return;
    }
    
    maxNodeNumber = temNodeNumber;
    maxResistors = temResistors;

  // Output the message confirming the creation of the network
  cout << "New network: max node number is " << maxNodeNumber
       << "; max resistors is " << maxResistors << endl;

  // Create node array and resistor array for the network
  nodes = new Node[maxNodeNumber];     // Nodes from 0 to maxNodeNumber
  resistors = new Resistor*[maxResistors];  // Resistors array
  for (int i = 0; i <maxResistors; i++) {
    resistors[i] = nullptr;
  }


}

void handleInsertR(stringstream& ss) {
  std::string name;
  double resistance;
  int nodeId1, nodeId2;
  
 if (ss.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }

  
  ss >> name; 
    if (ss.fail()) {
      cout << "Error: invalid argument" << endl;
      return;
    }


     if (ss.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }

  
  ss >> resistance; 
    if (ss.fail()) {
      cout << "Error: invalid argument" << endl;
      return;
    }

    if (ss.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }

  
  ss >> nodeId1; 
    if (ss.fail()) {
      cout << "Error: invalid argument" << endl;
      return;
    }
  if (ss.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }

  
  ss >> nodeId2; 
    if (ss.fail()) {
      cout << "Error: invalid argument" << endl;
      return;
    }

     if (resistance < 0) {
      cout << "Error: negative resistance" << endl;
      return;
    }

    if (name == "all") {
      cout << "Error: resistor name cannot be keyword \"all\"" << endl;
      return;
    }

    for (int i = 0; i < resistorsCount; i++) {
      if(resistors[i]->getName() == name) {
        cout << "Error: resistor" << name << "already exists" << endl;
      return;
      }
    }

   if (nodeId1 < 1 || nodeId1 > maxNodeNumber || nodeId2 < 1  || nodeId2 > maxNodeNumber) {
        cout << "Error: Node value is out of permitted range 1 - " << maxNodeNumber << endl;
        return; // Exit the function if the value is out of range
    }

     if (nodeId1 == nodeId2) {
        cout << "Error: both terminals of resistor connect to same node" << endl;
        return;
    }
    

  int endpoints[2];
  endpoints[0] = nodeId1;
  endpoints[1] = nodeId2;

  //Resistor newResistor(name, resistance, endpoints);
 

  resistors[resistorsCount] = new Resistor (name, resistance, endpoints);

  int resistorIndex = resistorsCount;  // Store the index of the new resistor
  

  // Update the 2 nodes to include this resistor
    nodes[nodeId1-1].addResistor(resistorIndex);
    nodes[nodeId2-1].addResistor(resistorIndex);
    resistorsCount++;
  // Output the result
  cout << "Inserted: resistor " << name << " " << fixed << setprecision(2) << resistance << " Ohms "
       << nodeId1 << " -> " << nodeId2 << std::endl;
}

void handleModifyR(std::stringstream& ss) {
  string name;
  double newResistance;
  int count = 0;

 if (ss.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }
  ss >> name;

    if (ss.fail()) {
      cout << "Error: invalid argument" << endl;
      return;
    }
    
     if (ss.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }
  ss >> newResistance;

    if (ss.fail()) {
      cout << "Error: invalid argument" << endl;
      return;
    }

    if (newResistance < 0) {
      cout << "Error: negative resistance" << endl;
      return;
    }

    if (name == "all") {
      cout << "Error: resistor name cannot be keyword \"all\"" << endl;
      return;
    }

     for (int i = 0; i < maxResistors; i++) {
      if(resistors[i]->getName() == "name") {
        count++;
      }
     }

    if(count == 0) {
      cout << "Error: resistor" << name << "not found" << endl;
      return;
     }
    

  // Search for the resistor by name %%不对！！！
  for (int i = 0; i < resistorsCount; ++i) {
    if (resistors[i]->getName() == name) {
      // Store old resistance for logging
      double oldResistance = resistors[i]->getResistance();
      // Modify the resistance
      resistors[i]->setResistance(newResistance);

      // Output the result
      cout << "Modified: resistor " << name << " from " << oldResistance
           << " Ohms to " << fixed << setprecision(2)<< newResistance << " Ohms" << endl;
      return;
    }
  }
}

void handlePrintR(stringstream& ss) {
  string name;
  int count = 0;

  if (ss.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }

  ss >> name;

    if (ss.fail()) {
      cout << "Error: invalid argument" << endl;
      return;
    }
    
      for (int i = 0; i < maxResistors; i++) {
      if(resistors[i]->getName() == "name") {
        count++;
      }
     }
     
    if(count == 0) {
      cout << "Error: resistor" << name << "not found" << endl;
      return;
     }

  // Search for the resistor by name in the resistor array

    for(int i =0; i<maxResistors; i++) {
      if (resistors[i]->getName()== name) {
        if (resistors[i] != nullptr) {
        // Call the print function of Resistor class
        resistors[i]->print();
    } else {
        break;
    }
      
      
    }
    
}
}
void handleDeleteR(stringstream& ss){
  string resistorsToFr;

  if (ss.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }

 ss >> resistorsToFr;

    if (ss.fail()) {
      cout << "Error: invalid argument" << endl;
      return;
    }
  
    
  if (resistorsToFr == "all") {
        if (resistors !=nullptr) {
    for (int i = 0; i < resistorsCount; i++) {
      if(resistors[i] != nullptr){
          delete resistors[i];
          resistors[i] = nullptr;
      }
      resistorsCount = 0;
    }
    
   }
  }
   if(nodes != nullptr) {
    delete[] nodes;
    nodes = nullptr;
   }
      cout << "Deleted: all resistors" << endl;
  
}

void handleSetV(stringstream& ss){
  	int nodeid;
    double voltage;

    if (ss.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }

  ss >> nodeid;
    if (ss.fail()) {
      cout << "Error: invalid argument" << endl;
      return;
    }
    
      if (ss.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }

  ss >> voltage;
    if (ss.fail()) {
      cout << "Error: invalid argument" << endl;
      return;
    }

   

   if (nodeid <= 1 || nodeid >= maxNodeNumber) {
        cout << "Error: Node value is out of permitted range 1 - " << maxNodeNumber << endl;
        return; // Exit the function if the value is out of range
    }

    // Set the voltage of the specified node
    nodes[nodeid].setVoltage(voltage);

    // Print a confirmation message
    cout << "Set: node " << nodeid << "to " << fixed << setprecision(2) << voltage << " Volts." << endl;
}




/*
// Check for duplicate resistor names
for (int i = 0; i < resistorsCount; ++i) {
  if (resistors[i].name == name) {
    std::cout << "A resistor with the name " << name << " already exists."
              << std::endl;
    return;
  }
}
*/