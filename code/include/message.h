#ifndef MESSAGE_H
#define MESSAGE_H 2016

#include <string>

#include "constants.h"
#include "user.h"
#include "ddsincludes.h"

using namespace SuperChat;

class Message
{
public:
	Message(User p_user, std::string p_content);
	Message(User p_user, unsigned long p_chat_room_index, std::string p_content, unsigned long long p_checksum);
	bool isCorrupted(string message);

	message convertToOS();

	unsigned long long calculateChecksum(string message); //TODO: KARTIK

	//getters
	std::string getContent();
	unsigned long long getAuthorUUID();
	unsigned long getChatRoomIndex();
	unsigned long long getChecksum();
	std::string getAuthorNickName();
	//TODO: .toStruct for OpenSplice

private:
	std::string content;
	unsigned long long author_uuid;
	unsigned long chat_room_index; 
	unsigned long long checksum; 
	std::string author_nick_name;

	
};

#endif