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
void parseRegisterAction(stringstream &lineStream, string mode);
void openRegister(
    stringstream &lineStream,
    string mode);  // register opens (it is upto customers to join)
void closeRegister(stringstream &lineStream,
                   string mode);  // register closes 

// Customer
void addCustomer(stringstream &lineStream,
                 string mode);  // customer wants to join


// Helper functions
bool getInt(stringstream &lineStream, int &iValue);
bool getDouble(stringstream &lineStream, double &dValue);
bool foundMoreArgs(stringstream &lineStream);

// Global variables
RegisterList *registerList; // holding the list of registers
QueueList *doneList; // holding the list of customers served
QueueList *singleQueue; // holding customers in a single virtual queue
double expTimeElapsed; // time elapsed since the beginning of the simulation

// List of commands:
// To open a register
// register open <ID> <secPerItem> <setupTime> <timeElapsed>
// To close register
// register close <ID> <timeElapsed>
// To add a customer
// customer <items> <timeElapsed>

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
    } else if (command == "customer") {
      addCustomer(lineStream, mode);
    } else {
      cout << "Invalid operation" << endl;
    }
    cout << "> ";  // Prompt for input
    getline(cin, line);
  }

//print final word
    double totalWaitTime = 0.0;
    double maxWaitTime = 0.0;
    int count = 0;
    double waitTime;

    Customer* current = doneList->get_head(); // Assuming QueueList has a method to get the head customer

    // Calculate total wait time and maximum wait time
    while (current != nullptr) {
        waitTime = current->get_departureTime() - current->get_arrivalTime(); // Assuming Customer has these attributes
        totalWaitTime += waitTime;
        if (waitTime > maxWaitTime) {
            maxWaitTime = waitTime;
        }
        count++;
        current = current->get_next(); // Assuming the customer list is linked
    }

    // Calculate average wait time
    double averageWaitTime = totalWaitTime / count;

    // Calculate standard deviation
    double varianceSum = 0.0;
    current = doneList->get_head(); // Reset pointer to head
    while (current != nullptr) {
        waitTime = current->get_departureTime() - current->get_arrivalTime();
        varianceSum += (waitTime - averageWaitTime) * (waitTime - averageWaitTime);
        current = current->get_next();
    }
    double standardDeviation = sqrt(varianceSum / count);

    // Print results
    cout << "Finished at time " << expTimeElapsed << endl; 
    cout << "Statistics:" << endl;
    cout << "Maximum wait time: " << maxWaitTime << endl;
    cout << "Average wait time: " << averageWaitTime << endl;
    cout << "Standard Deviation of wait time: " << standardDeviation << endl;


  delete registerList;
  delete doneList;
  delete singleQueue;
  // You have to make sure all dynamically allocated memory is freed 
  // before return 0
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
  } else if (mode == "multiple") {
    cout << "Simulating multiple queues ..." << endl;
  }

  return mode;
}

