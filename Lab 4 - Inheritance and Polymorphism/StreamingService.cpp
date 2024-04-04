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

    //Functionality member functions
    virtual void PlayFunctionality() const = 0;
    void detailsFunctionality(){
        cout << "Title: " << getTitle() << "\n";
        cout << "Descrpition: " << getDescription() << "\n";
    }
};

//Derived Class Declaration: tvShows
class tvShows : public StreamingService {
private:
    int seasonEpisodeRunTime[5][5];
    int season;
    int episode;
public:
    // Getters
    int getSeason() {
        return season;
    }
    int getEpisode() {
        return episode;
    }
    int getRunTime(int season, int episode) {
        return seasonEpisodeRunTime[season-1][episode-1];
    }
    // Setters
    void setRuntime(int season, int episode, int runtime) {
        seasonEpisodeRunTime[season][episode] = runtime;
        return;
    }
    void setSeasons(int newSeasons){
        season = newSeasons;
    }
    void setEpisode(int newEpisode){
        episode = newEpisode;
    }

    // Functionality Functions
    void detailsFunctionality() {
        StreamingService::detailsFunctionality();
        cout << "Run time of first episode of first season: " << getRunTime(season,episode) << " minutes." << endl;
    }
    void PlayFunctionality() const override {
        int season, episode;
        cout << "Enter season number: ";
        cin >> season;
        cout << "Enter episode number: ";
        cin >> episode;
        cout << "Run time of selected episode: " << seasonEpisodeRunTime[season - 1][episode - 1] << " minutes" << endl;
    }
    // Default constructor
    tvShows() {}
    // Overloaded constructor
    tvShows(int seasonsEpisodeRunTime[5][5]) {
        string newTitle, newDescription, newOpeningCredits;
        cout << "Enter Title: ";
        cin.ignore();
        getline(cin, newTitle);
        setTitle(newTitle);
        cout << "Enter Description: ";
        getline(cin, newDescription);
        setDescription(newDescription);
        cout << "Enter the number of seasons (max 5): ";
        int seasons, episodes, runtime;
        cin >> seasons;
        setSeasons(seasons);
        cout << "Enter the number of episodes per season : ";
        cin >> episodes;
        setEpisode(episodes);
        cout << "Enter runtime of each episode: \n";
        //loop to check each episode 
        for (int i = 0; i<seasons;++i){
            for (int j = 0; j <episodes; ++j){
                cout << "S" << i+1 << "E" << j+1 << ": ";
                cin >> runtime; 
                //updates each entry individually 
                setRuntime(i,j,runtime);
            }
        }
    }

    //Overloaded constructor with all 3 parameters 
    tvShows(string Title, string Description, int seasonsEpisodeRunTime[5][5]) : StreamingService(Title, Description){
        cout << "Enter the title: ";
        cin.ignore();
        getline(cin, Title);
        cout << "Enter the Description: ";
        getline(cin, Description);
        cout << "Enter the number of seasons (max 5): ";
        int seasons;
        cin >> seasons;
        cout << "Enter the number of episodes per season : ";
        int episodes;
        cin >> episodes;
        for (int i = 0; i<seasons;++i){
            for (int j = 0; j <episodes; ++j){
                cout << "S" << i+1 << "E" << j+1;
                cin >> seasonsEpisodeRunTime[i][j]; 
            }
        }
    }
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
            string newTitle, newDescription, newOpeningCredits;
            cout << "Enter Title: ";
            cin.ignore();
            getline(cin,newTitle);
            setTitle(newTitle);
            cout << "Enter Description: ";
            getline(cin,newDescription);
            setDescription(newDescription);
            cout << "Enter Opening Credits: ";
            getline(cin, newOpeningCredits);
            setopeningCredits(newOpeningCredits);
        }
        //Overloaded constructor
        Movies(string Title, string Description, string openingCredits) : StreamingService(Title, Description), openingCredits(openingCredits) {
        }
        
        //overriden play function
        void PlayFunctionality() const override {
            cout << "Opening Credits: " << getopeningCredits() << "\n";
        }
};

//Function to print the overloaded Play and Details Functionalities
void combinedFunction(StreamingService& myObj){
    cout << "\nDetails: \n";
    myObj.detailsFunctionality();
    cout << "\nPlay Functionality: \n";
    myObj.PlayFunctionality();
}

int main(){
//while loop to allow multiple entries 
while(true){
    //Prompts for user input for which instance they would like
    cout << "Press 1 for instance of Movie. \nPress 2 for instance of TV show.\nPress 3 for instance of Movie declared as a Show.\nPress 4 for instance of TV Show declared as a Show.\n";
    int choice;
    cin >> choice;

    if (choice == 1){
        //Movie
        cout << "**************** Creating an Instance of a Movie *******************\n";
        Movies currentmovie;
        combinedFunction(currentmovie);
        cout <<"**********************************************************************\n";

    }
    else if(choice ==2 ){
        //show 
        cout << "************** Creating an Instance of a TV Show *******************\n";
        int seasonEpisodeRuntime[5][5];
        tvShows newtvShow(seasonEpisodeRuntime);
        combinedFunction(newtvShow);
        cout <<"**********************************************************************\n";
    }
    else if(choice == 3){
        //movie declared as show
        cout << "*********Creating an instance of a Movie declared as a Show **********\n";
        StreamingService* Show = new Movies();
        combinedFunction(*Show);
        cout <<"**********************************************************************\n";

    }
    else if(choice == 4){
        cout << "*********Creating an instance of a TV Show declared as a Show **********\n";
        int seasonEpisodeRuntime[5][5];
        StreamingService* Show = new tvShows(seasonEpisodeRuntime);
        combinedFunction(*Show);
        cout <<"**********************************************************************\n";

    }
    else{
        cout << "Invalid choice. Please try again. \n";
    }

    //allows the loop to continue 
    cout << "Do you want to continue? (Y/N)";
    char choice2;
    cin >> choice2;
    if (choice2 == 'N' or choice2 == 'n'){
        cout << "Thanks, have a nice day!";
        break;
    }
}
}