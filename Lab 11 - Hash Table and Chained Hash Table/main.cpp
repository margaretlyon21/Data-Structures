#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>
using namespace std;
#include "LinkedList.cpp"

class fullTable : public std::exception{
  public:
    const char* message() {
      return "Hash Table is Full";
    }
};

const int size = 100;

//a one dimensional hash table with linear probing
template <class T>
class oneHash{
  public:
    long int spotsChecked;
    T table[size];
    bool removed[size];

  //constructor
  oneHash(){
    //sets all spots in the table to 0 and all removed to false
    for(int i = 0; i < size; i++){
      table[i] = T();
      removed[i] = false;
    }
  };

  //destructor
  ~oneHash(){};

  //isFull
  bool isFull(){
    //checks if each spot in the table if full
    for (int i = 0; i < size; i++){
      if (table[i].sku == ""){
        return false;
      }
    }
    return true;
  }

  //isEmpty
  bool isEmpty(){
    //checls if each spot in the table is empty
    for (int i = 0; i < size; i++){
      if (table[i].sku != ""){
        return false;
      }
    }
    return true;
  }

  //hash function 
  int Hash(T key){
    // gets the sum of all the ascii characters in the sku 
    int sum = 0;
    for (int i = 0; i < key.sku.length(); i++){
      sum += static_cast<int>(key.sku[i]);
    }
    return sum % size;
  }

  //insert
  void addItem(T* val){
    //checks if the table is full
    if (isFull()){
      throw fullTable();
    }
    int index = Hash(*val);
    //if the hash spot is empty, put the value here 
      if (table[index].sku == "" ){     
        cout << "Index: " << index << endl;
      table[index] = *val;
      return;
    }
    int initialIndex = index;
    //the hash spot was not empty, so we will do linear probing
    while (table[index].sku != ""){
      //increment index to the right 
      index = (index+1) % size;		
      //If we wrapped all the way back around and didnt find an empty spot the table is full
      if (index == initialIndex){
        cout << "Hash table is full";
      }
    }
    //put the value in the found empty spot
    cout << "Index: " << index << endl;

    table[index] = *val;
    removed[index] = false; 
  }

  //find
  T* findItem(T* key){
    //check if the table is empty 
    if (isEmpty()){
      cout << "The table is empty.";
    }
    int index = Hash(*key);
    int initialIndex = index;
    //if the hash spot does not contain the key, and if it is not empty, and if something was not removed from the spot
    while (table[index] != *key && table[index].sku != "" && removed[index] == false){
      spotsChecked++;
      //increment the index to the right one 
      index = (index +1) % size;
      //if we wrapped all the way around and didnt find the key, then the key is not in the table
      if (index == initialIndex){
        break;
      }
    }
    //if the key is at the computed index, we found it 
    if (table[index].sku == key->sku){
      spotsChecked++;
      return &table[index];
    }
    throw notFound();
  }

  //remove
  T* RemoveItem(T* key){
    //check if the table is empty
    if (isEmpty()){
      cout << "The table is empty.";
    }
    int index = Hash(*key);
    int initialIndex = index;
    //if the value is not at the hash spot, and the spot is not empty, and nothing was removed from the spot
    while (table[index] != *key && table[index].sku != "" && removed[index] == false){
      //increment the index to the right one
      index = (index + 1) % size;
      //if we wrapped all the way around and didnt find the key, then the key is not in the table
      if (index == initialIndex){
        break;
      }
    }
    //if the value is at the computed index, we found it
    if (table[index] == *key){
      //remove the value from the table
      T* temp = &table[index];
      table[index] = T(); 
      removed[index] = true;
      //return the removed value
      return temp;
    }
    throw notFound();
  }

  //print
  void print(){
    //loop through the table and print the keys and corresponding values
    for (int i = 0; i < size; i++){
      if (table[i] != 0){
        std::cout << "Key = " << i << "  Value = " << table[i].printItem() << std::endl;
      }
      else{
        //if there is not vlaue at that spot, just print the key
        cout << "Key = " << i << endl;
      }
    }
  }

  //getLength gets hte number of items in the table 
  int getLength(){
    int count = 0;
    for (int i=0; i < size; i++){
      if (table[i].sku != ""){
        count++;
      }
    }
    return count;
  }
};


