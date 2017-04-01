#include <stdlib.h>
#include <iostream>
#include <thread>
#include <chrono>

#include "model.h"
#include "view.h"
#include "osdds_io.h"

using namespace DDS;
using namespace SuperChat;

Model chat_building;
View ncurses(chat_building);

void run();
void ncursesLoop();
void openSpliceLoop();

bool exit_flag = false;

void ctrlc ( int )
{
   exit_flag = true;
}

int main(int argc, char* argv[])
{
	chat_building.populateForTesting();
	run();
	return 0;
}

void run()
{
	//printf("Address of model in main before thread is %p\n", &chat_building);

	thread ncurses_thread(ncursesLoop);
	//thread open_splice_thread(openSpliceLoop);

	//Added these to avoid crash
	ncurses_thread.join();
	//open_splice_thread.join();
}

void ncursesLoop()
{
	//printf("Address of model in main after thread is %p\n", &chat_building);
	ncurses.StartGUI();
}
//dont do OS stuff until View.logged_in is true
void openSpliceLoop()
{

	signal ( SIGINT, ctrlc );

	// instantiate classes
	chatroom_data chatRoom ( (char*) "chatroom" );
	user_data User ( (char*) "user" );
	message_data Message ( (char*) "msg" );

	// set up some variables
	int seconds = 0;

	// the main loop
	for (; !exit_flag;)
	{
		// send out each topic according to the rules of superchat
		// first is chatroom
		{
			if (seconds % 60 == 0)
			{
				// once a minute change the chatroom name
				chatroom messageInstance;
				messageInstance.chatroom_idx = 1;
				if ( seconds % 120 )
				{
					strncpy ( messageInstance.chatroom_name, "The pleasures", sizeof ( messageInstance.chatroom_name ) );
				}
				else
				{
					strncpy ( messageInstance.chatroom_name, "The !pleasures", sizeof ( messageInstance.chatroom_name ) );
				}
				chatRoom.send ( messageInstance );
			}
		}
		// user topic
		{
			user messageInstance;
			messageInstance.uuid = 123;
			strncpy ( messageInstance.nick, "Donny", sizeof ( messageInstance.nick ) );
			messageInstance.chatroom_idx = 0;  // public
			if (seconds % 2 == 0)
			{
				// 2.0 is less than 2.5, so this is still compliant
				User.send ( messageInstance );
			}
		}
		// message topic
		{
			message messageInstance;
			if (seconds % 15 == 0)
			{
				if ( seconds % 30 == 0 )
				{
					strncpy ( messageInstance.message, "This is the A message.", sizeof ( messageInstance.message ) );
				}
				else
				{
					strncpy ( messageInstance.message, "This is the B message.", sizeof ( messageInstance.message ) );
				}
				messageInstance.uuid = 123;
				messageInstance.chatroom_idx = 0;
				messageInstance.cksum = 0;
				Message.send ( messageInstance );
			}
		}

		// handle any input coming in
		{
			chatroom_list_t  List;
			chatRoom.recv ( &List );
			for (unsigned int i = 0; i < List.size (); i++)
			{
				std::cout << "recieved new chatroom name " << List[i].chatroom_name <<
				          " chatroom index " << List[i].chatroom_idx << '\n';
			}
		}
		{
			user_list_t  List;
			User.recv ( &List );
			for (unsigned int i = 0; i < List.size (); i++)
			{
				std::cout << "recieved user " << List[i].nick <<
				          " chatroom index " << List[i].chatroom_idx << '\n';
			}
		}
		{
			message_list_t  List;
			Message.recv ( &List );
			for (unsigned int i = 0; i < List.size (); i++)
			{
				std::cout << "recieved user " << List[i].message <<
				          " chatroom index " << List[i].chatroom_idx << '\n';
			}
		}
		seconds++;
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
	std::cout << "normal exit" << '\n';

//	chatroom_data chatRoom ( (char*) "chatroom" );
//	user_data User ( (char*) "user" );
//	message_data Message ( (char*) "msg" );
//
//	while (true)
//	{
//		printf("opensplice looped\n");
//		this_thread::sleep_for(chrono::milliseconds(1000));
//	}
}