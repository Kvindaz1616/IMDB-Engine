/**********************************************************
 * KEVIN DIAZ
 * MWF 1 - 1:50PM
 * CSC - 141 AT UIC FALL 2022 SEMESTER
 * VISUAL STUDIO USING WINDOWS 10
 * PROGRAM 4 - IMDB DATABASE
 * *********************************************************/

#include <iostream>
#include <vector>    //storing files
#include <sstream>   //for reading in files
#include <algorithm> //needed for the find() syntax if used
#include <iomanip>   //for setw()
#include <fstream>  //read files
#include <string> //getline syntax
#include <cassert>  //write files

using namespace std;

struct TitleRecord
{ // objects for movieTitles.tsv to be stored in
    string primaryTitle;
    string genres;
    string titleId;
    string startYear;
};

struct NameRecord
{ // objects for names.tsv to be stored in
    string nameId;
    string primName;
    string profession;
    string birthYear;
    string deathYear;
};

struct PrincipalRecord
{ // objects for principal.tsv to be stored in
    string titleId;
    string nameId;
    string category;
    string characterPlayed;
};

/*********************************************** Helper functions ***************************************/

// The splitString function takes a line and split it on the delimiter and push the parts into items
void splitString(string line, char delimiter, vector<string>& items)
{
    stringstream s_stream(line);
    while (s_stream.good())
    {
        string item;
        getline(s_stream, item, delimiter);
        items.push_back(item);
    }
}

void searchTitles(const vector<TitleRecord>& titles, const vector<PrincipalRecord>& records, const vector<NameRecord>& names, string searchWord)
{

    vector<TitleRecord> matching; // Vector to capture matching titles
    vector<string> items_1;
    string movieTitle;

    for (int i = 0; i < searchWord.length(); i++)
    { // convert searchWord to lowercase
        searchWord.at(i) = tolower(searchWord.at(i));
    }

    for (int num = 0; num < titles.size(); num++)
    { // Going thru the titleRecords and saving the title to 'movieTitle'
        movieTitle = titles.at(num).primaryTitle;

        for (int x = 0; x < movieTitle.length(); x++)
        { // convert movietitle to lowercase
            movieTitle.at(x) = tolower(movieTitle.at(x));
        }

        splitString(searchWord, '+', items_1);
        bool flag = true;
        for (int i = 0; i < items_1.size(); i++)
        {
            if (movieTitle.find(items_1.at(i)) != string::npos)
            { // compare movietitle to searchword if a match push that into 'matching' vector
                continue;
            }
            else
            {
                flag = false;
                break;
            }
        }
        if (flag == true)
        {
            matching.push_back(titles.at(num));
        }
    }  

    int counter = 0;
    int spacer=0;
    for (int j = 0; j < matching.size(); j++) {

        if (spacer ==0){
            cout << endl;
        }

        cout << counter << ":" << endl;
        cout << "Title: " << matching.at(j).primaryTitle << endl;   //prints title of movie
        cout << "Year: " << matching.at(j).startYear << endl;       //start year of movie
        // cout << "Genre: " << matching.at(j).genres << endl;         // type of genre
         //vector<string> genres;
         //splitString(matching.at(j).genres, ',', genres);
        cout << "Genre: ";
        for (int i = 0; i < matching.at(j).genres.size(); i++) {     //display genres without the comma
            if (matching.at(j).genres.at(i) == ',') {
                matching.at(j).genres.at(i) = ' ';
            }
        }
        cout << matching.at(j).genres << endl;

        for (int i = 0; i < 16; ++i)    //displays dashes
        {
            cout << "-";
        }
        counter++;
        spacer++;
        cout << endl;
    }
    if (counter == 0) {           //if no match it will display error
        cout << "No match found!" << endl;
        cout << endl;
        return;
    }

    cout << "Select a movie to see its actors/actresses (-1 to go back to the previous menu): ";

    int index;
    cin >> index;       //for the user to enter the listing of choice
    if (cin.fail())
    {
        return;
    }
    if (index >= 0)
    {
        vector<string> realNames;     // holds the matching actor/actress' names from principal.tsv when found
        vector<string> nconst;        // holds nconst of the matching actor/actress' when matched
        vector<string> characterName; // holds charcter name
        for (int i = 0; i < records.size(); i++)
        { // for loop going through principal.tsv
            if ((records.at(i).titleId == matching.at(index).titleId) && (records.at(i).category == "actor" || records.at(i).category == "actress") && (records.at(i).characterPlayed != "\\N"))
            {
                realNames.push_back(records.at(i).characterPlayed); // pushes back real actor/actress' name and stores in realNames
                nconst.push_back(records.at(i).nameId);             // pushes back matching nconst string
            }
        }

        for (int i = 0; i < names.size(); i++) { // reads through names.tsv
            for (int j = 0; j < nconst.size(); j++) { // reals through items of vector string nconst
                if (names.at(i).nameId == nconst.at(j)) { // if both nameiD AND nconst match then the corresponding actor/actress' name will be stored
                    characterName.push_back(names.at(i).primName);
                }
            }
        }

        for (int i = 0; i < characterName.size(); i++)
        { // reads through contents of characterName and realNames and displays movie character name followed by their actual name
            cout << characterName.at(i) << " " << realNames.at(i) << endl;
        }
        string searchPhrase;
        cout << "Enter search phrase (type done to go back to the previous menu): ";
        cin >> searchPhrase;
        if (cin.fail())
        {
            return;
        }
        if (searchPhrase == "done") //if equals done it will return to main menu
        {
            return;
        }
        else
        {
            searchTitles(titles, records, names, searchPhrase); //else will continue to search the user phrase
        }
    }
    else {  //if user enters -1 it will return to main menu
        return;
    }
}

