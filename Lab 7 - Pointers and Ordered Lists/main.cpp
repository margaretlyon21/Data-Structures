#include <iostream>
using namespace std;

class fullList : public exception{
  public:
    const char* message() {
      return "The list is full!";
    }
};

class emptyList : public exception{
  public:
    const char* message() {
      return "The list is empty!";
    }
};

class notFound : public exception{
  public:
    const char* message() {
      return "This item doesn't exist!";
    }
};

//Task 1 - done
const int size = 10;
template <class T>
class orderedList{
//ordered list class using an array of pointers
public:
//array of pointers of size 25
T *arr[size] = {nullptr};
int comparisons = 0;
int moves = 0;

void printlist(){
  for(int j = 0; j < size; j++){
    if(arr[j] != nullptr){
      cout << *(arr[j]) << " ";
    }
    else{
      cout << "x ";
    }
}
  cout << endl;
  cout << "Comparisons: "<< comparisons << endl;
  cout << "Moves: " << moves << endl;
}

void addItem(T item){
  if (isFull()) {
    throw fullList();
  }
  int insertionIndex = 0;
  //loop through the array
  for(int i = 0; i < size; i++){
    //if the item is less than the current item
    if (arr[i] != nullptr){
      comparisons++;
    }
    if(arr[i] == nullptr || item < *arr[i]){
      insertionIndex = i;
      break;
    }
  }
  for (int j = size - 1; j > insertionIndex; j--){
    if(arr[j-1] != nullptr){
      moves++;
    }
    arr[j] = arr[j-1];
  }
  arr[insertionIndex] = new T(item);
}

//removeItem method starts at the front of the array and removes an item in its ordered spot
void removeItem(T item){
  if (isEmpty()) {
    //throw emptyList();
    //removed so task 4 is possible
    return;
  }
  int removalIndex = -1;
  for (int i=0; i<size; i++){
    if (arr[i] != nullptr){
      comparisons++;
    }
    if (arr[i] != nullptr && *arr[i] == item){
      removalIndex = i;
      break;
    }
  }
  if (removalIndex == -1){
    //throw notFound();
    //removed so task 4 is possible
    return;
  }
  for (int j = removalIndex; j < size - 1; j++){
    if(arr[j+1] != nullptr){
      moves++;
    }
    arr[j] = arr[j+1];
  }
  arr[size-1] = nullptr;
}

//isEmpty method checks if the array is empty
bool isEmpty(){
    if(arr[0] == NULL){
      return true;
    }
    return false;
  }

//isFull method checks if the array is full
bool isFull(){
  if(arr[size - 1] != NULL){
    return true;
  }
  return false;
}

//makeEmpty method empties the array
void makeEmpty(){
  for(int i = 0; i < size; i++){
    arr[i] = NULL;
  }
}

};

//Task 2 - done
template <class T>
class derivedOne : public orderedList<T>{
public:
T *arr[size] = {nullptr};
int comparisons = 0;
int moves = 0;

void printlist(){
  for(int j = 0; j < size; j++){
    if(arr[j] != nullptr){
      cout << *(arr[j]) << " ";
    }
    else{
      cout << "x ";
    }
}
  cout << endl;
  cout << "Comparisons: "<< comparisons << endl;
  cout << "Moves: " << moves << endl;
}

// modified to begin search in middle of curret collection 
void addItem(T item){
  int lowIndex = 0;
  int highIndex = 0;
  int insertionIndex = 0;
  for (int i = 0; i < size; i++){
    if (arr[i] != nullptr){
      highIndex++;
    }
  }
  if (highIndex != 0){
    insertionIndex = (lowIndex + highIndex) / 2;
  }

  while(lowIndex < highIndex){
    if (arr[insertionIndex] != nullptr){
        comparisons++;
    }
    if(item < *arr[insertionIndex] || arr[insertionIndex] == nullptr){
      highIndex = insertionIndex;
      if (lowIndex == highIndex){
        break;
      } 
    } 
    else {
      lowIndex = insertionIndex + 1;
    }
    insertionIndex = (lowIndex + highIndex) / 2;
    }

  for(int j = size - 1; j >= insertionIndex; j--){
    if(arr[j-1] != nullptr){
      moves++;
    }
    arr[j] = arr[j-1];
  }
  arr[insertionIndex] = new T(item);
}

void removeItem(T item){
    int lowIndex = 0;
    int highIndex = 0;
    int removalIndex = 0;
    for (int i = 0; i < size; i++){
      if (arr[i] != nullptr){
        highIndex++;
      }
    }
    if (highIndex != 0){
      removalIndex = (lowIndex + highIndex) / 2;
    }

    while(lowIndex < highIndex){
      if (arr[removalIndex] != nullptr){
          comparisons++;
      }
      if (item == *arr[removalIndex]){
        break;
      }
      else if(item < *arr[removalIndex] || arr[removalIndex] == nullptr){
        highIndex = removalIndex;
      } 
      else {
        lowIndex = removalIndex + 1;
      }
      removalIndex = (lowIndex + highIndex) / 2;
      }
  if (removalIndex >=0 && removalIndex < size && arr[removalIndex] != nullptr && (*arr[removalIndex] == item)){
    for(int j = removalIndex; j < size-1; j++){
      if(arr[j+1] != nullptr){
        moves++;
      }
      arr[j] = arr[j+1];
    }
    arr[size-1] = nullptr;
  } else{
    //throw notFound();
    //removed so task 4 is possible
  }
  }
};


