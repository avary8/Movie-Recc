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
    bool operator() (const Movie* left, const Movie* right) { return left->avgRating < right->avgRating; }
};

class primary {
public:
    static void LoadRatings(string filename);
    static void LoadData(string filename);

    static vector<string> getGenres(string s, string delim);
    static int GRating(Movie* m);
    static void Print(Movie& m);
    static int r_helper(AdjacencyList& l, string s);
    static int r(string s);  
    static void getResults();
    static void setBuff();

    static vector<Movie*>& getMovie() { return m; };
    static AdjacencyList& getList() { return l; }
    static priority_queue<Movie*, vector<Movie*>, Compare>& getMovieRanker() { return MovieRanker; }

private:
    static vector<Movie*> m;
    static AdjacencyList l;
    static priority_queue<Movie*, vector<Movie*>, Compare> MovieRanker;
    //static priority_queue<Movie, vector<Movie>, greater<Movie>> MovieRanker;
};

