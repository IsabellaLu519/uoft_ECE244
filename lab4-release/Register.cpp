
// Created by Salma Emara on 2023-06-02.
#include "Register.h"

#include <iostream>

using namespace std;//记得删掉

Register::Register(int id, double timePerItem, double overhead,
                   double entryTime) {
  ID = id;
  secPerItem = timePerItem;
  overheadPerCustomer = overhead;
  availableTime = entryTime;
  next = nullptr;           // no other registers yet
  queue = new QueueList();  // no customers in line yet, but has to initialize a
                            // queue
}

Register::~Register() {
  delete queue;
 }

QueueList* Register::get_queue_list() { 
  return queue;
}

Register* Register::get_next() {
  return next;
 }

int Register::get_ID() { 
  return ID;
 }

double Register::get_secPerItem() { 
  return secPerItem;
 }

double Register::get_overheadPerCustomer() { 
  return overheadPerCustomer;
 }

double Register::get_availableTime() { 
  return availableTime;
 }

void Register::set_next(Register* nextRegister) { 
  next = nextRegister;
 }


void Register::set_availableTime(double availableSince) {
  availableTime = availableSince;
}

double Register::calculateDepartTime() {
  double deptime;
  Customer* temp = queue->get_head();
  if(temp == nullptr){
    return -1;
  }else {
    if(availableTime < temp->get_arrivalTime()){
      deptime = temp->get_numOfItems() * secPerItem + overheadPerCustomer + temp->get_arrivalTime();
      //cout<<temp->get_numOfItems() << secPerItem << overheadPerCustomer << temp->get_arrivalTime()<<"GG"<<endl;
    }
    if(availableTime >= temp->get_arrivalTime()){
      deptime = temp->get_numOfItems() * secPerItem + overheadPerCustomer + availableTime;
      //cout<<temp->get_numOfItems() << secPerItem << overheadPerCustomer << availableTime<<endl;
    }
  }
  return deptime;

  // Get the departure time of the first customer in the queue
  // returns -1 if no customer is in the queue 
}

void Register::departCustomer(QueueList* doneList) {
  
  Customer* temp = queue->get_head();
  
  double departureTime = calculateDepartTime();
  temp->set_departureTime(departureTime);
  //cout<<departureTime<<"AAA"<<endl;
  doneList->enqueue(temp);
  set_availableTime(departureTime);
  queue->dequeue();
  //availableTime = calculateDepartTime();//更新可用时间
  }

  // dequeue the head, set last dequeue time, add to doneList,
  // update availableTime of the register


void Register::print() {
  std::cout << "Register ID: " << ID << std::endl;
  std::cout << "Time per item: " << secPerItem << std::endl;
  std::cout << "Overhead per customer: " << overheadPerCustomer << std::endl;
  if (queue->get_head() != nullptr) {
    std::cout << "Queue has customers: \n";
    queue->print();
  }
}
