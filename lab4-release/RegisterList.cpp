#include "RegisterList.h"

#include <iostream>

#include "Register.h"
using namespace std;

RegisterList::RegisterList() {
  head = nullptr;
  size = 0;
}

RegisterList::~RegisterList() {
  Register *current = head;
  Register *next = nullptr;
  while(current != nullptr){
    next = current->get_next();
    current->set_next(nullptr);
    delete current;
    current = next;
  }
  head = nullptr;
  //delete registerList;

  // Delete all registers in the list
}

Register* RegisterList::get_head() { 
  return head;
 }

int RegisterList::get_size() { 
    return size;
  // return number of registers 
}


Register* RegisterList::get_min_items_register() {
  if (head == nullptr) {
        return nullptr; // Return nullptr if the list is empty
    }
    
  Register* minRegister = head; // Start with the head as the min register
  QueueList* minQueuelist  = head->get_queue_list();;
  int minItem = minQueuelist->get_items();
  Register* current = head->get_next();
  while(current != nullptr) {
    QueueList* currentQueuelist = current->get_queue_list();
    int numItem = currentQueuelist->get_items();
    if(numItem < minItem){
      minItem = numItem;
      minRegister = current;
    }
    current = current->get_next();
  }
  return minRegister;
  // loop all registers to find the register with least number of items 
}

Register* RegisterList::get_free_register() {
  Register* current = head; // Start with the head of the list
    while (current != nullptr) {
       QueueList* currentQueuelist = current->get_queue_list();
       Customer* temp = currentQueuelist->get_head();
      if (temp == nullptr) { 
          return current; // Return the first free register found
      }
      current = current->get_next(); // Move to the next register
    }
    return nullptr; 

  // return the register with no customers
  // if all registers are occupied, return nullptr
}

void RegisterList::enqueue(Register* newRegister) {
  //Register* newAddRegister = new Register(*newRegister);
  if (head == nullptr) {
      head = newRegister;
  }else {
    Register* current = head;
    while(current->get_next() != nullptr) {
      current = current->get_next(); // Traverse to the last register
    }
    current->set_next(newRegister); // Set the next of the last register to the new register
  }
  size++; 
  // a register is placed at the end of the queue
  // if the register's list is empty, the register becomes the head
  // Assume the next of the newRegister is set to null
  // You will have to increment size  
}

bool RegisterList::foundRegister(int ID) {
  Register* current = head;
  while(current != nullptr) {
    if(current->get_ID() == ID){
      return true;
    }
    current = current->get_next();
  }
  return false;
  // look for a register with the given ID
  // return true if found, false otherwise
}

Register* RegisterList::dequeue(int ID) {
  if(!foundRegister(ID)){
    return nullptr;
  }
  Register* pre = head;
  Register* current = head->get_next();
  if(head->get_ID() == ID){
    //Register* needreturn = pre;
    head = pre->get_next();
    pre->set_next(nullptr);
    size--;
    //delete pre;//?????
    return pre;
  }
  while(current != nullptr) {
    if(current->get_ID() == ID){
      pre->set_next(current->get_next());
      //Register* needreturn = current;
      current->set_next(nullptr);
      //delete current;//????
      size--;
      return current;
    }
    pre = current;
    current = current->get_next();
  }
  return nullptr;
  // dequeue the register with given ID
  // return the dequeued register
  // return nullptr if register was not found
}

Register* RegisterList::calculateMinDepartTimeRegister(double expTimeElapsed) {
  Register* minRegister = nullptr;
    double minDepartTime = std::numeric_limits<double>::max();

    Register* current = head;
    while (current != nullptr) {
        double departTime = current->calculateDepartTime();
        if (departTime != -1 && departTime < minDepartTime) {
            minDepartTime = departTime;
            minRegister = current;
        }
        current = current->get_next();
    }

    return minRegister;
  // return the register with minimum time of departure of its customer
  // if all registers are free, return nullptr
}

void RegisterList::print() {
  Register* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
