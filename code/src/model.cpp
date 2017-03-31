#include "model.h"

using namespace std;

Model::Model()
{
}

void Model::moveUserToNewChatRoom(User user, ChatRoom destination_chat_room)
{
	//remove from old chatroom
	chat_rooms[user.getChatRoomIndex()].removeUser(user);

	//update chatroom_index
	user.setChatRoomIndex(destination_chat_room.getChatRoomIndex());

	//add to new chatroom
	chat_rooms[user.getChatRoomIndex()].addUser(user);
}

User Model::findUser(unsigned long long uuid)
{
	for (User u : users)
	{
		if (u.getUUID() == uuid)
		{
			return u;
		}
	}
}

//getters
string Model::getChatroomName(unsigned long desired_chatroom_index)
{
	return chat_rooms[desired_chatroom_index].getName();
}

vector<User*> Model::getUsersInChatRoom(unsigned long desired_chatroom_index)
{
	vector<User*> result;
	for (User& user : users)
	{
		if (user.getChatRoomIndex() == desired_chatroom_index)
		{
			result.push_back(&user);
		}
	}
	return result;
}
