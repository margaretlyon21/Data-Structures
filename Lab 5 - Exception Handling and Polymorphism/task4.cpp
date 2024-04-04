#include <iostream>
#include <string>
using namespace std;

// Exceptions
class fullCollection : public exception{
  public:
    const char* message() {
      return "The collection is full";
    }

};
class emptyCollection : public exception{
  public:
    const char* message() {
      return "The collection is empty";
    }
};

// Template for entertain collections
template <class T>
class EntertainmentCollection {
private:
    const int maxSize = 5;
    T collection[5];
    int index;

public:
    // Constructor
    EntertainmentCollection() : index(0) {}

    // Functions
    // Add a new item to the collection
    void add(T item) {
        if (isFull()) {
            throw fullCollection();
        }
        collection[index++] = item;
    }
    // Removes the top item from the collection
    void remove(){
      if (isEmpty()){
        throw emptyCollection();
      }
      index -= 1;
    }
    // Shows what item is currently on top
    T top() {
      return collection[index - 1];
    }
    // Checks if collection is full/empty
    bool isFull() {
        return index >= maxSize;
    }
    bool isEmpty (){
      return index <= 0;
    }
    // Returns number of items in collection
    int count(){
      return index;
    }
};

// Video game class with title and genre
class VideoGame {
private:
    string title;
    string genre;

public:
    // Constructors
    VideoGame() {}
    VideoGame(string gameTitle, string gameGenre) : title(gameTitle), genre(gameGenre) {}

    // Getters and setters
    string getGenre() {
        return genre;
    }
    string getTitle() {
        return title;
    }
    void setGenre(string gameGenre) {
        genre = gameGenre;
    }
    void setTitle(string gameTitle) {
      title = gameTitle;
    }
};

int main() {
  EntertainmentCollection<VideoGame> videoGames;

  int choice;
  do {
    cout << "Choose an option:\n";
    cout << "1. Add a video game to the collection\n";
    cout << "2. Remove a video game from the collection\n";
    cout << "3. Show number of video games in the collection\n";
    cout << "4. Exit\n";

    cin >> choice;

    if (choice == 1) {
      string title, genre;
      cout << "Enter the title of the video game: " << endl;
      cin >> title;
      cout << "Enter the genre of the video game: " << endl;
      cin >> genre; 
      videoGames.add(VideoGame(title, genre));
    }
    else if (choice == 2) {
      cout << "The video game being removed is " << videoGames.top().getTitle() << endl;

      videoGames.remove();
    }
    else if (choice == 3) {
      cout << "Number of video games in the collection: " << videoGames.count() << endl;
    }
    else if (choice == 4) {
      return 0;
    }
  } while (choice != 4);
  return 0;
}