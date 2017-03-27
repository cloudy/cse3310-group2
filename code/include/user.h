#ifndef USER_H
#define USER_H 2016

#include <string>
#include "constants.h"

class User
{
public:
	User();
	void changeName();

private:
	char nick_name[NICK_SIZE_MAX];
	unsigned long long uuid;
	unsigned long chat_room_index; //DISCUSSION: could be an int?
};

#endif