#include "resultScreen.h"
#include "homeScreen.h"
#include "AdjacencyList.h"
//#include "movie.h"
#include "primary.h"

using namespace std;

Fl_Text_Buffer* resultScreen::buffer;
Fl_Text_Display* resultScreen::display;

void resultScreen::init() {
	title();
	topText();

	Fl_Text_Display* display = new Fl_Text_Display(0, 80, 800, 590);
	Fl_Text_Buffer* buffer = new Fl_Text_Buffer();
	display->buffer(buffer);	
	display->box(FL_NO_BOX);
	display->color(FL_BLACK);
	display->textcolor(FL_WHITE);
	display->textfont(FL_HELVETICA);
	display->textsize(14);
	buffer->loadfile("results.txt");
}

void resultScreen::title() {	
	Fl_Box* box = new Fl_Box(392, 30, 50, 16, "Results"); //w = 47 h = 16
	box->labelcolor(FL_RED);
	box->box(FL_NO_BOX);
	box->labelsize(36);
	box->labelfont(FL_HELVETICA_BOLD);
	box->redraw_label();
}

void resultScreen::topText() {
	Fl_Output * searchInput = new Fl_Output(0, 55, 800, 16);
	searchInput->box(FL_NO_BOX);
	searchInput->type(FL_MULTILINE_OUTPUT_WRAP);
	string print = "Search results matching the genre \"" + homeScreen::getGenre() + "\" between the years of " + to_string(homeScreen::getYearMin()) + ("-") + to_string(homeScreen::getYearMax()) + " with at least " + to_string(homeScreen::getStars()) + " stars";
	searchInput->value(print.c_str());
	searchInput->textcolor(FL_WHITE);
	searchInput->redraw();
}

void resultScreen::resultsOuput() {
	/*Fl_Text_Display* display = new Fl_Text_Display(0, 80, 800, 600);
	Fl_Text_Buffer* buffer = new Fl_Text_Buffer();
	display->buffer(buffer);

    int size = MovieRanker.size();
    if (size == 0) {
        buffer->text("No results found");
    }
	int numResults = homeScreen::getNumResults();
	int index = 1;	
	while (numResults != 0 && size != 0) {
		
		Movie temp = MovieRanker.top();

		string result = to_string(index) + ". " + temp.title + "(" + temp.year + ") ";
		for (int i = 0; i < temp.genres.size(); i++) {
			result += temp.genres[i] + " ";
		}

		result += temp.avgRating;

		buffer->append(result.c_str());

		MovieRanker.pop();

		numResults--;
		size--;
		index++;
	}*/
    

}