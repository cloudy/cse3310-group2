#include "user.h"


using namespace std;

User::User()
{

}

//setters
void User::setName(string desired_name)
{
	if (desired_name.length() > MAX_NICKNAME_LENGTH)
	{
		throw runtime_error("Tried to set name that was too long.");
	}
	nick_name = desired_name;
}

void User::setChatRoomIndex(unsigned long index)
{
	if (index < 0 || index > NUM_CHATROOMS)
	{
		throw runtime_error("Tried to change to invalid chatroom index.");
	}

	chat_room_index = index;
}

//getters
string User::getNickName()
{
	return nick_name;
}

unsigned long long User::getUUID()
{
	return uuid;
}

OnlineStatus User::getStatus()
{
	return status;
}

unsigned long User::getChatRoomIndex()
{
	return chat_room_index;
}

int User::getColorIndex()
{
	return color_index;
}