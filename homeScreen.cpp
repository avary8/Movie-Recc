#include "resultScreen.h"
#include "homeScreen.h"
#include "AdjacencyList.h"
//#include "movie.h"
#include "primary.h"

using namespace std;

//initializing static member vars
vector <Fl_Toggle_Button*> homeScreen::buttons;
vector<string> homeScreen::genres = {"-", "Action", "Adventure", "Animation", "Children's", "Comedy", "Crime", "Documentary", "Drama", "Fantasy", "Film - Noir", "Horror", "Musical", "Mystery", "Romance", "Sci - Fi", "Thriller", "War", "Western", "(no genres listed)"};
int homeScreen::toggle = 0;
int homeScreen::starsInput = 0;
string homeScreen::genreInput = "";
int homeScreen::yearMinInput = 0;
int homeScreen::yearMaxInput = 0;
int homeScreen::numResultsInput = 0;
bool homeScreen::search = false;

void homeScreen::title() {
	Fl_Box* box = new Fl_Box(260, 90, 281, 43, "Movie Generator");
	box->labelcolor(FL_RED);
	box->box(FL_NO_BOX);
	box->labelsize(36);
	box->labelfont(FL_HELVETICA_BOLD);
}

void homeScreen::keywordCB(Fl_Widget* input) {
	//maybe save the value in a string or something no good. using boxCB instead 
	cout << "keyword cb called\n";
	
	if (((Fl_Input*)input)->label() ==  ".") {
		((Fl_Input*)input)->label("");
		string userInput = ((Fl_Input*)input)->value();
		userInput = userInput.substr(userInput.length(), userInput.length());
		
		//((Fl_Input*)input)->static_value(userInput); 
		((Fl_Input*)input)->redraw();
	}

}

void homeScreen::boxCB(Fl_Widget* input, void* data) {
	((Fl_Box*)data)->hide();
}

void homeScreen::keyword() {
	Fl_Input* input = new Fl_Input(326, 150, 149, 30);
	Fl_Box* inputBox = new Fl_Box(326, 150, 149, 30, "Enter a keyword");
	inputBox->labelfont(FL_HELVETICA);
	inputBox->labelsize(16);

	input->when(FL_WHEN_CHANGED);
	input->callback(boxCB, inputBox);
	
	//input->label(".");
	//input->labelcolor(FL_BLACK);

	//input->static_value("Enter a keyword");
	//input->textfont(FL_HELVETICA);
	//input->textsize(16);
	//input->when(FL_WHEN_CHANGED);
	//input->callback(keywordCB);
}


//deletes the label "Genere" when a genre is selected
void homeScreen::genreCB(Fl_Widget* input) {
	((Fl_Choice*)input)->label("");
	int picked = ((Fl_Choice*)input)->value(); //returns index of genre selected
	genreInput = genres[picked];
	cout << "Genre: " << genreInput << endl;
}

