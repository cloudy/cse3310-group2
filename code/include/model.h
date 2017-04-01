#ifndef MODEL_H
#define MODEL_H 2016

#include <vector>

#include "chat_room.h"
#include "user.h"
#include "message.h"

class Model
{
public:
	Model();

	ChatRoom chat_rooms[10];
	std::vector<User> users; //TESTING: can we have our user be first in the vector?

	//vectors that will be accessed in OS loop of outgoing things to be published
	std::vector<ChatRoom> chat_room_outbox;
	std::vector<Message> message_outbox;

	void populateForTesting();
	bool isUserNew(unsigned long long uuid); //TODO: logic for checking this when get heartbeat, if new, add to users.

	User findUser(unsigned long long uuid);
	int calculateNumUsersInChatRoom(unsigned long desired_chatroom_index);
	std::string calculateCurrentChatRoomName();

	//getters
	std::vector<User> getUsersInChatRoom(unsigned long desired_chatroom_index);
};

#endif