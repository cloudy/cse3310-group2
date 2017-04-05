#include "model.h"

using namespace std;
using namespace SuperChat;

Model::Model()
{
	chat_rooms[0] = ChatRoom(0, "PUBLIC");
	for (int i = 1; i < NUM_CHATROOMS; i++)
	{
		string name = "Chatroom #" + to_string(i);
		chat_rooms[i] = ChatRoom(i, name);
	}
}

void Model::updateUsers(vector<user> p_users)
{
	for(user u : p_users)
	{
		User temp_user = User(string(u.nick), u.uuid, u.chatroom_idx);
		int index = findUserIndex(u.uuid);
		if(index == -1)//if user is new
		{
			users.push_back(temp_user);
		}
		//TODO: this is where logic for chatroom time would go
		users[index] = temp_user; //update even if nothing changed, update anyway
	}
}

void Model::updateChatRooms(vector<chatroom> p_chat_rooms)
{
	for(chatroom cr : p_chat_rooms)
	{
		chat_rooms[cr.chatroom_idx].changeName(string(cr.chatroom_name));
	}
}

void Model::updateMessages(vector<message> p_messages)
{
	for(message m : p_messages)
	{
		User temp_user = users[findUserIndex(m.uuid)];
		Message temp_message = Message(temp_user, m.chatroom_idx, string(m.message), m.cksum);
		chat_rooms[temp_message.getChatRoomIndex()].addMessage(temp_message);
	}
}

//returns index of user in users vector. If not in the vector, returns -1, so caller should push to vector
int Model::findUserIndex(unsigned long long uuid)
{
	for(int i = 0; i < users.size(); i++)
	{
		if(users[i].getUUID() == uuid)
		{
			return i;
		}
	}
	
	return -1;
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

void Model::populateForTesting(int selected_user) //TODO
{
	//Create Fake Users
	string user_names[] = { "Joe", "Robert", "Rivka", "Ramon", "Stephani", "Jewel", "Isaias", "Murray", "Darell", "Alyce", "Carylon", "Dona", "George", "Doug", "Hannah" };
	unsigned long long uuids[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	unsigned long chat_room_indexes[] = { 0,0,0,1,1,1,2,2,2,3,3,3,4,4,4 };

	if(selected_user == -1)
	{
		User me = User("me", 0, 0);

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

	else
	{
		User me = User(user_names[selected_user], selected_user, 0);
		users.push_back(me);
	}
}

bool Model::isChatRoomEmpty(unsigned long chatroom_index)
{
	return getUsersInChatRoom(chatroom_index).size();
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
