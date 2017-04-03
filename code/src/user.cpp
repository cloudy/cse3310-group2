#include "user.h"

#include <stdexcept>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//default constructor for creating our local user at very beginning of program when nothing is know about him
User::User()
{

}

//this will likely only be used for when we receive heartbeat from new user and these are known
User::User(std::string p_nick_name, unsigned long long p_uuid, unsigned long p_chat_room_index) :
	nick_name(p_nick_name), uuid(p_uuid), chat_room_index(p_chat_room_index), online_status(Online), time_online_seconds(0) {} //by default, a new user will be online and their duration is 0 seconds

user User::convertToOS()
{
	user result;
	strcpy(result.nick, nick_name.c_str());
    result.uuid = uuid;
    result.chatroom_idx = chat_room_index;
    return result;
}

//setters
void User::setName(string desired_name)
{
	try
	{
		if (desired_name.length() > MAX_USER_NICK_SIZE)
		{
			throw runtime_error("Tried to set name that was too long.");
		}

		nick_name = desired_name;
	}

	catch (const std::exception& e)
	{
		//printf(e.what());
	}
}

void User::setChatRoomIndex(unsigned long index)
{
	try
	{
		if (index < 0 || index > NUM_CHATROOMS)
		{
			throw runtime_error("Tried to change to invalid chatroom index.");
		}

		chat_room_index = index;
	}

	catch (const std::exception& e)
	{
		//printf(e.what());
	}
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

string User::timeToString()
{
	char result[10];
	int temp_time_seconds = time_online_seconds;
	int hours = temp_time_seconds / 3600;
	temp_time_seconds = temp_time_seconds % 3600;
	int minutes = temp_time_seconds / 60;
	int seconds = time_online_seconds % 60;
	sprintf(result, "%02d:%02d:%02d", hours, minutes, seconds);
	string string_result(result);
	return string_result;
}

static unsigned long long generateUUID()
{
	boost::uuids::uuid uuid = boost::uuids::random_generator()();
	unsigned long long x;
	memcpy ( &x, &uuid, sizeof (x) );
	return x;
}

static user loadUser(std::string desired_name)
{
	user found_user;
	ifstream read_User;
	string found_uuid;
	try
	{
		read_User.open("User_data.txt");
		strcpy(found_user.nick, desired_name.c_str());
		getline(read_User, found_uuid, '~');
		std::string::size_type sz = 0;
		found_user.uuid = std::stoull(found_uuid, &sz, 0);
		found_user.chatroom_idx = 0;
		return found_user;
	}
	catch (exception& userfiledoesnotexist)
	{
		strcpy(found_user.nick, desired_name.c_str());
		found_user.uuid = generateUUID();
		found_user.chatroom_idx = 0;
		return found_user;
	}

	read_User.close();
}

void saveUser(user user_to_be_saved)
{
	ofstream write_User;
	write_User.open("User_data.txt");
	write_User << user_to_be_saved.uuid << '~' << endl;
	write_User.close();
}