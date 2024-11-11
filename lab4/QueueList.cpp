#include "QueueList.h"

#include "Customer.h"

QueueList::QueueList() {
  head = nullptr;
}

QueueList::QueueList(Customer* customer) {
  head = customer;
}

QueueList::~QueueList() {
  delete head;
}

Customer* QueueList::get_head() {
  return head;
}

void QueueList::enqueue(Customer* customer) {
  // a customer is placed at the end of the queue
  // if the queue is empty, the customer becomes the head

  Customer* p = head;

  if (p == NULL) {
    head = customer;
    return;
  }

  while (p != NULL && p->get_next() != NULL) {
    p = p->get_next();
  }

  p->set_next(customer);
}

Customer* QueueList::dequeue() {
  // remove a customer from the head of the queue 
  // and return a pointer to it

  if (head == NULL) {
    return nullptr;
  }

  Customer* p = head;
  head = p->get_next();

  p->set_next(NULL);
  return p;


}

int QueueList::get_items() {
  // count total number of items each customer in the queue has
  int count = 0;
  Customer* p = head;

  while (p != NULL) {
    count += p->get_numOfItems();
    p = p->get_next();
  }

  return count;
}

void QueueList::print() {
  // print customers in a queue
  Customer* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
