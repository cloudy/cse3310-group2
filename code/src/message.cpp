#include "message.h"

using namespace std;

Message::Message() //have two constructors, one for when creating message and checksum isn't known and one for when receiving message and checksum isn't known
{
	
}

bool Message::isCorrupted()
{
	return !(calculateChecksum() == checksum);
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