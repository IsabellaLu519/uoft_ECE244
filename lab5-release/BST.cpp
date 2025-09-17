//
//  BST.cpp
//  Lab 5 Search Through A Database
//
//  Created by Author Name, Date
#include "BST.h"

#include "Employee.h"

void insertHelper(string order, Employee *newEmployee, Employee *current);
void printInOrderHelper(Employee *node);
Employee *searchIDHelper(Employee *node, int ID);
void searchAgeRangeHelper(Employee *node, double lowAge, double highAge);
void autocompleteHelper(Employee *node, const string &prefix);

BST::BST(string order_)
{
  root = NULL;
  order = order_;
}
BST::~BST()
{
  delete root;
}

void BST::insert(Employee *newEmployee)
{
  // newEmployee is a pointer to a dynamically allocated Employee. Insert it
  // according to the value of "order" of the binary search tree.
  if (order == "ID")
  {
    if (root == NULL)
    {
      root = newEmployee;
    }
    else
    {
      insertHelper(order, newEmployee, root);
    }
  }
  else if (order == "name")
  {
    if (root == nullptr)
    {
      root = newEmployee;
    }
    else
    {
      insertHelper(order, newEmployee, root);
    }
  }
  else if (order == "age")
  {
    if (root == nullptr)
    {
      root = newEmployee;
    }
    else
    {
      insertHelper(order, newEmployee, root);
    }
  }
}

void insertHelper(string order, Employee *newEmployee, Employee *current)
{
  // Compare based on the tree's order
  if (order == "ID")
  {
    // Insert based on ID
    if (newEmployee->getID() < current->getID())
    {
      // Go to the left
      if (current->getLeft() == nullptr)
      {
        current->setLeft(newEmployee); // Insert new node on the left
      }
      else
      {
        insertHelper(order, newEmployee, current->getLeft()); // Recur left
      }
    }
    else if (newEmployee->getID() > current->getID())
    {
      // Go to the right
      if (current->getRight() == nullptr)
      {
        current->setRight(newEmployee); // Insert new node on the right
      }
      else
      {
        insertHelper(order, newEmployee, current->getRight()); // Recur right
      }
    }
  }
  else if (order == "name")
  {
    // Insert based on name (firstName + lastName)
    if (newEmployee->getName() < current->getName())
    {
      // Go to the left
      if (current->getLeft() == nullptr)
      {
        current->setLeft(newEmployee); // Insert on the left
      }
      else
      {
        insertHelper(order, newEmployee, current->getLeft()); // Recur left
      }
    }
    else if (newEmployee->getName() > current->getName())
    {
      // Go to the right
      if (current->getRight() == nullptr)
      {
        current->setRight(newEmployee); // Insert on the right
      }
      else
      {
        insertHelper(order, newEmployee, current->getRight()); // Recur right
      }
    }
  }
  else if (order == "age")
  {
    // Insert based on age
    if (newEmployee->getAge() <= current->getAge())
    {
      // Go to the left
      if (current->getLeft() == nullptr)
      {
        current->setLeft(newEmployee); // Insert on the left
      }
      else
      {
        insertHelper(order, newEmployee, current->getLeft()); // Recur left
      }
    }
    else if (newEmployee->getAge() > current->getAge())
    {
      // Go to the right
      if (current->getRight() == nullptr)
      {
        current->setRight(newEmployee); // Insert on the right
      }
      else
      {
        insertHelper(order, newEmployee, current->getRight()); // Recur right
      }
    }
  }
}

void BST::printInOrder()
{
  return printInOrderHelper(root);
}

void printInOrderHelper(Employee *current)
{
  if (current != nullptr)
  {

    printInOrderHelper(current->getLeft());
    current->print();
    printInOrderHelper(current->getRight());
  }
}

// Helper function to search for an Employee by ID recursively
Employee *searchIDHelper(Employee *node, int ID)
{
  if (node == nullptr)
  {
    return nullptr;
  }
  if (ID == node->getID())
  {

    return node;
  }
  else if (ID < node->getID())
  {
    return searchIDHelper(node->getLeft(), ID);
  }
  else
  {
    return searchIDHelper(node->getRight(), ID);
  }
}

// Search for an employee with a particular ID
Employee *BST::searchID(int ID)
{
  if (order != "ID")
  {

    return nullptr;
  }

  // Call the helper function
  Employee *findEmp = searchIDHelper(root, ID);

  if (findEmp == nullptr)
  {
    // If not found, print an error message
    // cout << ID << " ID does not exist" << endl;
  }

  return findEmp;
}

// Helper function for in-order traversal to search within the age range
void searchAgeRangeHelper(Employee *node, double lowAge, double highAge)
{
  if (node == nullptr)
  {
    return; // Base case: null node
  }

  // Recur on the left subtree if there might be nodes with ages < lowAge
  if (node->getAge() >= lowAge)
  {
    searchAgeRangeHelper(node->getLeft(), lowAge, highAge);
  }

  // Check if the current node's age is within the range
  if (node->getAge() >= lowAge && node->getAge() <= highAge)
  {
    node->print(); // Print the employee details
  }

  // Recur on the right subtree if there might be nodes with ages > highAge
  if (node->getAge() < highAge)
  {
    searchAgeRangeHelper(node->getRight(), lowAge, highAge);
  }
}

// Function to search for employees within an age range
void BST::searchAgeRange(double lowAge, double highAge)
{
  if (order != "age")
  {
    return;
  }

  // Perform the in-order traversal to search for employees
  searchAgeRangeHelper(root, lowAge, highAge);
}

// Helper function for in-order traversal to find matching names
void autocompleteHelper(Employee *node, const string &prefix)
{
  if (node == nullptr)
  {
    return; // Base case: null node
  }
  // Check if the current node's name matches the prefix
  string fullName = node->getName();
  autocompleteHelper(node->getLeft(), prefix);
  if (fullName.find(prefix) == 0)
  {                // Prefix match
    node->print(); // Print employee details
  }

  autocompleteHelper(node->getRight(), prefix);
}

// Function to search for employees with names having the same prefix
void BST::autocomplete(string prefix)
{
  if (order != "name")
  {
    return;
  }
  autocompleteHelper(root, prefix);
}