//the item class to be added to the hash table 
class Item{
  public:
    string sku;
    string Description;
    float Price;
    string UOM; 
    int QuantityOnHand;
    int LeadTime;
  public:
  //Constructor 
    Item(string sku = "", string Description = "", float Price = 0, string UOM = "", int QuantityOnHand = 0, int Lead = 0) : sku(sku), Description(Description), Price(Price), UOM(UOM), QuantityOnHand(QuantityOnHand), LeadTime(Lead){}
  //concatenates the stock keeping number and the description
  string GetPartInfo(){
    return sku + " " + Description;
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

// Task 4
template <class T>
class chainedHash : public oneHash<Item> {
public:
  Node<Item>* prev;
  Node<Item>* next;
  Node<Item>* head;
  Node<Item>* current;

  dbLL<T> data[size];

  void insert (T inVal){
    int h = Hash(inVal);
    //check if data[h] == null
    data[h].addItem(inVal);
  }

  T remove(T key){
    return data[Hash(key)].removeItem(key) ; 
    //we can call remove from the linked list class
  }

  T Find(T key){
    return data[Hash(key)].findItem(key);
    //we can call find from the linked list class 
  }

  int getLength(){
    int count = 0;
    for (int i=0; i < size; i++){
      if (!data[i].isEmpty()){
        count += data[i].size();
      }
    }
    return count;
  }

};

//gets a random string of 4 characters 
string randomString() {
  string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  const int length = 4;
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0, characters.size() - 1);
  string result;
  for (int i = 0; i < length; ++i) {
    result += characters[dis(gen)];
  }
  return result;
}

int main() {
  oneHash<Item> myHash;
  chainedHash<Item> myChain;
  while(true){
    //I/O for main menu
    cout << "Main Menu" << endl;
    cout << "1. User Test" << endl;
    cout << "2. Automated Test" << endl;
    cout << "3. Exit" << endl;
    int testType;
    cin >> testType;
    
   //asks the user which type they would like to test 
    int which;
    if (testType == 1){
    cout << "Do you want to test... " << endl;
    cout << "1. One Dimensional Hash Table" << endl;
    cout << "2. Chained Hash Table" << endl;
    cout << "3. Main Menu" << endl;
    cin >> which;
    }

    //user tests
    if (testType == 1 && which != 3){
      //user tests 
      bool cont = true;
      while(cont){
      cout << "Select a function to test: " << endl;
      cout << "1. Add Item. 2. Find Item. 3. Remove Item. 4. Get Length 5. Exit "<< endl;
      int choice;
      cin >> choice;
      switch(choice){
        //add item 
        case 1: {
          cout << "Adding Item... " << endl;
          cout << "Enter SKU: " << endl;
          string sku;
          cin.ignore();
          getline(cin,sku);
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
          if (which == 1){
            myHash.addItem(&myItem);
          }
          if (which == 2){
            myChain.insert(myItem);
          }
          break;
        }
        //Find item
        case 2: {
          cout << "Enter SKU: " << endl;
          string sku;
          cin >> sku;
          try {
              if (which ==1){
                Item myItem(sku); 
                myHash.findItem(&myItem);
                myItem.printItem();
                cout << "Item was found at index: " << myChain.Hash(myItem) << endl;
              }
              if (which == 2){
                Item myItem = myChain.Find(sku);
                myItem.printItem();
                cout << "Item was found at index: " << myChain.Hash(myItem) << endl;
              }
              } catch (const notFound& e) {
                  cout << "Item was not found." << endl;
              }
              break;
        }
        //remove an item from the list 
        case 3:{
          cout << "Enter SKU of item you would like to remove " << endl;
          string input;
          cin >> input;
          Item myItem;
          myItem.sku = input;
          try {
            if (which == 1){
              myHash.RemoveItem(&myItem);
              cout << "Item was removed from index " << myHash.Hash(myItem) << endl;
            }
            if (which == 2){
              myChain.remove(myItem);
              cout << "Item was removed from index " << myChain.Hash(myItem) << endl;

            }
          } catch (const notFound& e) {
              cout << "Item was not found." << endl;
          }
          break;
        }
        //Get length
        case 4:{
          if (which == 1){
            cout << "The length of the table is " << myHash.getLength() << endl;
          }
          if (which ==2 ){
            cout << "The length of the chained table is " << myChain.getLength() << endl;
          }
          break;
        }
        //Exit
        case 5:{
          cont = false;
          break;
        }
      }
    }
  }
    //automated tests
    if (testType == 2){
      //inserts 50 random strings into the hash table
      Item skus[50];
      for (int i=0; i < 50; i++){
        string sku = randomString();
        Item myItem(sku);
        cout << "Inserting " << myItem.sku << endl;
        myHash.addItem(&myItem);
        myChain.insert(myItem);
        skus[i] = myItem;
      }
      //call findItem on each item in the hash table
      for (int i=0; i < 50; i++){
        try{
          Item myItem(skus[i].sku);
          myHash.findItem(&myItem);
          Item myItem2 = myChain.Find(skus[i].sku);
        } catch (const notFound& e) {
            cout << "Item was not found." << endl;
        }
      }
      cout << "Linear Probing: " << myHash.spotsChecked << " comparisons" << endl;
      int totalSpotsChecked = 0;
      for (int i = 0; i < size; i++) {
          totalSpotsChecked += myChain.data[i].spotsChecked;
      }
      cout << "Chaining: " << totalSpotsChecked << " comparisons" << endl;
  
    }
    //exit
    if (testType == 3){
      break;
    }
  }
}