// Movie Generator.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <queue>
#include <cstdlib>
#include <algorithm>
#include <time.h>
#include <ctime>
#include <iterator>
#include <iomanip>
#include <math.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Text_Buffer.H>
//#include "structs.h"
#include "homeScreen.h"
#include "resultScreen.h"
//#include "movie.h"
#include "primary.h"
#include "AdjacencyList.h"
using namespace std;

int main(){
    vector<Movie*> m = primary::getMovie();
    AdjacencyList l = primary::getList();
    priority_queue<Movie*, vector<Movie*>, Compare> MovieRanker = primary::getMovieRanker();
    //priority_queue<Movie, vector<Movie>, greater<Movie>> MovieRanker = primary::getMovieRanker();
    primary::LoadData("movies.csv");
    //primary::LoadRatings("ratings2.csv");

    //for (int i = 0; i < m.size(); i++) {
    //    GRating(m[i], l);
    //}


    cout << "Welcome to the movie generator!\n";

    string genre = "Romance";
    int start_year = 2008; //1995 - 2017
    int end_year = 2012;
    int minStars = 5;
    int numResults = 5;


    //cout << "Pick a genre\n";

    //cin >> genre;

    //cout << "Pick a starting year\n";

    //cin >> start_year;

    //cout << "Pick an end year\n";

    //cin >> end_year;

    //cout << "Minimum number of ratings\n";

    //cin >> minStars;

    //cout << "How many results would you like to see?\n";

    //cin >> numResults;
 
    Fl_Window* window = new Fl_Window(800, 600, "Movie  Recommender");
    window->begin();
    window->color(FL_BLACK);
    homeScreen::title();
    //homeScreen::keyword();
    homeScreen::genre();
    homeScreen::year();
    homeScreen::rating();
    homeScreen::numResults();
    homeScreen::SearchButton();
    cout << "here";
    /*if (homeScreen::getSearch()) {
        cout << "search";
        primary::getResults(MovieRanker, m, l);
        primary::setBuff(MovieRanker);
    }*/
    
    window->end();
    window->show();
    return Fl::run();
}
