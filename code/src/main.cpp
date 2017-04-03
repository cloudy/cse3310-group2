#include <stdlib.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

#include "model.h"
#include "view.h"
#include "osdds_io.h"

using namespace DDS;
using namespace SuperChat;

//global data
Model chat_building;
std::mutex model_mutex;
View ncurses;

void run();
void ncursesLoop();
void openSpliceLoop();

int main(int argc, char* argv[])
{
	int selection = (argc < 2) ? -1 : stoi(string(argv[1]));

	chat_building.populateForTesting(selection);
	run();
	return 0;
}

void run()
{
	thread ncurses_thread(ncursesLoop);
	thread open_splice_thread(openSpliceLoop);

	//Added these to avoid crash
	ncurses_thread.join();
	open_splice_thread.join();
}

void ncursesLoop()
{
	ncurses.StartGUI();
}

//dont do OS stuff until View.logged_in is true
void openSpliceLoop()
{

	// instantiate classes
	chatroom_data chatroom_IO ( (char*) "chatroom" );
	user_data user_IO ( (char*) "user" );
	message_data message_IO ( (char*) "msg" );
	int seconds = 0;

	model_mutex.lock();
	while (chat_building.is_running)
	{
		model_mutex.unlock();
		model_mutex.lock();
		bool is_logged_in = chat_building.logged_in;
		model_mutex.unlock();
		if(is_logged_in)
		{
			//--------------------OUTGOING--------------------//
			model_mutex.lock();
			// Send heartbeat every 2 seconds
			if (seconds % 10 == 0)
			{
				user_IO.send ( chat_building.users[0].convertToOS() );
			}
			
			// Send chatroom outbox
			for (ChatRoom cr : chat_building.chat_room_outbox)
			{
				chatroom_IO.send(cr.convertToOS());
			}
			chat_building.chat_room_outbox.clear(); // Don't send the same thing from outbox more than once

			// Send message outbox
			for (Message m : chat_building.message_outbox)
			{
				message_IO.send(m.convertToOS());
			}
			chat_building.message_outbox.clear(); 

			//--------------------INCOMING--------------------//

			// Receive chatrooms
			chatroom_list_t  cr_list;
			chatroom_IO.recv ( &cr_list );
			chat_building.updateChatRooms(cr_list);

			// Receive users
			user_list_t  u_list;
			user_IO.recv ( &u_list );
			chat_building.updateUsers(u_list);

			// Receive messages
			message_list_t  m_list;
			message_IO.recv ( &m_list );
			chat_building.updateMessages(m_list); // Sends messages to model inbox

			//--------------------LOGIC--------------------//
			for(User& u : chat_building.users)
			{
				u.time_online_seconds++;
			}

			model_mutex.unlock();
			ncurses.RefreshGUI();

			seconds++;
		}

		this_thread::sleep_for(chrono::milliseconds(1000));
	}
	std::cout << "normal exit" << '\n';
}