// Task 3:
template <class T>
class blankSpots : public orderedList<T> {
public:
T *arr[size] = {nullptr};
int moves = 0;
int comparisons = 0;

void addItem(T item){
  int elements = 0;
  int lowIndex = 0;
  int highIndex = size;
  int insertionIndex = 0;
  for (int i = 0; i < size; i++){
    if (arr[i] != nullptr){
      elements++;
    }
  }
  if (elements == 0){
    arr[0] = new T (item);
    return;
  }

  for(int i = 0; i < size; i++){
    // if the item is less than the value at this index, index becomes highIndex and we will insert the item halfway to there
    if(arr[i] != nullptr && item < *arr[i]){
      highIndex = i;
      insertionIndex = (lowIndex + highIndex) / 2;
      break;
    }
    // if the item is greater than the value at this index, index becomes lowIndex
    if(arr[i] != nullptr && item > *arr[i]){
        comparisons++;
      lowIndex = i+1;
      highIndex = size-1;
    }
  }

  if(insertionIndex == 0){
  insertionIndex = (lowIndex + highIndex) / 2;
  }
  if (arr[insertionIndex] != nullptr){
    for (int j = size-1; j > insertionIndex; j--) {
        arr[j] = arr[j - 1];
      if (arr[j-1] != nullptr){
        moves++;
      }
    }
  }
  arr[insertionIndex] = new T(item);
}

  void removeItem(T item) {
    for (int i = 0; i < size; i++){
      if (arr[i] != nullptr && *arr[i] == item){
        comparisons++;
        delete arr[i];
        break;
      }
    }
  }
  void printlist(){
  for(int j = 0; j < size; j++){
    if(arr[j] != nullptr){
      cout << *(arr[j]) << " ";
    }
    else{
      cout << "x ";
    }
}
    cout << endl;
  cout << "Comparisons: "<< comparisons << endl;
  cout << "Moves: " << moves << endl;
}
};


//Task 4
int main(){
  //a loop to print the results of the add array fucntion
  cout << "Press 1 for user test\nPress 2 for automated test\nPress 3 to quit\n";
  int testchoice;
  cin >> testchoice;
  if (testchoice == 1){
    orderedList<int> order;
    derivedOne<int> binary;
    blankSpots<int> blank;
  while(true){
    cout << "Press 1 to add an item to the list and display current state\nPress 2 to remove an item from the list and display current state\nPress 3 to quit\n";
    int what;
    cin >> what;

    if (what == 1){
    //ask the user what item they want to add
    cout << "What item do you want to add? ";
    int item;
    cin >> item;
    order.addItem(item);
    binary.addItem(item);
    blank.addItem(item);
    //print list 
    cout << "Orignial Ordered List:\n";
    order.printlist();
    cout << "Binary Sorted List:\n";
    binary.printlist();
    cout << "Blank Space Sorted List:\n";
    blank.printlist();  
  }
    if (what == 2){
      cout << "What item do you want to remove? ";
      int item;
      cin >> item;
      //remove the items
      order.removeItem(item);
      binary.removeItem(item);
      blank.removeItem(item);
      //print new list
      cout << "Orignial Ordered List:\n";
      order.printlist();
      cout << "Binary Sorted List:\n";
      binary.printlist();
      cout << "Blank Space Sorted List:\n";
      blank.printlist();  

    }
    if (what ==3){
      break;
    }
  }
  }
  if (testchoice ==2){
    //instantiate each type of list
    int orderComparisons = 0;
    int orderMoves = 0; 
    int binaryComparisons= 0;
    int binaryMoves= 0;
    int blankComparisons = 0;
    int blankMoves = 0;
    for (int i = 0; i <100; i++){
        orderedList<int> order;
        derivedOne<int> binary;
        blankSpots<int> blank;
        //add random elements to the array
        for (int i = 0; i < 15; i++){
            int newitem = (rand() % 100) + 1;
        if (i % 3 != 0 && i % 5 != 0){
            order.addItem(newitem);
            binary.addItem(newitem);
            blank.addItem(newitem);
        }
        else{
            order.removeItem(newitem);
            binary.removeItem(newitem);
            blank.removeItem(newitem);
        }
        }
        orderComparisons += order.comparisons;
        binaryComparisons += binary.comparisons;
        blankComparisons += blank.comparisons;
        orderMoves += order.moves;
        binaryMoves += binary.moves;
        blankMoves += blank.moves;
    }
        cout << "Averages over 100 trials: " << endl;
        cout << "Regular ordered list: " << endl;
        cout << "Comparisons: " << orderComparisons / 100 << endl;
        cout << "Moves: " << orderMoves / 100 << endl;


        cout << "Binary sorted list: " << endl;
        cout << "Comparisons: " << binaryComparisons / 100 << endl;
        cout << "Moves: " << binaryMoves / 100 << endl;

        cout << "Blank Space Sorted list: " << endl;
        cout << "Comparisons: " << blankComparisons / 100 << endl;
        cout << "Moves: " << blankMoves / 100 << endl;

  }
};
