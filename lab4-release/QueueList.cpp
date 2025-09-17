#include "QueueList.h"

#include "Customer.h"

QueueList::QueueList() { head = nullptr; }

QueueList::QueueList(Customer* customer) { head = customer; }

QueueList::~QueueList() {
  Customer* current = head; // Start from the head of the queue
    while (current != nullptr) {
        Customer* toDelete = current; // Store the current node to delete
        delete toDelete;
        current = current->get_next(); // Move to the next node
    }
}

Customer* QueueList::get_head() { 
  return head;
 }

void QueueList::enqueue(Customer* customer) {

  // Create a new node to add to the queue
      //Customer* newNode = new Customer(*customer);  // Allocate new customer node

        if (head == nullptr) {
            head = customer;
        } else {
            Customer* temp = head;
            while (temp->get_next() != nullptr) {
                temp = temp->get_next();
            }
            temp->set_next(customer);
        }
  // a customer is placed at the end of the queue
  // if the queue is empty, the customer becomes the head
  
}

Customer* QueueList::dequeue() {
  if (head == nullptr){
    return nullptr;
  }
  Customer* temp = head;
  head = temp->get_next();
  temp->set_next(nullptr);
  //delete temp;???
  return temp;
  // remove a customer from the head of the queue 
  // and return a pointer to it
  
}

int QueueList::get_items() {
  int count = 0;
    Customer* current = head;
    if(head == nullptr) {
      return count;
    }
    // Traverse the linked list and count each node
    while (current != nullptr) {
        count += current->get_numOfItems();
        current = current->get_next();
    }
    return count;
  // count total number of items each customer in the queue has
}

void QueueList::print() {
  // print customers in a queue
  Customer* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
