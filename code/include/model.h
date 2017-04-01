#ifndef MODEL_H
#define MODEL_H 2016

#include <vector>

#include "chat_room.h"
#include "user.h"

class Model
{
public:
	Model();
	void changeChatRoom();
	//User lookupUser(unsigned long long uuid); 

private:
	ChatRoom chat_rooms[10];
	std::vector<User> users; //DISCUSSION: Should this be a vector
	User current_user;
};

#endif