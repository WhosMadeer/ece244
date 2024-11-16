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
  if (n->getID() == newEmployee->getID()) {
    // std::cout << "ID already exists" << endl;
    return;
  }
  else if (newEmployee->getID() < n->getID()) {
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
    std::cout << n->getID() << " " << n->getName() << " " << n->getAge() << " " << n->getSalary() << "";
    printInOrderHelper(n->getRight());
  }
}

// void printInOrderByIDHelper(Employee* n) {
//   if (n != NULL) {
//     printInOrderByIDHelper(n->getLeft());
//     std::cout << n->getID() << " " << n->getName() << " " << n->getAge() << " " << n->getSalary() << "";
//     printInOrderByIDHelper(n->getRight());
//   }
// }


// void printInOrderByAgeHelper(Employee* n) {
//   if (n != NULL) {
//     printInOrderByIDHelper(n->getLeft());
//     std::cout << n->getID() << " " << n->getName() << " " << n->getAge() << " " << n->getSalary() << "";
//     printInOrderByIDHelper(n->getRight());
//   }
// }

void BST::printInOrder() {
  // print the Employees in the tree according its order
  // Doesn't print anything if nothing is found

  Employee* n = root;

  if (root == NULL) {
    return;
  }
  else {
    printInOrderHelper(n);
    // if (order == "name") {
    //   printInOrderByIDHelper(n);
    //   return;
    // }

    // if (order == "ID") {
    //   printInOrderByIDHelper(n);
    //   return;
    // }

    // if (order == "age") {
    //   printInOrderByIDHelper(n);
    //   return;
    // }
  }
}

Employee* searchIDHelper(int ID, Employee* n) {
  if (n == NULL) {
    return NULL;
  }
  else if (n->getID() == ID) {
    return n;
  }
  else if (n->getID() > ID) {
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


// void searchAgeHelper(double lowAge, double highAge, Employee* n, Employee* root) {
//   if (n == NULL) {
//     return;
//   }
//   // else if (n->getLeft() == NULL) {
//   //   searchAgeHelper(lowAge, highAge, root->getRight(), root);
//   // }

//   // if (n->getAge() >= lowAge) {
//   //   n->print();
//   // }
//   // if (n->getAge() <= highAge) {
//   //   n->print();
//   // }

//   // searchAgeHelper(lowAge, highAge, n->getLeft(), root);
//   // searchAgeHelper(lowAge, highAge, n->getRight(), root);
//   // else if (n->getAge() >= lowAge) {
//   //   n->print();
//   //   return searchAgeHelper(lowAge, highAge, n->getLeft(), root);
//   // }
//   // else if (n->getAge() <= highAge) {
//   //   n->print();
//   //   return searchAgeHelper(lowAge, highAge, n->getRight(), root);
//   // }
// }


void searchAgeHelper(double lowAge, double highAge, Employee* n) {
  if (n == NULL) {
    return;
  }
  searchAgeHelper(lowAge, highAge, n->getLeft());
  if (n->getAge() >= lowAge && n->getAge() <= highAge) {
    n->print();
  }


  searchAgeHelper(lowAge, highAge, n->getRight());
  if (n->getAge() >= lowAge && n->getAge() <= highAge) {
    n->print();
  }


  // if (n->getAge() >= lowAge) {
  //   n->print();
  // }
  // if (n->getAge() <= highAge) {
  //   n->print();
  // }

  // searchAgeHelper(lowAge, highAge, n->getLeft(), root);
  // searchAgeHelper(lowAge, highAge, n->getRight(), root);
  // else if (n->getAge() >= lowAge) {
  //   n->print();
  //   return searchAgeHelper(lowAge, highAge, n->getLeft(), root);
  // }
  // else if (n->getAge() <= highAge) {
  //   n->print();
  //   return searchAgeHelper(lowAge, highAge, n->getRight(), root);
  // }
}


void BST::searchAgeRange(double lowAge, double highAge) {
  // search for employees within the age range
  // Doesn't print anything if nothing is found

  searchAgeHelper(lowAge, highAge, root);
}


Employee* searchNameHelper(string name, Employee* n, string prefix) {
  if (n == NULL) {
    return NULL;
  }
  else if (n->getName().compare(prefix) < 0) {

  }
  else if (n->getName().compare(prefix) > 0) {

  }
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

  if (root != NULL) {
    return;
  }


}