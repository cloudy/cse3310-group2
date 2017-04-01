#ifndef USER_H
#define USER_H 2016

#include <string>
#include "constants.h"
#include "ddsincludes.h"

using namespace SuperChat;

enum OnlineStatus { Online, Offline };

class UserFileDoesNotExist {};

class User
{
public:
	User();
	User(std::string p_nick_name, unsigned long long p_uuid, unsigned long p_chat_room_index);

	static User loadUser(std::string desired_name); //TODO: KARTIK, if file doesn't exist throw userfiledoesnotexist exception that will be cuaght 
	static unsigned long long generateUUID(); //TODO: KARTIK

	void saveUser(); //TODO: KARTIK

	user convertToOS();

	//setters
	void setName(std::string desired_name);
	void setChatRoomIndex(unsigned long index);
	void setStatus(OnlineStatus desired_status);

	//getters
	std::string getNickName();
	unsigned long long getUUID();
	OnlineStatus getStatus();
	unsigned long getChatRoomIndex();
	int getColorIndex();

	std::string timeToString();

private:
	std::string nick_name;
	unsigned long long uuid;
	OnlineStatus online_status;
	unsigned long chat_room_index;

	int time_online_seconds; //TODO: DISCUSSION: logic for incrementing this. do we do ++ for every loop, +2.5 or +5 for each heartbeat
};

#endif