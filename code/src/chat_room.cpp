#include "chat_room.h"

using namespace std;

ChatRoom::ChatRoom()
{

}

//getters
string ChatRoom::getName()
{
	string name(chat_room_name); //convert char array to string
	return name;
}