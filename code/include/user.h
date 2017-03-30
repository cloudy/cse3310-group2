#ifndef USER_H
#define USER_H 2016

#include "ddsincludes.h"
#include "constants.h"

enum class OnlineStatus { Online, Offline };

using namespace DDS;
using namespace SuperChat;

typedef std::vector<user> user_list_t;

class User
{
public:
	User(char *topic_name);
	~User();
	void send(user userInstance);
	void recv(user_list_t* userList);
	void changeName();

private:
	char nick_name[MAX_NICKNAME_LENGTH];
	unsigned long long uuid;
	unsigned long chat_room_index; //DISCUSSION: could be an int?
	OnlineStatus status;
	int ColorIndex;

	// OpenSplice Integration
	DDSEntityManager em;
	userDataWriter_var Writer;
	userDataReader_var Reader;

};

#endif