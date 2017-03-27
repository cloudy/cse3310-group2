#include "controller.h"
 
#include <thread>
#include <chrono>

using namespace std;

Controller::Controller()
{

}

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
	while (true)
	{
		printf("ncurses looped\n");
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}

void Controller::openSpliceLoop()
{
	while (true)
	{
		printf("opensplice looped\n");
		this_thread::sleep_for(chrono::milliseconds(2500));
	}
}