void homeScreen::genre() {
	//Fl_Color darkGray{};
	//Fl::set_color(darkGray, 32, 32, 32);

	//Fl_Choice* choice = new Fl_Choice(326, 190, 149, 30, "Genre");
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



void homeScreen::yearCB(Fl_Widget* input, void* data) {
	((Fl_Box*)data)->hide();
	if (((Fl_Input*)input)->x() == 326) {
		yearMinInput = stoi(((Fl_Input*)input)->value());
	}
	else {
		yearMaxInput = stoi(((Fl_Input*)input)->value());
	}
	cout << "yearmin: " << yearMinInput << endl;
	cout << "yearMax: " << yearMaxInput << endl;

	/*string value = ((Fl_Input*)input)->value(); //could do something with this like lock the search button until valid input but..
	if (value.length() > 4) {
		cout << "greater than 4";

	}*/
}


void homeScreen::year() {
	Fl_Color darkGray{};
	Fl::set_color(darkGray, 32, 32, 32);

	/*Fl_Choice* choice = new Fl_Choice(326, 230, 149, 30, "Year");

	choice->align(FL_ALIGN_CENTER);
	choice->labelcolor(FL_BLACK);
	choice->labelsize(18);
	choice->labelfont(FL_HELVETICA_BOLD);

	choice->textcolor(FL_BLACK);
	choice->textfont(FL_HELVETICA);
	choice->textsize(14);*/

	/*Fl_Input* inputLeft = new Fl_Input(326, 230, 70, 30);
	Fl_Input* inputRight = new Fl_Input(405, 230, 70, 30);

	Fl_Box* inputBox = new Fl_Box(320, 230, 149, 30, "Year: From       Year: To");*/

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


void homeScreen::starOn(Fl_Widget* starX, void* data) {
	if (toggle == 1) {
		//cout << "changed == 0";
		((Fl_PNG_Image*)data)->color_average(FL_WHITE, 0.0);
		starX->redraw();	
		//toggle = 0;
	}
	else {
		//toggle = 1;
		//cout << "changed ==1 : " << toggle;
		((Fl_PNG_Image*) data)->color_average(FL_YELLOW, 0.0);
		starX->redraw();
	}
}

void homeScreen::stars(Fl_Widget* starX, void* data) {//figuring out how to link the stars callbacks so that when star3 is pressed the first two are also colored yellow
	int index = 0;
	if (toggle == 0) {
		while (starX != buttons[index]) {
			index++;
		}
	}
	else {
		index = buttons.size()-1;
	}
	
	
	for (int i = 0; i <= index; i++) {
		starOn(buttons[i], ((Fl_PNG_Image*)data));
	}

	if (toggle == 1){
		toggle = 0;
		starsInput = 0;
	}
	else {
		toggle = 1;
		starsInput = index+1;
	}	
	cout << "stars: " << starsInput << endl;
}


void homeScreen::rating() {
	/*Fl_PNG_Image* star = new Fl_PNG_Image("images/ystar.png");
	Fl_Toggle_Button* star1 = new Fl_Toggle_Button(326, 270, 30, 30);
	Fl_Toggle_Button* star2 = new Fl_Toggle_Button(356, 270, 30, 30);
	Fl_Toggle_Button* star3 = new Fl_Toggle_Button(386, 270, 30, 30);
	Fl_Toggle_Button* star4 = new Fl_Toggle_Button(416, 270, 30, 30);
	Fl_Toggle_Button* star5 = new Fl_Toggle_Button(446, 270, 30, 30);*/
	Fl_PNG_Image* star = new Fl_PNG_Image("images/ystar.png");

	Fl_Toggle_Button* star1 = new Fl_Toggle_Button(326, 230, 30, 30);
	Fl_Toggle_Button* star2 = new Fl_Toggle_Button(356, 230, 30, 30);
	Fl_Toggle_Button* star3 = new Fl_Toggle_Button(386, 230, 30, 30);
	Fl_Toggle_Button* star4 = new Fl_Toggle_Button(416, 230, 30, 30);
	Fl_Toggle_Button* star5 = new Fl_Toggle_Button(446, 230, 30, 30);
	buttons = { star1, star2, star3, star4, star5 };

	star->color_average(FL_WHITE, 0.0);

	for (int i = 0; i < buttons.size(); i++) {
		//buttons[i]->type(FL_TOGGLE_BUTTON);
		buttons[i]->value(0);
		buttons[i]->box(FL_NO_BOX);
		buttons[i]->image(star);
		buttons[i]->redraw();
		buttons[i]->when(FL_WHEN_RELEASE);

		//buttons[i]->callback(starOn, star); //works for one star
		buttons[i]->callback(stars, star);//toggles other stars
	}

	/*star1->type(FL_TOGGLE_BUTTON);
	star1->box(FL_UP_BOX);
	star1->image(star);
	star1->redraw();

	star2->type(FL_TOGGLE_BUTTON);
	star2->box(FL_NO_BOX);
	star2->image(star);
	star2->redraw();

	star3->type(FL_TOGGLE_BUTTON);
	star3->box(FL_NO_BOX);
	star3->image(star);
	star3->redraw();

	star4->type(FL_TOGGLE_BUTTON);
	star4->box(FL_NO_BOX);
	star4->image(star);
	star4->redraw();

	star5->type(FL_TOGGLE_BUTTON);
	star5->box(FL_NO_BOX);
	star5->image(star);
	star5->redraw();
	
	star1->when(FL_WHEN_RELEASE);
	star1->callback(star1CB, star);*/
	

}


void homeScreen::sliderCB(Fl_Widget* slider) {
	numResultsInput = ((Fl_Value_Slider*)slider)->value();
	cout << "num of results : " << numResultsInput << endl;
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

void homeScreen::searchCB(Fl_Widget* starX, void* data) {
	cout << "search CB\n";
	primary::getResults();
	cout << "after getResults\n";
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
	//Fl_Button* button = new Fl_Button(326, 270, 149, 30);
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
	if (button->value() == 1) {
		search = true;
	} 
	else {
		search = false;
	}
}
