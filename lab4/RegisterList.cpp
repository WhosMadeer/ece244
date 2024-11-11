#include "RegisterList.h"

#include <iostream>

#include "Register.h"
using namespace std;

RegisterList::RegisterList() {
  head = nullptr;
  size = 0;
}

RegisterList::~RegisterList() {
  // Delete all registers in the list
  delete head;
}

Register* RegisterList::get_head() {
  return head;
}

int RegisterList::get_size() {
  // return number of registers 
  return size;
}


Register* RegisterList::get_min_items_register() {
  // loop all registers to find the register with least number of items


  Register* p = head, * leastRegister = nullptr;
  double minItemsCount = -1;

  if (p != NULL) {
    minItemsCount = p->get_queue_list()->get_items();
    leastRegister = p;
    while (p != NULL) {
      QueueList* qp = p->get_queue_list();
      if (minItemsCount > qp->get_items()) {
        leastRegister = p;
        minItemsCount = qp->get_items();
      }
      p = p->get_next();
    }
  }

  return leastRegister;

}

Register* RegisterList::get_free_register() {
  // return the register with no customers
  // if all registers are occupied, return nullptr

  Register* p = head;

  // if (p == NULL) {
  //   return nullptr;
  // }


  while (p != NULL) {
    if (p->get_queue_list()->get_head() == NULL) {
      return p;
    }
    p = p->get_next();
  }

  return nullptr;


}

void RegisterList::enqueue(Register* newRegister) {
  // a register is placed at the end of the queue
  // if the register's list is empty, the register becomes the head
  // Assume the next of the newRegister is set to null
  // You will have to increment size 

  Register* p = head;

  if (p == NULL) {
    head = newRegister;
    size++;
    return;
  }

  while (p->get_next() != NULL) {
    p = p->get_next();
  }

  p->set_next(newRegister);
  size++;
}

bool RegisterList::foundRegister(int ID) {
  // look for a register with the given ID
  // return true if found, false otherwise
  Register* p = head;

  while (p != NULL) {
    if (p->get_ID() == ID) {
      return true;
    }
    p = p->get_next();
  }

  return false;
}

Register* RegisterList::dequeue(int ID) {
  // dequeue the register with given ID
  // return the dequeued register
  // return nullptr if register was not found

  Register* p = head, * prev = NULL;

  while (p != NULL && p->get_ID() != ID) {
    prev = p;
    p = p->get_next();
  }

  if (p == NULL) {
    return nullptr;
  }

  if (prev == NULL) {
    head = p->get_next();
  }
  else {
    prev->set_next(p->get_next());
  }

  p->set_next(NULL);
  return p;
}

Register* RegisterList::calculateMinDepartTimeRegister(double expTimeElapsed) { // * time elasped is after it is added
  // return the register with minimum time of departure of its customer
  // if all registers are free, return nullptr


  // * because p starts with head, it means that if minDepartTime is - 1, it will still return head
  Register* p = head, * leastRegister = p;
  double minDepartTime = -1;
  while (p != NULL) {
    double customerDepartTime = p->calculateDepartTime();
    if (customerDepartTime != -1 && customerDepartTime <= expTimeElapsed && (minDepartTime == -1 || minDepartTime > customerDepartTime)) { // * if the depart time is not -1, it is less than the time Elasped and its smaller than min Depart Time
      minDepartTime = customerDepartTime;
      leastRegister = p;
    }
    p = p->get_next();
  }


  // ? old code
  // if (p != NULL) {
  //   minDepartTime = p->calculateDepartTime();
  //   leastRegister = p;
  //   while (p != NULL) {
  //     if (expTimeElapsed < p->calculateDepartTime() && minDepartTime > p->calculateDepartTime()) {
  //       leastRegister = p;
  //       minDepartTime = p->calculateDepartTime();
  //     }
  //   }
  // }

  if (minDepartTime != -1) {
    return leastRegister; // * stuck returning the same register
  }
  return nullptr;

}

void RegisterList::print() {
  Register* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
