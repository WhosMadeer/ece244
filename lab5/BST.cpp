//
//  BST.cpp
//  Lab 5 Search Through A Database
//
//  Created by Author Name, Date
#include "BST.h"

#include "Employee.h"

BST::BST(string order_) {
  root = NULL;
  order = order_; // name or ID or age
}

BST::~BST() {
  delete root;
}
void insertByIDHelper(Employee* newEmployee, Employee* n) {
  // if (n->getID() == newEmployee->getID()) {
  //   // std::cout << "ID already exists" << endl;
  //   return;
  // }
  if (newEmployee->getID() < n->getID()) {
    // std::cout << "checking left" << endl;
    if (n->getLeft() == NULL) {
      // std::cout << "setting left" << endl;
      n->setLeft(newEmployee);
    }
    else {
      // std::cout << "reclusively going left" << endl;
      insertByIDHelper(newEmployee, n->getLeft());
    }
  }
  else {
    // std::cout << "checking right" << endl;
    if (n->getRight() == NULL) {
      // std::cout << "setting right" << endl;
      n->setRight(newEmployee);
    }
    else {
      // std::cout << "reclusively going right" << endl;
      insertByIDHelper(newEmployee, n->getRight());
    }
  }
}

void insertByAgeHelper(Employee* newEmployee, Employee* n) {
  if (newEmployee->getAge() <= n->getAge()) {
    // std::cout << "checking left" << endl;
    if (n->getLeft() == NULL) {
      // std::cout << "setting left" << endl;

      n->setLeft(newEmployee);
    }
    else {
      // std::cout << "reclusively going left" << endl;

      insertByAgeHelper(newEmployee, n->getLeft());
    }
  }
  else {
    // std::cout << "checking right" << endl;

    if (n->getRight() == NULL) {
      // std::cout << "setting right" << endl;

      n->setRight(newEmployee);
    }
    else {
      // std::cout << "reclusively going right" << endl;

      insertByAgeHelper(newEmployee, n->getRight());
    }
  }
}

void insertByNameHelper(Employee* newEmployee, Employee* n) {
  if (n->getName() == newEmployee->getName()) {
    return; // Assuming no duplicates allowed
  }
  else if (newEmployee->getName().compare(n->getName()) < 0) {
    // std::cout << "checking left" << endl;

    if (n->getLeft() == NULL) {
      // std::cout << "setting left" << endl;

      n->setLeft(newEmployee);

    }
    else {
      // std::cout << "reclusively going left" << endl;

      insertByNameHelper(newEmployee, n->getLeft());
    }
  }
  else {
    // std::cout << "checking right" << endl;

    if (n->getRight() == NULL) {
      // std::cout << "setting right" << endl;

      n->setRight(newEmployee);
    }
    else {
      // std::cout << "reclusively going right" << endl;

      insertByNameHelper(newEmployee, n->getRight());
    }
  }
}

void BST::insert(Employee* newEmployee) {
  // newEmployee is a pointer to a dynamically allocated Employee. Insert it
  // according to the value of "order" of the binary search tree.


  if (root == NULL) {
    root = newEmployee;
    return;
  }
  else {
    if (order == "name") {
      insertByNameHelper(newEmployee, root);
      return;
    }

    if (order == "ID") {
      insertByIDHelper(newEmployee, root);
      return;
    }

    if (order == "age") {
      insertByAgeHelper(newEmployee, root);
      return;
    }
  }
}


void printInOrderHelper(Employee* n) {
  if (n != NULL) {
    printInOrderHelper(n->getLeft());
    n->print();
    printInOrderHelper(n->getRight());
  }
}

void BST::printInOrder() {
  // print the Employees in the tree according its order
  // Doesn't print anything if nothing is found

  Employee* n = root;

  if (root == NULL) {
    return;
  }
  else {
    printInOrderHelper(n);
  }
}

Employee* searchIDHelper(int ID, Employee* n) {
  if (n == NULL) {
    return NULL;
  }

  if (n->getID() == ID) {
    return n;
  }

  if (ID < n->getID()) {
    return searchIDHelper(ID, n->getLeft());
  }
  else {
    return searchIDHelper(ID, n->getRight());
  }

}

Employee* BST::searchID(int ID) {
  // search for an employee with a particular ID
  // If ID doesn't exist in the function. Instead it should return NULL, and the printing should be taken care of in the main.cpp.
  return searchIDHelper(ID, root);
}


void searchAgeHelper(double lowAge, double highAge, Employee* n) {
  if (n == NULL) {
    return;
  }

  if (n->getAge() >= lowAge) {
    searchAgeHelper(lowAge, highAge, n->getLeft());
  }

  if (n->getAge() >= lowAge && n->getAge() <= highAge) {
    n->print();
  }

  if (n->getAge() <= highAge) {
    searchAgeHelper(lowAge, highAge, n->getRight());
  }

}


void BST::searchAgeRange(double lowAge, double highAge) {
  // search for employees within the age range
  // Doesn't print anything if nothing is found

  searchAgeHelper(lowAge, highAge, root);
}


void searchNameHelper(Employee* n, string prefix) {
  if (n == NULL) {
    return;
  }
  // cout << n->getName().substr(0, prefix.length()) << endl;
  if (n->getName().substr(0, prefix.length()) == prefix) {
    // cout << "substring matches" << endl;

    n->print();

  }

  searchNameHelper(n->getLeft(), prefix);
  searchNameHelper(n->getRight(), prefix);
  // else if (n->getName().compare(prefix) > 0) {

  // }
  // else if (n->getName().compare(prefix) < 0) {

  // }
  // else if (n->getName().compare(prefix) > 0) {

  // }
  // else if (n->getName() == name) {
  //   return n;
  // }
  // else if (n->getName() > name) {
  //   return searchNameHelper(name, n->getLeft());
  // }
  // else {
  //   return searchNameHelper(name, n->getRight());
  // }
}

void BST::autocomplete(string prefix) {
  // Search for employees with names having the same prefix in the firstName +
  // secondName If available, it prints them in order of their names in
  // alphabetical order
  // Doesn't print anything if nothing is found

  if (root == NULL) {
    return;
  }

  searchNameHelper(root, prefix);


}