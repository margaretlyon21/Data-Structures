#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Declaration of Book Structure
struct Book{
    string Title;
    string Author;
    int WordCount = 0;
    int LineCount = 0;
    float CharCount = 0;
    char letters[26];
    int letterfrequencies[26] = {0};
};

int main(){
//Runs code as long as true. Allows the program to repeat if the user wants
//to process another book. If not, it will return false and terminate.
while (true){

    //User inputs filename, file opens 
    Book newbook;
    string FileName;
    std::cout << "Input Name of File <FileName>.txt\n";
    std::cin >> FileName;
    ifstream cardcatalog(FileName,ios::in);  
    if (cardcatalog.fail()){
        cout << "Error opening file. Please enter a valid file name";
        break;
    }

    //reads title and author from first and second line
    getline(cardcatalog, newbook.Title);
    getline(cardcatalog, newbook.Author);
    string contents;
    getline(cardcatalog, contents);

    //Sets up arrays for letter frequency
    for (int i = 0; i < 26; ++i) {
        newbook.letters[i] = static_cast<char>('a' + i);
    }

    //Gets word count, line count, total character count, frequency array
    char ch;
    bool Word = false;
    while (cardcatalog.get(ch)) {
        if(std::isalpha(ch)){
            newbook.CharCount++;
            ch = tolower(ch);
            newbook.letterfrequencies[ch- 'a']++;

            }
        if (ch == '\n') {
            newbook.LineCount++;
        }

        // Check if the current character is not a letter to deliminate words
        if (ch == ' ' || ch == '\t' || ch == '\n') {
            Word = false;
        } else if (!Word) {
            Word = true;
            if(std::isalpha(ch)){
                newbook.WordCount++;
            }
            
        }
    }

    //opens CardCatalog file and appends to it 
    ofstream catalog("CardCatalog.txt", ios::app);
    if (!catalog.is_open()){
        cout << "Error - unable to open/create CardCatalog File";
    }
    catalog << "Title: " << newbook.Title << endl;
    catalog << "Author: " << newbook.Author << endl;
    catalog << "Word Count: " << newbook.WordCount << endl;
    catalog << "Line Count: " << newbook.LineCount << endl << "\n";

    //Checks if user wants to see letter frequency
    cout << "Do you want to see the letter frequency? (y/n)";
    char choice;
    cin >> choice;
    if (choice == 'Y' | choice == 'y'){
        catalog << newbook.Title << "Letter Frequency: \n";
        for (int i = 0; i <26; ++i){
            catalog << newbook.letters[i] << ": " << (newbook.letterfrequencies[i] / newbook.CharCount) << "%\n";
        }
        catalog << "\n";
    }

    //Checks if the user wants to process another book
    char input;
    cout<< "Would you like to process another book? (y/n)";
    cin >> input;
    if (input == 'N' | input == 'n'){
        cout << "Have a nice day!";
        catalog.close();
        break;
    }
    else if(input == 'Y' | input == 'y'){
        //continue iterating
    }
    }
    }
