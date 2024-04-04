#include <iostream>
using namespace std;
#include <stdexcept>

//throw not found 
class notFound : public std::exception{
  public:
    const char* message() {
      return "Item Not Found";
    }
};

template <typename T>
class Node{
public:
  Node(T value) : data(value), prev(nullptr), next(nullptr) {}
  T data;
  Node* prev, *next;
  Node* head;
};

template <typename T>
class dbLL{
public:
  int spotsChecked = 0;
  T data;
  Node<T>* prev;
  Node<T>* next;
  Node<T>* head;
  Node<T>* current;

  // Constructor
  dbLL() : next(nullptr), head(nullptr), current(nullptr) {}

  // Functions
void addItem(T val) {
  if (head == nullptr) {
    head = new Node<T>(val);
    head->prev = nullptr; // Set prev to nullptr for the first node
    return;
  }

  Node<T>* newNode = new Node<T>(val);

  if (val < head->data) {
    // Add to the beginning
    newNode->next = head;
    head->prev = newNode; // Set prev of existing head to new node
    head = newNode;
    newNode->prev = nullptr; // Set prev to nullptr for the new head
    return;
  }

  Node<T>* temp = head;
  while (temp->next != nullptr && temp->next->data < val) {
    temp = temp->next;
  }

  // Add in the middle or at the end
  newNode->next = temp->next;
  if (temp->next != nullptr) {
    temp->next->prev = newNode; // Set prev of next node to new node
  }
  temp->next = newNode;
  newNode->prev = temp; // Set prev of new node to current node
  return;
}

  T removeItem(T val) {
    if (head == nullptr) { // empty
      cout << "List is empty" << endl;
    }
    if (head->data == val) { // front
      Node<T>*old = head;
      T temp = head->data;

      head = head->next;

      delete old;
      return temp;
    }
    Node<T>* temp = head;
    while (temp->next != nullptr && temp->next->data != val) { // can we go to next, and should we go to next?
      temp = temp->next;
    }
    if (temp->next == nullptr) {
      throw notFound();
    }
    T retVal = temp->next->data;
    Node<T>* old = temp->next;
    temp->next = temp->next->next;

    delete old;

    return retVal;
  }

  T findItem(T val) {
    if (head == nullptr) {
      throw notFound();
    }
    if (head->data == val) {
      return head->data;
    }

    Node<T>* temp = head;
    while (temp->data != val && temp->next != nullptr) {
      spotsChecked++;
      temp = temp->next;
    }
    if (temp->data == val) {
      spotsChecked++;
      return temp->data;
    }
    throw notFound();
  }

  bool isEmpty() {
    return head == nullptr;
  }

  int size() {
    int count = 0;
    Node<T>* current = head;
    while (current != nullptr){
      count++;
      current = current->next;
    }
    return count;
  }

void printList(Node<T>* head) {
    Node<T>* current = head;
    while (current != nullptr) {
        current->data.printKeyInfo();
        current = current->next;
    }
    cout << endl;
}

  // Destructor
  ~dbLL() {}
};