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
vector<Movie*> primary::m;
AdjacencyList primary::l;
priority_queue<Movie*, vector<Movie*>, Compare> primary::MovieRanker;

//bool operator>(const Movie& left, const Movie& right) {
//    return left.avgRating > right.avgRating;
//}

//bool operator<(const Movie& left, const Movie& right) {
//    return left.avgRating < right.avgRating;
//}

void primary::LoadRatings(string filename) {
    ifstream File(filename, ios::in);
    if (File.is_open()) {
        string line;
        string from, to, wt;  //userID, movieID, rating
        getline(File, line);

        while (getline(File, line)) {

            istringstream stream(line);
            stringstream ss(line);

            getline(stream, from, ',');
            getline(stream, to, ',');
            getline(stream, wt);
            //cout << "movie: " << to << " to: " << from << endl;
            //l.buildoutgoing(from, to, wt);
            l.buildingoing(to, from, wt);
        }
        File.close();
        cout << "closed";
    }
    else {
        cout << "Error: " << filename << "could not be opened!" << endl;
    }
    return;
}

void primary::LoadData(string filename) {
    primary::LoadRatings("ratings2.csv");

    //AdjacencyList l;
    ifstream File(filename, ios::in);
    if (File.is_open()) {
        string line;
        getline(File, line);

        while (getline(File, line)) {

            istringstream stream(line);
            stringstream ss(line);

            string s;
            Movie* temp = new Movie; 
            //string year = "";

            getline(stream, temp->movieID, ',');
            getline(stream, temp->title, '(');
            getline(stream, temp->year, ')');

            //cout << temp.movieID << " : " << temp.title << " : " << temp.year << endl;
            
            /*cout << m.size() << " : begin year:" << year << endl;
            if (year == "" || year == "no genres listed") {
                year = '0';
            }
            else {
                bool invalid = true;
                do {
                    if (year.size() != 4) {
                        getline(stream, year, '(');
                        getline(stream, year, ')');
                    } 
                    else if ((year.at(0) != '1' && year.at(1) != '9' && year.at(2) != '9') && (year.at(0) != '2' && year.at(1) != '0')) {
                        getline(stream, year, '(');
                        getline(stream, year, ')');
                    }
                    else {
                        invalid = false;
                    }
                } while (invalid);
            }
            */
            
            //cout << "result year: " << year << endl;
            //temp->year = year;

            getline(stream, temp->genre, ',');
            getline(stream, temp->genre, ',');

            temp->genres = getGenres(temp->genre, "|");
            temp->avgRating = l.Rating(temp->movieID);
            
            m.push_back(temp);
        }

        File.close();
    }
    else {
        cout << "Error: " << filename << "could not be opened!" << endl;
    }

    return;
}

vector<string> primary::getGenres(string s, string delim) {
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



int primary::GRating(Movie* m) {
    // AdjacencyList l;

    double avgReview = 0;
    if (l.graphingoing.find(m->movieID) == l.graphingoing.end()) {
        return 1;
    }

    for (auto it = l.graphingoing[m->movieID].begin(); it != l.graphingoing[m->movieID].end(); ++it) {
        avgReview += (it->second);
    };

    int size = l.graphingoing[m->movieID].size();
    avgReview /= size;
    int avg = (int)(avgReview + 0.5);

    m->avgRating = avg;
    return avg;
}

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

int primary::r_helper(AdjacencyList& l, string s) {
    return l.Rating(s);
}

int primary::r(string s) {
    AdjacencyList h;
    return r_helper(h, s);
}


void primary::getResults() {
    cout << "in getREsults\n";

    string genre = homeScreen::getGenre();
    int start_year = homeScreen::getYearMin(); //1995 - 2017
    int end_year = homeScreen::getYearMax();
    int minStars = homeScreen::getStars();
    int numResults = homeScreen::getNumResults();
    //for (int i = 0; i < m.size(); i++) {
    cout << "before for\n";

    for (int i = 0; i < m.size(); i++) {
        //GRating(m[i], l);
        /*Movie* temp = m[i];
        temp->avgRating = l.Rating(temp->movieID);*/
        //cout << "m[" << i << "]->year : " << m[i]->year << endl;
        //cout << m->at(0)->genres[0] << endl;
        cout << m[i]->genres[0] << endl;

        /*if (stoi(m->at(0)->year) >= start_year && stoi(m->at(0)->year) <= end_year && m->at(0)->avgRating >= minStars
            && count(m->at(0)->genres.begin(), m->at(0)->genres.end(), genre)) {*/
        if ((m[i]->year.size() == 4) && (((m[i]->year.at(0) == '1' && m[i]->year.at(1) == '9' && m[i]->year.at(2) == '9')) || (m[i]->year.at(0) == '2' && m[i]->year.at(1) == '0'))) {
            if (stoi(m[i]->year) >= start_year && stoi(m[i]->year) <= end_year && m[i]->avgRating >= minStars
                && count(m[i]->genres.begin(), m[i]->genres.end(), genre)) {
                /*if (m[i]->year >= start_year && m[i]->year <= end_year && m[i]->avgRating >= minStars
                    && count(m[i]->genres.begin(), m[i]->genres.end(), genre)) {*/
                MovieRanker.push(m[i]);
            }
        }
    }
}



//void setBuff(Fl_Text_Buffer& buffer, priority_queue<Movie, vector<Movie>, greater<Movie>>& MovieRanker) {
//    int size = MovieRanker.size();
//    if (size == 0) {
//        buffer.text("No results found");
//    }
//    int numResults = homeScreen::getNumResults();
//    int index = 1;
//    while (numResults != 0 && size != 0) {
//
//        Movie temp = MovieRanker.top();
//
//        string result = to_string(index) + ". " + temp.title + "(" + temp.year + ") ";
//        for (int i = 0; i < temp.genres.size(); i++) {
//            result += temp.genres[i] + " ";
//        }
//
//        result += temp.avgRating;
//
//        buffer.append(result.c_str());
//        buffer.append("\n");
//
//        MovieRanker.pop();
//
//        numResults--;
//        size--;
//        index++;
//    }
//
//}

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

        result = to_string(index) + ". " + temp->title + "(" + temp->year + ") ";
        //result = to_string(index) + ". " + temp->title + "(" + to_string(temp->year) + ") ";
        for (int i = 0; i < temp->genres.size(); i++) {
            result += temp->genres[i] + " ";
        }

        result += temp->avgRating;

        file << result + "\n";
        MovieRanker.pop();
        numResults--;
        size--;
        index++;
    }
    file.close();
}