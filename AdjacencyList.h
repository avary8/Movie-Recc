#pragma once
#include <map>
#include <string>
#include <vector>
//#include "movie.h"
using namespace std;

class AdjacencyList {
public:
    void buildingoing(string from, string to, string wt);
    short int Rating(string from);
    void Print();
private:
    //  movie ->  userID , rating
    map<string, vector<pair<string, short int>>> graphingoing; 
};

