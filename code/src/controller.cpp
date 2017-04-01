#include "controller.h"
 
#include <thread>
#include <chrono>

using namespace std;

Controller::Controller()
{

}

void Controller::run()
{
	//thread ncurses_thread(&Controller::ncursesLoop, Controller());
	thread open_splice_thread(&Controller::openSpliceLoop, Controller());
	
	//Added these to avoid crash
	//ncurses_thread.join();
	open_splice_thread.join();
}

void Controller::ncursesLoop()
{
	char ch;
	while ((ch = getch()) != KEY_F(1))
	{
		//ncurses.handleInput(ch);
		//printf("ncurses looped\n");
		//this_thread::sleep_for(chrono::milliseconds(1000));
	}
}

void Controller::openSpliceLoop()
{
	int seconds = 0;

	while (true)
	{
		if (seconds %2 == 0)
		{
			printf("opensplice looped\n");
		}
		if (seconds == 40)
		{
			exit(0);
		}
		
		seconds++;
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}
