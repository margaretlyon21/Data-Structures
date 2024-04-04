#include <iostream>
using namespace std;
#include <stdexcept>

class notFound : public std::exception{
  public:
    const char* message() {
      return "Item Not Found";
    }
};

class Item{
private:
  int sku;
  string Description;
  float Price;
  string UOM; 
  int QuantityOnHand;
  int LeadTime;
public:
//Constructor 
  Item(int sku = 0, string Description = "", float Price = 0, string UOM = "", int QuantityOnHand = 0, int Lead = 0) : sku(sku), Description(Description), Price(Price), UOM(UOM), QuantityOnHand(QuantityOnHand), LeadTime(Lead){}

//concatenates the stock keeping number and the description
string GetPartInfo(){
  return to_string(sku) + " " + Description;
}

//gets private member variable price
float GetPrice(){
  return Price;
}

//checks if the item is in stock
bool InStock(){
  return (QuantityOnHand > 0);
}

//function to get the day of the year, x/365
int DateToDays(int month, int day) {
    // Array to store the number of days in each month
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Initialize total days
    int totalDays = 0;

    // Add days for previous months
    for (int i = 0; i < month - 1; ++i) {
        totalDays += daysInMonth[i];
    }

    // Add days for the current month
    totalDays += day;

    return totalDays;
}

//checks if item is available by date
bool IsAvailable(int curDay, int curMonth, int needDay, int needMonth){
  if (QuantityOnHand > 0){
    return true;
  }
  else{
    return (DateToDays(curMonth, curDay) + LeadTime <= DateToDays(needMonth, needDay));    
  }
}

//overloaded > operator
bool operator>(Item& other){
  return sku > other.sku;
}
//overloaded < operator
bool operator<(Item& other){
  return sku < other.sku;
}
//overloaded = operator 
bool operator==(Item& other){
  return sku == other.sku;
}
//overloaded != operator 
bool operator!=(Item& other){
  return sku != other.sku;
}


void printItem(){
  cout << "SKU: " << sku << endl;
  cout << "Description: " << Description << endl;
  cout << "Price: " << Price << endl;
  cout << "UOM: " << UOM << endl;
  cout << "QuantityOnHand: " << QuantityOnHand << endl;
  cout << "LeadTime: " << LeadTime << endl;
}

void printKeyInfo(){
  cout << "__________________" << endl;
  cout << "|SKU: " << sku << endl;
  cout << "|Description: " << Description << endl;
  cout << "|Price: " << Price << endl;
  cout << "__________________" << endl;
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

  T getItem(T val) {
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

  bool isInList(T val) {
    if (head == nullptr) {
      return false;
    }
    if (head->data == val) {
      return true;
    }

    Node<T>* temp = head;
    while (temp->data != val && temp->next != nullptr) {
      temp = temp->next;
    }
    if (temp->data == val) {
      return true;
    }
    return false;
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

  T seeNext() {
    if (head == nullptr) {
      cout << "List is empty." << endl;
    }
    if (current == nullptr) {
      reset();
      cout << "End of list reached. Starting over." << endl;
    }
    T temp = current->data;
    current = current->next;
    return temp;
  }

  T seePrev() {
    if (head == nullptr) {
      cout << "List is empty." << endl;
    }
    if (current == nullptr) {
        reset();
        cout << "Beginning of list reached. Starting over." << endl;
        return current->data;
    }
    if (current->prev == nullptr){
      cout << "Beginning of list reached." << endl;
      return current->data;
    }
    current = current->prev;
    return current->data;
  }

  // Finds an item at a location in the list and returns the item without removing it 
  T seeAt(int position) {
    if(position < 1){ //check if valid loaction
      throw notFound();
    }
    Node<T>* temp = head; // loop through list until position is reached
    for (int i = 1; i < position && temp != nullptr; i++){
      temp = temp->next;
    }
    if (temp == nullptr){
      throw notFound();
    }
    current = temp->next; //update the current loaction
    return temp->data; //return pointer to data
  }

  void reset() {
    current = head;
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


int main() {
  dbLL<Item> list;
  bool cont = true;
  while(cont){
  cout << "Select a function to test: " << endl;
  cout << "1. Add Item. 2. Get Item. 3. Is in List. 4. Is Empty. 5. Size. 6. See Next. 7. See Prev. 8. See At. 9. Reset. 10. print list" << endl;
  int choice;
  cin >> choice;
  switch(choice){
    //add
    case 1: {
      cout << "Adding Item... " << endl;
      cout << "Enter SKU: " << endl;
      int sku;
      cin >> sku;
      cout << "Enter Description: " << endl;
      string description;
      cin.ignore();
      getline(cin, description); // Use getline to read entire line  
      cout << "Enter Price: " << endl;
      float price;
      cin >> price;
      cout << "Enter UOM: " << endl;
      string uom;
      cin.ignore();
      getline(cin, uom); // Use getline to read entire line
      cout << "Enter Lead Time: " << endl;
      int lead;
      cin >> lead;
      cout << "Enter Quantity On Hand: " << endl;
      int quantity;
      cin >> quantity;
      Item myItem(sku, description, price, uom, quantity, lead);
      list.addItem(myItem);
      break;
    }
    //get
    case 2: {
      cout << "Getting item..." << endl;
      cout << "Enter SKU: " << endl;
      int sku;
      cin >> sku;
      Item myItem = list.getItem(sku);
      myItem.printItem();
      break;
    }
    //is in list
    case 3:{
      cout << "Is in list..." << endl;
      cout << "Enter SKU: " << endl;
      int sku;
      cin >> sku;
      if (list.isInList(sku)){
        cout << "Item is in list" << endl;
      }
      else{
        cout << "Item is not in list" << endl;
      }
      
      break;
    }
    //is empty
    case 4:{
      cout << "Checking if empty..." << endl;
      if (list.isEmpty()){
        cout << "List is empty" << endl;
      }
      else{
        cout << "List is not empty" << endl;
      }
      break;
    }
    //size
    case 5:{
      cout << "Getting the number of items in the list..." << endl;
      cout << "There are "<< list.size() << " items in the list" << endl;
      break;
    }
    //see next
    case 6:{
      cout << "Seeing the next item..." << endl;
      Item seeItem = list.seeNext();
      seeItem.printItem();
      break;
    }
    //see prev
    case 7:{
      cout << "Seeing the previous item..." << endl;
      Item seeItem = list.seePrev();
      seeItem.printItem();
      break;
    }
    //see at
    case 8:{
      cout << "Seeing the item at a location..." << endl;
      cout << "Enter location to find item at: " << endl;
      int location;
      cin >> location;
      Item seeItem = list.seeAt(location);
      seeItem.printItem();
      break;
    }
    //reset
    case 9:{
      cout << "Resetting the current position..." << endl;
      list.reset();
      break;
    }
    //exit
    case 10:{
      cout << "Printing list..." << endl;
      list.printList(list.head);
      break;
    }
  }
  }
  
  
}