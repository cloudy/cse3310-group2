#ifndef USER_H
#define USER_H 2016

#include "constants.h"

enum class OnlineStatus { Online, Offline };

class User
{
public:
	User();
	void changeName();

private:
	char nick_name[MAX_NICKNAME_LENGTH];
	unsigned long long uuid;
	unsigned long chat_room_index; //DISCUSSION: could be an int?
	OnlineStatus status;
	int ColorIndex;

};

#endif