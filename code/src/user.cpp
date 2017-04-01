#include "user.h"


using namespace std;

User::User()
{

}

//setters
void User::setName(string desired_name)
{
	if (desired_name.length() > MAX_USER_NICK_SIZE)
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

void User::setStatus(OnlineStatus desired_status)
{
	online_status = desired_status;
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
	return online_status;
}

unsigned long User::getChatRoomIndex()
{
	return chat_room_index;
}

int User::getColorIndex()
{
	return color_index;
}

string User::timeToString()
{
	char* result;
	int temp_time_seconds = time_online_seconds;
	int hours = temp_time_seconds / 3600;
	temp_time_seconds = temp_time_seconds % 3600;
	int minutes = temp_time_seconds / 60;
	int seconds = time_online_seconds % 60;
	sprintf(result, "%2d:%2d:%2d", hours, minutes, seconds);
	string string_result(result);
	return string_result;
}