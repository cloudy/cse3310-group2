#ifndef MODEL_H
#define MODEL_H 2016

#include "chat_room.h"
#include "user.h"

class Model
{
public:
	Model();
	void changeChatRoom();
	User lookupUser(unsigned long long uuid);

private:
	ChatRoom chat_rooms[10];
	User users[10];
	User current_user;
	int num_users;
};

#endif