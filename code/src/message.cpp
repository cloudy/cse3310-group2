#include "message.h"

using namespace std;

//constructor for messages created locally, we calculate checksum ourself
Message::Message(User p_user, std::string p_content) : 
	author_nick_name(p_user.getNickName()), author_uuid(p_user.getUUID()), chat_room_index(p_user.getChatRoomIndex()), content(p_content), checksum(calculateChecksum()) {}

//constructor for recevied messages when we are given a checksum
Message::Message(std::string p_author_nick_name, unsigned long long p_author_uuid, unsigned long p_chat_room_index, std::string p_content, unsigned long long p_checksum) : 
	author_nick_name(p_author_nick_name), author_uuid(p_author_uuid), chat_room_index(p_chat_room_index), content(p_content), checksum(p_checksum) {}

message Message::convertToOS()
{
	message result;
	result.message = content.c_str();
	result.uuid = author_uuid;
	result.cksum = checksum;
	result.chatroom_idx  = chat_room_index;
	return result;
}

bool Message::isCorrupted()
{
	return !(calculateChecksum() == checksum);
}

unsigned long long Message::calculateChecksum()
{
	return 0;
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