#pragma once
#include <map>
#include <string>
#include <vector>
//#include "movie.h"
using namespace std;

class AdjacencyList {
public:
    //userID           //movieID  //rank
   // map<string, vector<pair<string, int>>> graph; //userID -> movie
    map<string, vector<pair<string, short int>>> graphingoing; //movie -> userID
    //map<string, int> review;
public:
    void buildoutgoing(string from, string to, string wt);
    void buildingoing(string from, string to, string wt);
    short int Rating(string from);
    void Print();
};

