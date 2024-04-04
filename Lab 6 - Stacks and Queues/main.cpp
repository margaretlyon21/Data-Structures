#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class stackOverflow : public exception{
  public:
    const char* message() {
      return "Stack Overflow";
    }

};
class stackUnderflow : public exception{
  public:
    const char* message() {
      return "Stack Undeflow";
    }
};

class queueOverflow : public exception{
  public:
    const char* message() {
      return "Queue Overflow";
    }

};
class queueUnderflow : public exception{
  public:
    const char* message() {
      return "Queue Undeflow";
    }
};


template <class T>
class Stack {
private:
  int size;
  T** data;
  int index;
public:
  //constructor:
  Stack(int stackSize) : size(stackSize), index(0) {
    data = new T*[size];
  }
  //Destructor
  ~Stack(){
    delete[] data;
  }

  //Pushes an element to the top of the stack
  void Push(T *input){
    if(isFull()){
      throw stackOverflow();
    }
    data[index++] = input;
  }

  //Pops an element from the top of the stack
  T* Pop(){
    if (isEmpty()){
      throw stackUnderflow();
    }
    return data[--index];
    
    }

  //Checks if stack is full
  bool isFull(){
    return index >= size;
  }
  //Checks if stack is empty
  bool isEmpty(){
    return index <= 0;
  }

  //Returns element at top of stack
  T* top(){
    if (isEmpty()){
      throw stackUnderflow();
    }
    return data[index - 1];
  }

  //Returns size of stack
  int length(){
    return index;
  }

  //Empties the stack
  void empty(){
    while (!isEmpty()){
      Pop();
    }
  }
};

template <class T>
class Queue {
private:
  int size;
  T** data;
  int index;
public:
  // constructor
  Queue(int queueSize) : size(queueSize), index(0) {
    data = new T*[size];
  }
  void enqueue(T* item) {
    if (isFull()){
      throw queueOverflow();
    }
    data[index] = item;
    index++;
  }
  T* dequeue() {
    if (isEmpty()){
      throw queueUnderflow();
    }
    T* temp = data[0];
    for(int i = 1; i <= index - 1; i++){
      data[i-1] = data[i];
    }
    index--;
    return temp;
  }
  T* peek() {
    return data[0];
  }
  int length() {
    return index;
  }
  void makeEmpty() {
    index = 0;

  }

  bool isEmpty() {
    return index == 0;
  }
  bool isFull() {
    return index == size;
  }
};

void ReverseString(string myString){
  string finalString;
  
  //stringstream seperates words in string
  istringstream iss(myString);
  string word;

  //declares a stack and a queue of length of the string
  Stack<char> myStack(myString.length());
  Queue<char> myQueue(myString.length());

  //First step - splits string into words
  while (iss >> word){
    try{
      //second step - adds characters in a word to the stack
      for (char ch : word){
        myStack.Push(new char(ch));
      }
      //Third step - removes characters in a word from the stack and adds the now reversed characters to the queue
      while (!myStack.isEmpty()){
        char* charPtr = myStack.Pop();
        myQueue.enqueue(charPtr);
      }
      //fourth step - removes characters in a word from the queue and adds the now reversed characters to the final string
      while (!myQueue.isEmpty()){
        char* charPtr = myQueue.dequeue();
        finalString +=  *charPtr;
      }
      //adds a space in between words
      finalString += " ";
      //catches all possible errors
    } catch (stackUnderflow& e){
      cout << e.message() << endl;
    } catch (queueUnderflow& e){
      cout << e.message() << endl;
    } catch (stackOverflow& e){
      cout << e.message() << endl;
    } catch (queueOverflow& e){
      cout << e.message() << endl;
    }
  }
  //prints the reversed string
  cout << finalString << "\n";

}
int main() {
  char again;
  int choice;
  string fileName;
  ifstream inputFile;

  do {
    cout << "Choose an option:\n" << "1. File name:\n" << "2. User input:\n" << "3. Exit\n";
    cin >> choice;
    
    //file contents
    if (choice == 1) {
        //gets name of the file and opens file
        cout << "Enter the file name: " << endl;
        cin >> fileName;
        ifstream yourFile(fileName,ios::in);
        if (!yourFile.is_open()){
          cout << "Invalid file name or file could not be opened." << endl;
        }
        //reads the line of the file 
        string myString;
        getline(yourFile, myString);
        //calls reverseString to reverse the string
        ReverseString(myString);
      
    //input line
    } else if (choice == 2) {
      //gets a string from the input line
      cout << "Enter a string: " << endl;
      string myString;
      cin.ignore();
      getline(cin, myString);
      //reverses the string
      ReverseString(myString);
      
    } else {
      cout << "Invalid input. Please enter 1 or 2!\n";
    }

    cout << "Would you like to continue? (y/n)" << endl;
    cin >> again;
  } while (again == 'y' || again == 'Y');
  return 0;
}
