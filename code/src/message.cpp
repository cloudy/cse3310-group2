#include "message.h"
#include <zlib.h>
#include <string>
#include <iostream>

using namespace std;

//constructor for messages created locally, we calculate checksum ourself
Message::Message(User p_user, std::string p_content) : 
	author_nick_name(p_user.getNickName()), author_uuid(p_user.getUUID()), chat_room_index(p_user.getChatRoomIndex()), content(p_content), checksum(calculateChecksum(p_content)) {}

//constructor for recevied messages when we are given a checksum
Message::Message(User p_user, unsigned long p_chat_room_index, std::string p_content, unsigned long long p_checksum) : 
	author_nick_name(p_user.getNickName()), author_uuid(p_user.getUUID()), chat_room_index(p_chat_room_index), content(p_content), checksum(p_checksum) {}

message Message::convertToOS()
{
	message result;
	strcpy(result.message, content.c_str());
	result.uuid = author_uuid;
	result.cksum = checksum;
	result.chatroom_idx  = chat_room_index;
	return result;
}

bool Message::isCorrupted(string message)
{
	return !(calculateChecksum(message) == checksum);
}

unsigned long long Message::calculateChecksum(std::string message)
{
	unsigned long long crc;
	crc = crc32(0L, Z_NULL, 0);
	crc = crc32(crc, (const unsigned char*) message.c_str(), message.length() );
	return crc;
}

//getters
string Message::getContent()
{
	return content;
}

unsigned long long Message::getAuthorUUID()
{
	return author_uuid;
}

unsigned long Message::getChatRoomIndex()
{
	return chat_room_index;
}

unsigned long long Message::getChecksum()
{
	return checksum;
}

string Message::getAuthorNickName()
{
	return author_nick_name;
}