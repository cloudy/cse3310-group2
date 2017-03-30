#ifndef MESSAGE_H
#define MESSAGE_H 2016

#include "constants.h"
#include <string>

class Message
{
public:
	Message();
	bool isCorrupted();

	//getters
	std::string getContent();
	unsigned long long getAuthorUUID();
	unsigned long getChatRoomIndex();
	unsigned long long getChecksum();
	std::string getAuthorNickName();

private:
	std::string content;
	unsigned long long author_uuid;
	unsigned long chat_room_index; 
	unsigned long long checksum; 
	std::string author_nick_name;

	unsigned long long calculateChecksum();
};

#endif