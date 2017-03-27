#ifndef CHATROOM_H
#define CHATROOM_H 2016

#include "constants.h"

class ChatRoom
{
public:
	ChatRoom();
	void changeName(char name[CHATROOM_NAME_MAX]);

private:
	unsigned long chat_room_index; //DISCUSION: could be int?
	char chat_room_name[CHATROOM_NAME_MAX];
};

#endif