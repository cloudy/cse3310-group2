#include "model.h"

using namespace std;

Model::Model()
{
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

int Model::calculateNumUsersInChatRoom(unsigned long desired_chatroom_index)
{
	int count = 0;
	for (User& user : users)
	{
		if (user.getChatRoomIndex() == desired_chatroom_index)
		{
			count++;
		}
	}

	return count;
}

//getters

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
