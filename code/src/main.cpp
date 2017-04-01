#include <stdlib.h>
#include <iostream>
#include <thread>
#include <chrono>

#include "model.h"
#include "view.h"

Model chat_building;
View ncurses(chat_building);

void run();
void ncursesLoop();
void openSpliceLoop();

int main(int argc, char* argv[])
{
	chat_building.populateForTesting();
	run();
	return 0;
}

void run()
{
	printf("Address of model in main before thread is %p\n", &chat_building);

	thread ncurses_thread(ncursesLoop);
	thread open_splice_thread(openSpliceLoop);

	//Added these to avoid crash
	ncurses_thread.join();
	open_splice_thread.join();
}

void ncursesLoop()
{
	printf("Address of model in main after thread is %p\n", &chat_building);
	ncurses.StartGUI();
}
//dont do OS stuff until View.logged_in is true
void openSpliceLoop()
{
	while (true)
	{
		//printf("opensplice looped\n");
		this_thread::sleep_for(chrono::milliseconds(2500));
	}
}