#include <iostream>
#include <string>

using namespace std;

//Base Clase Declaration 
class StreamingService{
    private:
        string Title;
        string Description;
    public:
    //Getters/Setters
        void setTitle(string newTitle){
            Title = newTitle;
        }
        string getTitle(){
            return Title;
        }
        void setDescription(string newDescription){
            Description = newDescription;
        }
        string getDescription(){
            return Description;
        }
    //Default constructor
    StreamingService() {}
    //Overloaded constructor
    StreamingService(string Title, string Description) : Title(Title), Description(Description){}

};


//Derived Class Declaration: Movies
class Movies : public StreamingService{
    private:
        string openingCredits;
    public:
        //getter and setter for opening credits 
        void setopeningCredits(string newcredits){
            openingCredits = newcredits;
        }
        string getopeningCredits() const{
            return openingCredits;
        }
        //Default Constructor
        Movies(){
        }
        //Overloaded constructor
        Movies(string Title, string Description, string openingCredits) : StreamingService(Title, Description), openingCredits(openingCredits) {
        }
};
