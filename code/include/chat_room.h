#ifndef CHATROOM_H
#define CHATROOM_H 2016

#include <deque>
#include <string>

#include "constants.h"
#include "message.h"

class ChatRoom
{
public:
	ChatRoom();
	void changeName(char name[MAX_CHATROOM_NAME_LENGTH]);

	//getters
	std::string getName();

private:
	unsigned long chat_room_index; //DISCUSION: could be int?
	char chat_room_name[MAX_CHATROOM_NAME_LENGTH];
	std::deque<Message> message_history; //Using deque because it allows easy push_back, pop_front for history
};

#endif