void addCustomer(stringstream &lineStream, string mode) {
  int items;
  double timeElapsed;
  int times = 0;
  int numFreeReg = 0;
  if (!getInt(lineStream, items) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments." << endl;
    return;
  }
  Customer *newCustomer = new Customer(timeElapsed, items);//dynamic 
  double arri = newCustomer->get_arrivalTime();
  newCustomer->set_arrivalTime(expTimeElapsed + arri);
  Register* currentRegister = registerList->get_head();
  //先查可以走的人,按时间循环
  //Register* currentRegister = registerList->get_head();
  if(registerList->get_head()->get_queue_list()->get_head() != nullptr){
  for (int count = 0; count <= (timeElapsed * 10); count++) {
    double i = expTimeElapsed + count * 0.1;
    currentRegister = registerList->get_head();
    //cout<<currentRegister->calculateDepartTime()<<" AA"<<currentRegister->get_ID()<<endl;
   // cout<<currentRegister->get_availableTime()<<endl;
    while(currentRegister != nullptr){
      if(fabs(currentRegister->calculateDepartTime() - i) < 1e-6){
        currentRegister->departCustomer(doneList);
        cout << "Departed a customer at register ID "<< currentRegister->get_ID() << " at " << i << endl;
        //cout<<currentRegister->get_availableTime()<<endl;
        numFreeReg++;

        if(singleQueue->get_head() != nullptr){
            currentRegister->get_queue_list()->enqueue(singleQueue->get_head());
            singleQueue->dequeue();
            cout << "Queued a customer with free register " << currentRegister->get_ID() << endl;
            //cout << "A customer entered" << endl;
            //Register* freeReg2 = registerList->get_free_register(); 
          }
        }
        currentRegister = currentRegister->get_next();
    }
  }
  }


  if (mode == "multiple") {
    //先查可以走的人,按时间循环
    //这句在查完可以走的人以后怎么样都要打印
    // Find the register with the least number of customers in the queue
    Register* targetRegister = registerList->get_min_items_register();
      if (targetRegister != nullptr) {
        targetRegister->get_queue_list()->enqueue(newCustomer); // Assuming Register has a method to get its QueueList
        cout << "Queued a customer with quickest register " << targetRegister->get_ID() << endl;
      } 
    } else if (mode == "single") {
      //先查可以走的人,按时间循环
      //这句在查完可以走的人以后怎么样都要打印
      
      //然后找有没有free的柜台,加到free里
      Register* freeReg = registerList->get_free_register();
      if(freeReg != nullptr){
        //cout<<freeReg->get_availableTime()<<endl;
        //已经在singleQueue里面的人要先去空位
        if(singleQueue->get_head() != nullptr){
          Register* freeReg2;
          while(singleQueue->get_head() != nullptr && times < numFreeReg){
              freeReg2 = registerList->get_free_register();
              freeReg2->get_queue_list()->enqueue(singleQueue->get_head());
              singleQueue->dequeue();
              cout << "Queued a customer with free register " << freeReg2->get_ID() << endl;
              //cout << "A customer entered" << endl;
              //Register* freeReg2 = registerList->get_free_register();
              times++;
          }
          singleQueue->enqueue(newCustomer);
          cout << "A customer entered" << endl;
          cout << "No free registers" << endl;   
        }else{
          freeReg->get_queue_list()->enqueue(newCustomer);
          cout << "A customer entered" << endl;
          cout << "Queued a customer with free register " << freeReg->get_ID() << endl;
          
          //cout<<"bb"<<endl;
        }
        //cout<<freeReg->calculateDepartTime()<<endl;
        //cout<<freeReg->get_queue_list()->get_head()->get_numOfItems()<< freeReg->get_secPerItem() << freeReg->get_overheadPerCustomer() << freeReg->get_availableTime()<<"ff"<<endl;
        //cout << "Queued a customer with free register " << freeReg->get_ID() << endl;
      }else{//没有就去singleQueue排队
      // Add the customer to the single queue
        singleQueue->enqueue(newCustomer);
        cout << "A customer entered" << endl;
        cout << "No free registers" << endl;
      }
    }
   expTimeElapsed += timeElapsed;
  // Depending on the mode of the simulation (single or multiple),
  // add the customer to the single queue or to the register with
  // fewest items 
}

void parseRegisterAction(stringstream &lineStream, string mode) {
  string operation;
  lineStream >> operation;
  if (operation == "open") {
    openRegister(lineStream, mode);
  } else if (operation == "close") {
    closeRegister(lineStream, mode);
  } else {
    cout << "Invalid operation" << endl;
  }
}

