#ifndef MODEL_H
#define MODEL_H 2016

#include <vector>

#include "chat_room.h"
#include "user.h"

class Model
{
public:
	Model();
	ChatRoom chat_rooms[10];
	std::vector<User> users; //DISCUSSION: current user will never change, can we just keep our user as first index in vector?
	User* current_user; //DISCUSSION: current user will never change, can we just keep our user as first index in vector?


	User findUser(unsigned long long uuid);
	int calculateNumUsersInChatRoom(unsigned long desired_chatroom_index);

	//getters
	std::vector<User*> getUsersInChatRoom(unsigned long desired_chatroom_index);
};

#endif