#ifndef VIEW_H
#define VIEW_H 2016

#include <ncurses.h>
#include <string>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <panel.h>

class View
{
public:
	View();
	void handleInput(char ch);

private:
	WINDOW* windows[3];
	PANEL* panels[3];
	PANEL* top;
	void init_wins(WINDOW **wins, int n);
	void win_show(WINDOW *win, char *label, int label_color);
	void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

	WINDOW* MakeWindow(int Height, int Width, int Yposition, int Xposition, std::string Title);
	void DeleteWindows(std::vector<WINDOW*> & windows);
};

#endif
