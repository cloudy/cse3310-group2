#include "view.h"

#include <cstring>

using namespace std;

View::View()
{

}

void View::initialize()//TODO: Create all windows
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
//------------------------WINDOWS------------------------------
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

	//refresh(); //refresh later

	return returnWindow;
}

void View::deleteWindows(std::vector<WINDOW*> & windows)
{
	//Clear all of the windows
	for (int i = 0; i < windows.size(); i++)
		delwin(windows[i]);
}

//- - - - - - - - - - - SETTINGS WINDOW - - - - - - - - - - -
WINDOW* View::createSettingsTopBar()
{
	//Make the window
	WINDOW *window = MakeWindow(LINES, COLS, 0, 0, "");

	//Print the text inside top bar window
	mvwprintw(window, 1, 1, "F1 - Cancel\t\tF2 - Save and Return\t\tF3 - Change Username\t\tF4 - Change Chatroom Name");

	//Refresh the Window
	//wrefresh(window); //refresh later
	return window;
}

WINDOW* View::createSettingsChangeUserName()
{
	//Make the window
	int window_width = COLS / 2;

	WINDOW *window = MakeWindow(10, window_width - 1, 4, 1, "Change UserName");

	//Print Columns "Current UserName" and "New Username"
	wattron(window, A_BOLD);
	mvwprintw(window, 2, window_width / 2 - 8, "Current Username");
	mvwprintw(window, 6, window_width / 2 - 6, "New Username");
	wattroff(window, A_BOLD);

	//Print the Current Username
	wattron(window, COLOR_PAIR(9));
	mvwprintw(window, 3, window_width / 2 - currentUser.Name.length() / 2, currentUser.Name.c_str()); //TODO: cnat print current user when first created, dont know user. separate function?
	wattroff(window, COLOR_PAIR(9));

	//Input box for New Username
	mvwchgat(window, 7, window_width / 2 - 10, 20, A_NORMAL, 4, NULL);
	mvwprintw(window, 8, window_width / 2 - 8, "8 characters only");


	//Refresh the Window
	//wrefresh(window); //refresh later
	return window;
}

WINDOW* View::createSettingsChangeChatroomName()
{
	//Make the window
	int window_width = COLS / 2;

	WINDOW *window = MakeWindow(10, window_width, 4, window_width, "Change Chatroom Name");

	//Print Columns "Current UserName" and "New Username"
	wattron(window, A_BOLD);
	mvwprintw(window, 2, window_width / 2 - 8, "Current Chatroom Name");
	mvwprintw(window, 6, window_width / 2 - 6, "New Chatroom Name");
	wattroff(window, A_BOLD);

	//Print the Current Username
	wattron(window, COLOR_PAIR(9));
	mvwprintw(window, 3, window_width / 2 - currentUser.ChatroomName.length() / 2, currentUser.ChatroomName.c_str()); //TODO: Same problem as user name. call function to update this when window is displayed
	wattroff(window, COLOR_PAIR(9));

	//Input box for New Chatroom name
	mvwchgat(window, 7, window_width / 2 - 8, 20, A_NORMAL, 4, NULL);
	mvwprintw(window, 8, window_width / 2 - 7, "20 characters only");

	//Refresh the Window
	//wrefresh(window); //refresh later
	return window;
}

WINDOW* View::createSettingsAllUsers()
{
	//Make the window
	WINDOW *window = MakeWindow(20, COLS - 2, 14, 1, "All Users");

	//Create the Columns "Users", "Status", "Chatroom", "Time Online"
	wattron(window, A_BOLD);
	mvwprintw(window, 2, 1, "%-8s\t\t\t%-8s\t\t\t%-10s\t\t\t%s", "User", "Status", "Chatroom", "Time Online");
	wattroff(window, A_BOLD);


	//TODO: Same issue. cant show when window is made. call function before showing this.
	//Print the User Profiles
	for (int i = 0; i < Users.size(); i++)
	{
		//Print User Name
		mvwprintw(window, 3 + i, 1, "%-8s\t\t\t", Users[i].Name.c_str());
		if (Users[i].Status == Online)
		{
			//Print Online Status
			wattron(window, COLOR_PAIR(2));
			wprintw(window, "%-8s\t\t\t", "Online");
			wattroff(window, COLOR_PAIR(2));
			//Print ChatroomName and Time Online
			wprintw(window, "%-10s\t\t\t%s", Users[i].ChatroomName.c_str(), "2 Minutes");
		}
		else
		{
			//Print Offline Status
			wattron(window, COLOR_PAIR(3));
			wprintw(window, "%-8s\t\t\t", "Offline");
			wattroff(window, COLOR_PAIR(3));
			//Print Blanks for ChatroomName and Time Online Fields
			wprintw(window, "%-10s\t\t\t%s", "----------", "----------");
		}
	}

	//Refresh the Window
	//wrefresh(window); //refresh later
	return window;
}

//LOGIC
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
