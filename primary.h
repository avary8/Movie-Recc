#pragma once
#include <map>
#include <string>
#include <vector>
#include <queue>
#include "movie.h"
#include "AdjacencyList.h"
using namespace std;

class Compare {
public:
    bool operator() (Movie* left, Movie* right) {
        return left->avgRating < right->avgRating;
    }
};

class primary {
public:
    primary() {};
    static bool isYear(string& str);
    static void LoadRatings(string filename);
    static void LoadData(string filename);
    static vector<string> getGenres(string& s, string delim);
    static void Print(Movie& m);
    static void getResults();
    static void setBuff();

private:
    static vector<Movie*> m;
    static AdjacencyList l;
    static priority_queue<Movie*, vector<Movie*>, Compare> MovieRanker;
    //static priority_queue<Movie, vector<Movie>, greater<Movie>> MovieRanker;
};

