#ifndef CHATROOM_H
#define CHATROOM_H 2016

#include <list>
#include <string>

#include "constants.h"
#include "message.h"
#include "user.h"

class ChatRoom
{
public:
	ChatRoom();
	void changeName(std::string desired_name);
	void addMessage(Message message);

	//getters
	std::string getName();
	unsigned long getChatRoomIndex();

private:
	unsigned long chat_room_index; //DISCUSION: could be int?
	std::string chat_room_name;
	std::list<Message> message_history; //Using list because it allows easy push_back, pop_front for history
};

#endif
