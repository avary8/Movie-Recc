#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "movie.h"
#include "primary.h"
#include "homeScreen.h"
#include "resultScreen.h"
using namespace std; 
//declaring static variables 
vector<Movie*> primary::m;
AdjacencyList primary::l;
priority_queue<Movie*, vector<Movie*>, Compare> primary::MovieRanker;

//returns if string is a year 
bool primary::isYear(string& str){
    if (str.size() != 4) {
        return false;
    }
    for (int i = 0; i < str.size(); i++) {
        if (!isdigit(str.at(i))) {
            return false;
        }
    }
    return true;
}

void primary::LoadRatings(string filename) {
    ifstream File(filename, ios::in);
    if (File.is_open()) {
        string line;
        string from, to, wt;  //movieID, userID, rating
        getline(File, line);

        while (getline(File, line)) {
            istringstream stream(line);
            stringstream ss(line);
            getline(stream, to, ',');
            getline(stream, from, ',');
            getline(stream, wt);
 
            l.buildingoing(from, to, wt);
        }
        File.close();
    }
    else {
        cout << "Error: " << filename << "could not be opened!" << endl;
    }
}

void primary::LoadData(string filename) {
    primary::LoadRatings("ratings2.csv");

    ifstream File(filename, ios::in);
    if (File.is_open()) {
        string line;
        getline(File, line);

        while (getline(File, line)) {
            istringstream stream(line);
            stringstream ss(line);

            string s;
            Movie* temp = new Movie; 
 
            getline(stream, temp->movieID, ',');
            getline(stream, temp->title, '(');
            getline(stream, temp->year, ')');

            //if year is not valid
            if (temp->year == "no genres listed") {
                temp->year = "0";
                temp->genre = "no genres listed";
            }
            else {
                while (!isYear(temp->year) && !stream.eof()) {
                    getline(stream, temp->year, '(');
                    getline(stream, temp->year, ')');
                }
                getline(stream, temp->genre, ',');
                getline(stream, temp->genre, ',');
                temp->genres = getGenres(temp->genre, "|");
                temp->avgRating = l.Rating(temp->movieID);
            }
            m.push_back(temp);
        }
        File.close();
    }
    else {
        cout << "Error: " << filename << "could not be opened!" << endl;
    }
}
//sets up the genre vector 
vector<string> primary::getGenres(string& s, string delim) {
    size_t pos_start = 0, pos_end, delim_len = delim.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delim, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(s.substr(pos_start));
    return res;
}

//prints for the command line
void primary::Print(Movie& m) {
    cout << "Title: " << m.title << endl;
    cout << "Year: " << m.year << endl;
    cout << "Genre(s): ";
    int last = m.genres.size() - 1;
    for (int i = 0; i < last; i++) {
        cout << m.genres[i] << ", ";
    }
    cout << m.genres[last] << endl;
    cout << "Average rating: " << m.avgRating << "/5" << endl;
}

void primary::getResults() {
    string genre = homeScreen::getGenre();
    int start_year = homeScreen::getYearMin(); //1995 - 2019
    int end_year = homeScreen::getYearMax();
    int minStars = homeScreen::getStars();
    int numResults = homeScreen::getNumResults();

    for (int i = 0; i < m.size(); i++) {
        //cout << m[i]->movieID << " : " << m[i]->title << " : " << m[i]->year << " : " << m[i]->genre << endl;
        if (isYear(m[i]->year) && stoi(m[i]->year) >= start_year && stoi(m[i]->year) <= end_year && m[i]->avgRating >= minStars) {
            if (genre != "-" && genre != "no genres listed") {//ignores genre
                if (count(m[i]->genres.begin(), m[i]->genres.end(), genre)) {
                    MovieRanker.push(m[i]);
                }
            }    
            else {
                MovieRanker.push(m[i]);
            }
        }
    }
}

//writes the file of results for the buffer
void primary::setBuff() {
    ofstream file;
    file.open("results.txt");

    int size = MovieRanker.size();
    if (size == 0) {
        file << "No results found";
    }

    int numResults = homeScreen::getNumResults();
    int index = 1;

    while (numResults != 0 && size != 0) {
        string result = "";
        Movie* temp = MovieRanker.top();

        result = to_string(index) + ")  Title: " + temp->title + "\nYear: " + temp->year + "\nGenre(s): ";
        for (int i = 0; i < temp->genres.size()-1; i++) {
            result += temp->genres[i] + ", ";
        }
        result += temp->genres[temp->genres.size() - 1] + "\nAverage rating: " + to_string(temp->avgRating) + "/5";

        file << result + "\n\n\n";

        MovieRanker.pop();
        numResults--;
        size--;
        index++;
    }
    file.close();
}