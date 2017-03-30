#include "view.h"

#include <cstring>

#define NLINES 10
#define NCOLS 40

using namespace std;

View::View()
{

}

void View::initialize()
{
	//initialize ncurses
	initscr();
	start_color();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();

	//Create the Color Pairs - Global Throughout Program
	init_pair(1, COLOR_BLACK, COLOR_WHITE);	 //Inverse
	init_pair(2, COLOR_GREEN, COLOR_BLACK); //Online
	init_pair(3, COLOR_RED, COLOR_BLACK);   //Offline
	init_pair(4, COLOR_WHITE, COLOR_BLUE);	//Textbox
	init_pair(5, COLOR_WHITE, COLOR_BLACK); //Normal
	init_pair(7, COLOR_WHITE, COLOR_YELLOW); //Element of Interest

											 //Color Pairs for Chat Message History
	init_pair(8, COLOR_YELLOW, COLOR_BLACK);
	init_pair(9, COLOR_BLUE, COLOR_BLACK);
	init_pair(10, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(11, COLOR_CYAN, COLOR_BLACK);
	init_pair(12, COLOR_BLUE, COLOR_WHITE); //selected Index
}

WINDOW* View::makeWindow(int Height, int Width, int Yposition, int Xposition, string Title)
{
	//Create the Window
	WINDOW* returnWindow = newwin(Height, Width, Yposition, Xposition);

	//Draw Borders around the window
	box(returnWindow, 0, 0);

	//Print the title if there is one
	if (Title != "")
	{
		mvwchgat(returnWindow, 1, 1, Width - 2, A_NORMAL, 1, NULL);
		wattron(returnWindow, A_BOLD | COLOR_PAIR(1));
		mvwprintw(returnWindow, 1, Width / 2 - Title.length() / 2, Title.c_str());
		wattroff(returnWindow, A_BOLD | COLOR_PAIR(1));
	}

	refresh();

	return returnWindow;
}

void View::deleteWindows(std::vector<WINDOW*> & windows)
{
	//Clear all of the windows
	for (int i = 0; i < windows.size(); i++)
		delwin(windows[i]);
}


void View::handleInput(char ch)
{	
	switch(ch)
		{	case 9:
				top = (PANEL *)panel_userptr(top);
				top_panel(top);
				break;
		}
		update_panels();
		doupdate();
}
