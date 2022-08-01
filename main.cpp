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
#include "homeScreen.h"
#include "resultScreen.h"
#include "movie.h"
#include "primary.h"
#include "AdjacencyList.h"
using namespace std;

int main(){
    primary::LoadData("movies.csv");

    Fl_Window* window = new Fl_Window(800, 600, "Movie  Recommender");
    window->begin();
    window->color(FL_BLACK);
    homeScreen::init();

    window->end();
    window->show();
    return Fl::run();
}
