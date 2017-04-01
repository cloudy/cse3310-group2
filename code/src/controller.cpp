#include "controller.h"
 
#include <thread>
#include <chrono>

using namespace std;

Controller::Controller() : chat_building(Model()), ncurses(View(chat_building)) {}

void Controller::run()
{
	thread ncurses_thread(&Controller::ncursesLoop, Controller());
	thread open_splice_thread(&Controller::openSpliceLoop, Controller());
	
	//Added these to avoid crash
	ncurses_thread.join();
	open_splice_thread.join();
}

void Controller::ncursesLoop()
{
	ncurses.StartGUI();
}
//dont do OS stuff until View.logged_in is true
void Controller::openSpliceLoop() 
{
	while (true)
	{
		printf("opensplice looped\n");
		this_thread::sleep_for(chrono::milliseconds(2500));
	}
}
