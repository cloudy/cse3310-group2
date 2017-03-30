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
vector<string> Model::getAllChatroomNames() const
{
	vector<string> chat_room_names;
	for (ChatRoom cr : chat_rooms)
	{
		chat_room_names.push_back(cr.getName());
	}
}
