#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include "AdjacencyList.h"
#include "primary.h"
#include "movie.h"

//creates the map ingoing[movieID] = <userID, rating>
void AdjacencyList::buildingoing(string from, string to, string wt) {
    graphingoing[from].push_back(make_pair(to, stoi(wt)));
    if (graphingoing.find(to) == graphingoing.end()) {
        graphingoing[to] = {};
    }
}

//assigns avg rating to the Movie vector 
short int AdjacencyList::Rating(string from) { //from = movieID
    if (graphingoing.find(from) == graphingoing.end()) {
        return 0;
    }
    short int sum = 0;
    int size = graphingoing[from].size();
    for (auto it = graphingoing[from].begin(); it != graphingoing[from].end(); ++it) {
        //cout << it->second << endl;
        sum += (it->second);
    }
    if (size != 0) {         
        sum /= size;
    }
    return sum;
}

//void AdjacencyList::Print() {
//    for (auto it = graph.begin(); it != graph.end(); ++it)
//    {
//        cout << it->first << " ->";
//        for (int j = 0; j < it->second.size(); j++)
//            cout << " " << it->second[j].first << " " << it->second[j].second << " |";
//        cout << "\n";
//    }
//}