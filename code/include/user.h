#ifndef USER_H
#define USER_H 2016

#include <string>
#include "constants.h"

enum OnlineStatus { Online, Offline };

class UserFileDoesNotExist {};

class User
{
public:
	User();

	static User loadUser(); //TODO: KARTIK, if file doesn't exist throw userfiledoesnotexist exception that will be cuaght
	static void saveUser(); //TODO: KARTIK
	static unsigned long long generateUUID(); //TODO: KARTIK

	//TODO: .toStruct for OpenSplice

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
	int color_index;

	int time_online_seconds; //TODO: DISCUSSION: logic for incrementing this. do we do ++ for every loop, +2.5 or +5 for each heartbeat
};

#endif