void searchActorsOrActresses(const vector<TitleRecord>& titles, const vector<PrincipalRecord> records, const vector<NameRecord>& actorsActresses, string searchWord)
{
    vector<NameRecord> matching_2;  //vector of type struct to hold
    vector<string> items_2;         //vector for storage
    string actors;

    for (int i = 0; i < searchWord.length(); i++) { // convert searchWord to lowercase
        searchWord.at(i) = tolower(searchWord.at(i));
    }

    for (int i = 0; i < actorsActresses.size(); i++)        //reads through names.tsv
    {
        actors = actorsActresses.at(i).primName;

        for (int x = 0; x < actors.length(); x++)
        { // convert actor names to lowercase
            actors.at(x) = tolower(actors.at(x));
        }

        splitString(searchWord, '+', items_2); // when a + is found it will store the word in items2 and lead to the next + if there is one
        bool flag2 = true;
        for (int i = 0; i < items_2.size(); i++)
        {
            if (actors.find(items_2.at(i)) != string::npos)
            {
                continue;
            }
            else
            {
                flag2 = false;
                break;
            }
        }
        if (flag2 == true)
        {
            matching_2.push_back(actorsActresses.at(i));    //pushes all names.tsv information into matching_2
        }
    }

    int counter = 0;
    int spacer=0;

    for (int i = 0; i < matching_2.size(); i++) {       //reads through vector string matching_2
       if (spacer ==0){                                 //prints the ------------- for the first listing
         for (int i = 0; i < 16; ++i) {
            cout << "-";
        }
        cout <<endl;
       }

        cout << counter << ":" << endl;
        cout << matching_2.at(i).primName << endl;                                                     // prints actor/actress' name
        cout << matching_2.at(i).profession << endl;                                                   // prints their profession
        cout << "(" << matching_2.at(i).birthYear << "-" << matching_2.at(i).deathYear << ")" << endl; // prints their birth dates and year of death (if it has occured)
        for (int i = 0; i < 16; ++i)
        {
            cout << "-";
        }
        counter++;
        spacer++;
        cout << endl;
    }
    if (counter == 0) { //if not matches it will show this error
        cout << "No match found!" << endl;
        cout << endl;
        return;
    }
    cout << endl;

    cout << "Select a movie to see its actors/actresses (-1 to go back to the previous menu): "; // asks user to enter which listing they'd like to see

    int index;
    cin >> index;
    if (index >= 0) {                              // while index is greater or equal to 0 the following below will execute
        vector<string> realNames;  // holds the matching actor/actress' names from principal.tsv when found
        vector<string> movieTitle; // holds movieTitles from titles.tsv
        vector<string> tconst;     // holds tconst of the matching actor/actress' when matched

        for (int i = 0; i < records.size(); i++)
        { // reads through principal.tsv and if all if condtions are met then it pushes back indexes
            if ((records.at(i).nameId == matching_2.at(index).nameId) && (records.at(i).category == "actor" || records.at(i).category == "actress"))
            {
                realNames.push_back(records.at(i).characterPlayed); // pushes back index five of principal.tsv
                tconst.push_back(records.at(i).titleId);            // pushes back index 0 of principal.tsv
            }
        }

        for (int i = 0; i < titles.size(); i++)
        { // reads through titles.tsv
            for (int j = 0; j < tconst.size(); j++)
            { // reads through the vector string tconst items
                if (titles.at(i).titleId == tconst.at(j))
                { // if both titleIds and tconstIds match then it will push back Movie titles
                    movieTitle.push_back(titles.at(i).primaryTitle);
                }
            }
        }

        for (int i = 0; i < movieTitle.size(); i++)
        { // reads through movieTitle size and prints both movie titles and the corresponding actor/actress' characterp played in that movie
            cout << movieTitle.at(i) << " " << realNames.at(i) << endl;
        }
        string searchPhrase;
        cout << "Enter search phrase (type done to go back to the previous menu): ";
        cin >> searchPhrase;
        if (cin.fail())
        {
            return;
        }
        if (searchPhrase == "done")     //if user enters done then it will return to main menu
        {
            return;
        }
        else                            //if does not equal done it will then research
        {
            searchTitles(titles, records, actorsActresses, searchPhrase);
        }
    }
    else {
        return;
    }
}

