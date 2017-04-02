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
		//--------------------OUTGOING--------------------//

		// Send heartbeat every 2 seconds
		if (seconds % 2 == 0)
		{
			user local_user = chat_building.users[0].convertToOS();
			User.send ( local_user );
		}

		for (ChatRoom cr : chat_building.chat_room_outbox)
		{
			chatRoom.send(cr.convertToOS());
		}
		


		message message_instance;
		Message.send ( message_instance );



		//--------------------INCOMING--------------------//

		chatroom_list_t  cr_list;
		chatRoom.recv ( &cr_list );
		chat_building.updateChatRooms(cr_list);

		user_list_t  u_list;
		User.recv ( &u_list );
		chat_building.updateUsers(u_list);

		message_list_t  m_list;
		Message.recv ( &m_list );
		chat_building.updateMessages(m_list); // Sends messages to model inbox


		seconds++;
		this_thread::sleep_for(chrono::milliseconds(1000));
		ncurses.RefreshGUI();
	}
	std::cout << "normal exit" << '\n';
}