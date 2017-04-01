#include "chat_room.h"

using namespace std;

ChatRoom::ChatRoom()
{

}


void ChatRoom::changeName(string desired_name)
{
	chat_room_name = desired_name;
}


void ChatRoom::addMessage(Message message)
{
	//remove from front if history is full
	if (message_history.size >= MAX_CHAT_HISTORY)
	{
		message_history.pop_front();
	}

	message_history.push_back(message);
}

//getters
string ChatRoom::getName()
{
	string name(chat_room_name); //convert char array to string
	return name;
}

unsigned long ChatRoom::getChatRoomIndex()
{
	return chat_room_index;
}

//setters
void ChatRoom::setName(std::string desired_name)
{
	chat_room_name = desired_name;
}