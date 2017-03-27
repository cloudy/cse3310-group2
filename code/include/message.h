#ifndef MESSAGE_H
#define MESSAGE_H 2016

#include "constants.h"

class Message
{
public:
	Message();
	void publish();

private:
	char content[MESSAGE_SIZE_MAX];
	unsigned long long user_uuid; //DISCUSSION: For now, I'll keep this type same as interface
	unsigned long long checksum; //DISCUSSION: For now, I'll keep this type same as interface
	unsigned long chat_room_index; //DISCUSSION: could be int?
};

#endif