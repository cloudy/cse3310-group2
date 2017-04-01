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
	std::vector<User> users; //TESTING: can we have our user be first in the vector?
	//User* local_user; //Reference to our actual user

	void populateForTesting();
	bool isUserNew(unsigned long long uuid); //TODO: logic for checking this when get heartbeat, if new, add to users.

	User findUser(unsigned long long uuid);
	int calculateNumUsersInChatRoom(unsigned long desired_chatroom_index);
	std::string calculateCurrentChatRoomName();

	//getters
	std::vector<User> getUsersInChatRoom(unsigned long desired_chatroom_index);
};

#endif