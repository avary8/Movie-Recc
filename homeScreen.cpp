#include "resultScreen.h"
#include "homeScreen.h"
#include "AdjacencyList.h"
//#include "movie.h"
#include "primary.h"

using namespace std;

//initializing static member vars
vector <Fl_Toggle_Button*> homeScreen::buttons;
vector<string> homeScreen::genres = {"-", "Action", "Adventure", "Animation", "Children's", "Comedy", "Crime", "Documentary", "Drama", "Fantasy", "Film - Noir", "Horror", "Musical", "Mystery", "Romance", "Sci - Fi", "Thriller", "War", "Western"};
int homeScreen::toggle = 0;
int homeScreen::starsInput = 0;
string homeScreen::genreInput = "-";
int homeScreen::yearMinInput = 1995;
int homeScreen::yearMaxInput = 2019;
int homeScreen::numResultsInput = 1;

void homeScreen::init() {
	title();
	genre();
	year();
	rating();
	numResults();
	SearchButton();
}

void homeScreen::title() {
	Fl_Box* box = new Fl_Box(260, 90, 281, 43, "Movie Generator");
	box->labelcolor(FL_RED);
	box->box(FL_NO_BOX);
	box->labelsize(36);
	box->labelfont(FL_HELVETICA_BOLD);
}

//hides the label "Enter a keyword" when user starts typing
void homeScreen::keywordCB(Fl_Widget* input, void* data) {
	((Fl_Box*)data)->hide();
}

void homeScreen::keyword() {
	Fl_Input* input = new Fl_Input(326, 150, 149, 30);
	Fl_Box* inputBox = new Fl_Box(326, 150, 149, 30, "Enter a keyword");
	inputBox->labelfont(FL_HELVETICA);
	inputBox->labelsize(16);
	input->when(FL_WHEN_CHANGED);
	input->callback(keywordCB, inputBox);
}

//hides the label "Genre" when a genre is selected
void homeScreen::genreCB(Fl_Widget* input) {
	((Fl_Choice*)input)->label("");
	int picked = ((Fl_Choice*)input)->value(); //returns index of genre selected
	genreInput = genres[picked];
}

void homeScreen::genre() {
	Fl_Choice* choice = new Fl_Choice(326, 150, 149, 30, "Genre");

	choice->align(FL_ALIGN_CENTER);
	choice->labelcolor(FL_BLACK);	
	choice->labelfont(FL_HELVETICA);
	choice->labelsize(18);

	choice->textcolor(FL_BLACK);
	choice->textfont(FL_HELVETICA);
	choice->textsize(14);
	choice->selection_color(FL_WHITE);

	for (int i = 0; i < genres.size(); i++) {
		choice->add(genres[i].c_str());
	}

	choice->when(FL_WHEN_CHANGED);
	choice->callback(genreCB);
}

//hides the label when user begins typing
void homeScreen::yearCB(Fl_Widget* input, void* data) {
	((Fl_Box*)data)->hide();
	string value = ((Fl_Input*)input)->value();
	if (primary::isYear(value)) {
		if (((Fl_Input*)input)->x() == 326 && stoi(value) >= 1995 && stoi(value) <= 1995) {
			yearMinInput = stoi(value);
		}
		else if (((Fl_Input*)input)->x() == 405 && stoi(value) >= 1995 && stoi(value) <= 1995) {
			yearMaxInput = stoi(value);
		}
	}
	
	//cout << "yearmin: " << yearMinInput << endl;
	//cout << "yearMax: " << yearMaxInput << endl;
}

void homeScreen::year() {
	Fl_Input* inputLeft = new Fl_Input(326, 190, 70, 30);
	Fl_Input* inputRight = new Fl_Input(405, 190, 70, 30);

	Fl_Box* inputBox = new Fl_Box(320, 190, 149, 30, "Year: From       Year: To");

	inputBox->labelfont(FL_HELVETICA);
	inputBox->labelsize(12);

	inputLeft->when(FL_WHEN_CHANGED);
	inputRight->when(FL_WHEN_CHANGED);

	inputLeft->callback(yearCB, inputBox);
	inputRight->callback(yearCB, inputBox);
}

