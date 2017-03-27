#include "view.h"

#include <cstring>

#define NLINES 10
#define NCOLS 40

using namespace std;

View::View()
{
	// Initialize curses
   	initscr();
	start_color();
	cbreak();
    	keypad(stdscr, TRUE);

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
	init_pair(10, COLOR_MAGENTA,COLOR_BLACK);
	init_pair(11, COLOR_CYAN, COLOR_BLACK);
	init_pair(12, COLOR_BLUE, COLOR_WHITE); //selected Index

	init_wins(windows, 3);

	/* Attach a panel to each window */ 	/* Order is bottom up */
	panels[0] = new_panel(windows[0]); 	/* Push 0, order: stdscr-0 */
	panels[1] = new_panel(windows[1]); 	/* Push 1, order: stdscr-0-1 */
	panels[2] = new_panel(windows[2]); 	/* Push 2, order: stdscr-0-1-2 */

	/* Set up the user pointers to the next panel */
	set_panel_userptr(panels[0], panels[1]);
	set_panel_userptr(panels[1], panels[2]);
	set_panel_userptr(panels[2], panels[0]);

	/* Update the stacking order. 2nd panel will be on top */
	update_panels();

	/* Show it on the screen */
	attron(COLOR_PAIR(4));
	mvprintw(LINES - 2, 0, "Use tab to browse through the windows (F1 to Exit)");
	attroff(COLOR_PAIR(4));
	doupdate();

	top = panels[2];
}

void View::init_wins(WINDOW **wins, int n)
{	int x, y, i;
	char label[80];

	y = 2;
	x = 10;
	for(i = 0; i < n; ++i)
	{	wins[i] = newwin(NLINES, NCOLS, y, x);
		sprintf(label, "Window Number %d", i + 1);
		win_show(wins[i], label, i + 1);
		y += 3;
		x += 7;
	}
}

void View::win_show(WINDOW *win, char *label, int label_color)
{	int startx, starty, height, width;

	getbegyx(win, starty, startx);
	getmaxyx(win, height, width);

	box(win, 0, 0);
	mvwaddch(win, 2, 0, ACS_LTEE); 
	mvwhline(win, 2, 1, ACS_HLINE, width - 2); 
	mvwaddch(win, 2, width - 1, ACS_RTEE); 
	
	print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
}

void View::print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
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