void readInMovieTitles(string movieFile, vector<TitleRecord>& movieTitle)
{ // reads in movie.Titles.tsv

    // TitleRecord movieLine;
    vector<string> items2;
    ifstream inStream;
    inStream.open(movieFile);

    if (!inStream.is_open())
    {
        cout << "error";
        exit(0);
    }
    string recordLine;
    getline(inStream, recordLine);
    // read in each line of the file
    while (getline(inStream, recordLine))
    {
        vector<string> items2;
        splitString(recordLine, '\t', items2);
        TitleRecord oneMovieName;

        oneMovieName.titleId = items2[0];      // stores index of items2 to oneMovieName.titleId
        oneMovieName.primaryTitle = items2[2]; // stores index of items2 to oneMovieName.primaryTitle
        oneMovieName.startYear = items2[5];    // stores index of items2 to oneMovieName.startYear
        oneMovieName.genres = items2[8];       // stores index of items2 to oneMovieName.genres

        movieTitle.push_back(oneMovieName);
    }
}

void readInMovieNames(string movieNamesFile, vector<NameRecord>& movieNames)
{
    // NameRecord namesLine;
    vector<string> items3;
    ifstream inStream2;
    inStream2.open(movieNamesFile);

    if (!inStream2.is_open())
    {
        cout << "error";
        exit(0);
    }
    string recordLine;
    getline(inStream2, recordLine);
    // read in each line of the file
    while (getline(inStream2, recordLine))
    {
        vector<string> items3;
        splitString(recordLine, '\t', items3);
        NameRecord oneName;

        oneName.nameId = items3[0];     // stores index of items3 to oneName.nameId
        oneName.primName = items3[1];   // stores index of items3 to oneName.primName
        oneName.birthYear = items3[2];  // stores index of items3 to oneName.birthYear
        oneName.deathYear = items3[3];  // stores index of items3 to oneName.deathYear
        oneName.profession = items3[4]; // stores index of items3 to oneName.profession
        movieNames.push_back(oneName);
    }
}

void readInPrincipals(string moviePrincipalsFile, vector<PrincipalRecord>& moviePrincipals)
{
    // PrincipalRecord movieP;
    vector<string> items4;
    ifstream inStream3;
    inStream3.open(moviePrincipalsFile);

    if (!inStream3.is_open())
    {
        cout << "error";
        exit(0);
    }
    string recordLine;
    getline(inStream3, recordLine);
    // read in each line of the file
    while (getline(inStream3, recordLine))
    {
        vector<string> items4;
        splitString(recordLine, '\t', items4);
        PrincipalRecord one_P_Record;

        one_P_Record.titleId = items4[0];         // stores index of items4 to one_P_Record.titleId
        one_P_Record.nameId = items4[2];          // stores index of items4 to one_P_Record.nameId
        one_P_Record.category = items4[3];        // stores index of items4 to one_P_Record.category
        one_P_Record.characterPlayed = items4[5]; // stores index of items4 to one_P_Record.characterPlayed
        moviePrincipals.push_back(one_P_Record);
    }
}

void menuOption(const vector<TitleRecord>& movies, const vector<NameRecord>& names, const vector<PrincipalRecord>& records)
{                        // this is menu option 1 of exploring the database
    string userOption;   // string for user number input
    string searchPhrase; // string for the user to enter a phrase

    while (userOption != "3")       //Main Interface
    {
        cout << "Select a menu option:" << endl; // Menu interface
        cout << setw(6) << "1. " << "Search for movies" << endl;
        cout << setw(6) << "2. " << "Search for actors/actresses" << endl;
        cout << setw(6) << "3. "<< "Exit" << endl;
        cout << "Your choice --> ";
        // hello world -> -world-game
        // Flushing cin buffer
        cin.clear();
        fflush(stdin);
        cin >> userOption;
        if (cin.fail())
        {
            break;
        }
        if (userOption == "1")      //userOption 1
        {
            cout << "Enter search phrase: ";
            cin >> searchPhrase;
            if (cin.fail())
            {
                break;
            }
            searchTitles(movies, records, names, searchPhrase); //search function
        }
        if (userOption == "2")  //userOption 2
        {
            cout << "Enter search phrase: ";
            cin >> searchPhrase;
            if (cin.fail())
            {
                break;
            }
            searchActorsOrActresses(movies, records, names, searchPhrase);  //search function
        }
    }
}
/**********************************************************************************************************/

int run(string titlesFile, string namesFile, string principalsFile)
{ // the purpose of int run() is to store all needed functions and inputs into this definiton so it is ran in int main() without changing it
    vector<TitleRecord> movieNames;
    vector<NameRecord> actorNames;
    vector<PrincipalRecord> principals;

    readInMovieTitles(titlesFile, movieNames);
    readInMovieNames(namesFile, actorNames);
    readInPrincipals(principalsFile, principals);
    menuOption(movieNames, actorNames, principals);

    return 0;
}

int main()
{
    // Change these addresses according to your local machine
    string titlesFile = "movie.titles.tsv";
    string namesFile = "movie.names.tsv";
    string principalsFile = "movie.principals.tsv";

    // DO NOT change the main function. The main function will be removed by the autograder
    run(titlesFile, namesFile, principalsFile);
    return 0;
}
