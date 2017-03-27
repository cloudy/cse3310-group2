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

private:
	WINDOW* MakeWindow(int Height, int Width, int Yposition, int Xposition, string Title);
	void DeleteWindows(vector<WINDOW*> & windows)
};

#endif