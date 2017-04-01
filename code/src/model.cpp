#include "model.h"

using namespace std;

Model::Model()
{
	chat_rooms[0] = ChatRoom(0, "public");
	for (int i = 1; i < NUM_CHATROOMS; i++)
	{
		string name = "Chatroom #" + to_string(i);
		chat_rooms[i] = ChatRoom(i, name);
	}
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

string Model::calculateCurrentChatRoomName()
{
	return chat_rooms[users[0].getChatRoomIndex()].getName();
}

bool Model::isUserNew(unsigned long long uuid)
{
	for (User u : users)
	{
		if (u.getUUID() == uuid)
		{
			return false;
		}
	}
	return true;
}

void Model::populateForTesting() //TODO
{
	//Create Fake Users
	string user_names[] = { "Joe", "Robert", "Rivka", "Ramon", "Stephani", "Jewel", "Isaias", "Murray", "Darell", "Alyce", "Carylon", "Dona", "George", "Doug", "Hannah" };
	unsigned long long uuids[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	unsigned long chat_room_indexes[] = { 0,0,0,1,1,1,2,2,2,3,3,3,4,4,4 };
	User me = User("me", 0, 0);
	users.push_back(me);
	for (int i = 0; i < 15; i++)
	{
		users.push_back(User(user_names[i], uuids[i], chat_room_indexes[i]));
		users[i].time_online_seconds = i * 37;
	}

	//Create Fake Chat Messages
	string message_contents[] = { "Hello", "You Still there?", "I guess nice guys finish last." };
	for (int i = 0; i < 15; i++)
	{
		chat_rooms[users[i].getChatRoomIndex()].addMessage(Message(users[i], message_contents[0]));
		chat_rooms[users[i].getChatRoomIndex()].addMessage(Message(users[i], message_contents[1]));
		chat_rooms[users[i].getChatRoomIndex()].addMessage(Message(users[i], message_contents[2]));
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

vector<User> Model::getUsersInChatRoom(unsigned long desired_chatroom_index)
{
	vector<User> result;
	for (User user : users)
	{
		if (user.getChatRoomIndex() == desired_chatroom_index)
		{
			result.push_back(user);
		}
	}
	return result;
}