void openRegister(stringstream &lineStream, string mode) {
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
    if (registerList->foundRegister(ID)) { // Ensure this function is implemented
        cout << "Error: register " << ID << " is already open" << endl;
        return;
    }
  Register* currentRegister = registerList->get_head();
  //先查可以走的人,按时间循环
  //Register* currentRegister = registerList->get_head();
  
  for (int count = 0; count <= (timeElapsed * 10); count++) {
    double i = expTimeElapsed + count * 0.1;
    currentRegister = registerList->get_head();
    while(currentRegister != nullptr){
      //cout<<"test"<<endl;
      //cout<<currentRegister->get_availableTime()<<endl;
      //cout<<currentRegister->calculateDepartTime() << "and" << i <<endl;
      if(fabs(currentRegister->calculateDepartTime() - i) < 1e-6){
        currentRegister->departCustomer(doneList);
        cout << "Departed a customer at register ID "<< currentRegister->get_ID() << " at " << i << endl;
        
          if(singleQueue->get_head() != nullptr){
            currentRegister->get_queue_list()->enqueue(singleQueue->get_head());
            singleQueue->dequeue();
            cout << "Queued a customer with free register " << currentRegister->get_ID() << endl;
            //cout << "A customer entered" << endl;
            //Register* freeReg2 = registerList->get_free_register(); 
          }
      }
           
        currentRegister = currentRegister->get_next();
    }
  }
  // Otherwise, open the register
  Register *newRegister = new Register(ID, secPerItem, setupTime, timeElapsed);
  registerList->enqueue(newRegister); // Ensure addRegister is implemented in RegisterList
  cout << "Opened register " << ID << endl;

  double avail = newRegister->get_availableTime();
  newRegister->set_availableTime(avail+expTimeElapsed);

  // If we were simulating a single queue, 
  // and there were customers in line, then 
  // assign a customer to the new register
  if (mode == "single" && singleQueue->get_head() != nullptr) { // Assuming QueueList has a getSize() method
    Customer *firstCustomer = singleQueue->dequeue(); // Assuming dequeue returns the first customer
    newRegister->get_queue_list()->enqueue(firstCustomer); // Add customer to the new register's queue
    //cout << "Opened register " << ID << endl;
    cout << "Queued a customer with free register " << ID << endl;
  }

  expTimeElapsed += timeElapsed;
  
}

void closeRegister(stringstream &lineStream, string mode) {
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
   bool foundReg = registerList->foundRegister(ID); // Assume getRegister returns the register by ID
    if (!foundReg) {
        cout << "Error: register " << ID << " is not open" << endl;
        return;
    }

  Register* currentRegister = registerList->get_head();
  //先查可以走的人,按时间循环
  //Register* currentRegister = registerList->get_head();
  
  for (int count = 0; count <= (timeElapsed * 10); count++) {
    double i = expTimeElapsed + count * 0.1;
    currentRegister = registerList->get_head();
    while(currentRegister != nullptr){
      //cout<<"test"<<endl;
      //cout<<currentRegister->get_availableTime()<<endl;
      //cout<<currentRegister->calculateDepartTime() << "and" << i <<endl;
      if(fabs(currentRegister->calculateDepartTime() - i) < 1e-6){
        currentRegister->departCustomer(doneList);
        cout << "Departed a customer at register ID "<< currentRegister->get_ID() << " at " << i << endl;
        
          if(singleQueue->get_head() != nullptr){
            currentRegister->get_queue_list()->enqueue(singleQueue->get_head());
            singleQueue->dequeue();
            cout << "Queued a customer with free register " << currentRegister->get_ID() << endl;
            //cout << "A customer entered" << endl;
            //Register* freeReg2 = registerList->get_free_register(); 
          }
      }
           
        currentRegister = currentRegister->get_next();
    }
  }
  // If it is open dequeue it and free it's memory
  Register* regToClose = registerList->dequeue(ID);// Ensure dequeue removes the register from the list
  delete regToClose; // Free the memory associated with the register
  cout << "Closed register " << ID << endl;
  // Otherwise, print an error message 

  expTimeElapsed += timeElapsed;
  
}

bool getInt(stringstream &lineStream, int &iValue) {
  // Reads an int from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  iValue = stoi(command);
  return true;
}

bool getDouble(stringstream &lineStream, double &dvalue) {
  // Reads a double from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  dvalue = stod(command);
  return true;
}

bool foundMoreArgs(stringstream &lineStream) {
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  } else {
    return true;
  }
}


