#ifndef USER_H
#define USER_H 2016

#include <string>
#include "constants.h"

enum class OnlineStatus { Online, Offline };

class User
{
public:
	User();

	//setters
	void setName(std::string desired_name);
	void setChatRoomIndex(unsigned long index);
	void setStatus(OnlineStatus desired_status);//TODO

	//getters
	std::string getNickName();
	unsigned long long getUUID();
	OnlineStatus getStatus();
	unsigned long getChatRoomIndex();
	int getColorIndex();

private:
	std::string nick_name;
	unsigned long long uuid;
	OnlineStatus online_status;
	unsigned long chat_room_index; //DISCUSSION: could be an int?
	int color_index;
};

#endif