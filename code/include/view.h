#ifndef VIEW_H
#define VIEW_H 2016

#include <ncurses.h>
#include <string>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <panel.h>

enum class Windows { Login = 0, Chatroom = 1, Settings = 2 };

class View
{
public:
	View();
	void initialize();
	void handleInput(char ch);

private:
	const Model& chat_building;

	int chatroom_menu_index;

	WINDOW* makeWindow(int Height, int Width, int Yposition, int Xposition, std::string Title);
	void deleteWindows(std::vector<WINDOW*> & windows);
};

#endif