void homeScreen::starChange(Fl_Widget* starX, void* data) {
	if (toggle == 1) { //if the star was already selected, unselect it 
		((Fl_PNG_Image*)data)->color_average(FL_WHITE, 0.0);
		starX->redraw();	
	}
	else { //if the star was not selected, select it
		((Fl_PNG_Image*) data)->color_average(FL_YELLOW, 0.0);
		starX->redraw();
	}
}

//ex: if star #3 is pressed, need to chain reaction to activate the stars #1 and #2
void homeScreen::starsCB(Fl_Widget* starX, void* data) {
	int index = 0;
	if (toggle == 0) {//if stars have not been selected yet->> figure out how many need to be switched on
		while (starX != buttons[index]) {
			index++;
		}
	}
	else {//otherwise they can all be switched off 
		index = buttons.size()-1;
	}
	
	for (int i = 0; i <= index; i++) {
		starChange(buttons[i], ((Fl_PNG_Image*)data));
	}
	//sets toggle
	if (toggle == 1){
		toggle = 0;
		starsInput = 0;
	}
	else {
		toggle = 1;
		starsInput = index+1;
	}	
}


void homeScreen::rating() {
	Fl_PNG_Image* starIMG = new Fl_PNG_Image("images/ystar.png");

	Fl_Toggle_Button* star1 = new Fl_Toggle_Button(326, 230, 30, 30);
	Fl_Toggle_Button* star2 = new Fl_Toggle_Button(356, 230, 30, 30);
	Fl_Toggle_Button* star3 = new Fl_Toggle_Button(386, 230, 30, 30);
	Fl_Toggle_Button* star4 = new Fl_Toggle_Button(416, 230, 30, 30);
	Fl_Toggle_Button* star5 = new Fl_Toggle_Button(446, 230, 30, 30);
	buttons = { star1, star2, star3, star4, star5 };

	starIMG->color_average(FL_WHITE, 0.0);

	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->value(0);
		buttons[i]->box(FL_NO_BOX);
		buttons[i]->image(starIMG);
		buttons[i]->redraw();
		buttons[i]->when(FL_WHEN_RELEASE);

		buttons[i]->callback(starsCB, starIMG);//toggles other stars
	}
}

void homeScreen::sliderCB(Fl_Widget* slider) {
	numResultsInput = ((Fl_Value_Slider*)slider)->value();
	//cout << "num of results : " << numResultsInput << endl;
	slider->redraw();
}

void homeScreen::numResults() {
	Fl_Value_Slider* slider = new Fl_Value_Slider(326, 270, 149, 30);
	slider->type(FL_HOR_NICE_SLIDER);
	slider->bounds(1, 100);
	slider->step(1);
	slider->value(1);
	slider->color(FL_WHITE, FL_RED);
	//slider->box(FL_FLAT_BOX); //either do all flat or all down

	slider->textcolor(FL_BLACK);
	slider->redraw();
	slider->when(FL_WHEN_CHANGED);
	slider->callback(sliderCB);
}	

//when search is pressed, results will be displayed in a new window (go to resultScreen.cpp)
void homeScreen::searchCB(Fl_Widget* starX, void* data) {
	primary::getResults();
	primary::setBuff();
	Fl_Window* window = new Fl_Window(800, 600, "Results");
	window->begin();
	window->color(FL_BLACK);
	resultScreen::init();
	window->end();
	window->show();
	//return Fl::run();
}

void homeScreen::SearchButton() {
	Fl_Button* button = new Fl_Button(326, 310, 149, 30);
	button->box(FL_FLAT_BOX);
	button->down_box(FL_FLAT_BOX);
	button->color(FL_RED);
	button->down_color(FL_RED);
	button->label("Search Movies");
	button->labelcolor(FL_WHITE);
	button->labelsize(18);
	button->labelfont(FL_HELVETICA_BOLD);
	button->labelfont(FL_BOLD);
	button->callback(searchCB);
}
