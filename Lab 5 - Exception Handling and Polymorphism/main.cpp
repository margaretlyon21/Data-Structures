#include <iostream>
#include <string>
#include <stdexcept>
#include "streamingservice.cpp"
using namespace std;

class fullShelf : public exception{
  public:
    const char* message() {
      return "The shelf is full";
    }
    
};
class emptyShelf : public exception{
  public:
    const char* message() {
      return "The shelf is empty";
    }
};

const int maxMovies = 5;
class Shelf{
    private:
      const int movies = maxMovies;
      Movies movieShelf[maxMovies];
      int index;
    public:
    //constructor 
    Shelf() : movies(maxMovies), index(0){
      for (int i = 0; i < maxMovies; i++){
      }
    }
    //add function
    void add(string title, string description, string openingCredits){
      if (isFull()){
        throw fullShelf();
      }
      movieShelf[index] = Movies(title, description, openingCredits);
      index++;
    }
    //remove function
    string remove(){
      if (isEmpty()){
        throw emptyShelf();
      }
      index -=1;
      return movieShelf[index].getTitle();
    }
    //checks if shelf is full
    bool isFull(){
      return index >= movies;
    }
    //checks if shelf is empty
    bool isEmpty (){
      return index <= 0;
    }
    //gets the number of movies on the sheld 
    int count(){
      return index;
    }
    // gets the copy of next thing to remove without removing 
   Movies top(){
     return movieShelf[index - 1];
   }
};

int main() {
  Shelf movieShelf;
  int choice;

  // Prompts the user for an action
while (true) {
  cout << "Choose an option to proceed:\n" << "1. Add a movie to the shelf. \n" << "2. Remove a movie from the shelf. \n" << "3. See how many movies are currently on the shelf. \n" << "4. Quit.\n";
  cin >> choice;
  cin.ignore();
  //Add a movie ot the shelf 
  if (choice == 1) {
    cout << "Enter the name of the movie you would like to add: " << endl;
    string title, description, openingCredits;
    getline(cin,title);
    cout << "Enter the description of the movie you would like to add: " << endl;
    getline(cin,description);
    cout << "Enter the opening credits of the movie you would like to add: ";
    getline(cin, openingCredits);
    movieShelf.add(title,description,openingCredits);
    cout << "Added " << title << " to the shelf." << endl;
  }
  //Remove a movie from the shelf
  else if (choice == 2) {
    if (!movieShelf.isEmpty()){
      Movies thisMovie = movieShelf.top();
      movieShelf.remove();
      cout << "Movie being removed: " << thisMovie.getTitle() << endl;
      cout << "Movie Description: " << thisMovie.getDescription() << endl;
      cout << "Movie Opening Credits: " <<     thisMovie.getopeningCredits() << endl;
    }
    else{
      movieShelf.remove();
    }
  }
  //See how many movies are currently on the shelf
  else if (choice == 3) {
    cout << "There are " << movieShelf.count() << " movies on the shelf." << endl;
  }
  // Quits the program
  else {
    cout << "Goodbye!" << endl;
    break;
  }
}
  return 0;
}

