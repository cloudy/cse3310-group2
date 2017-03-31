#include "model.h"

using namespace std;

Model::Model() : local_user(users.at(0))
{

}

User Model::findUser(unsigned long long uuid)
{
	for (User u : users)
	{
		if (u.getUUID() == uuid)
		{
			return u;
		}
	}
}

void Model::populateForTesting() //TODO
{
	string userNames[] = { "Joe", "Robert", "Rivka", "Ramon", "Stephani", "Jewel", "Isaias", "Murray", "Darell", "Alyce", "Carylon", "Dona", "George", "Doug", "Hannah" };
	srand(time(NULL));

	//Create the Fake Users
	User tempUser;
	for (int i = 0, chatID = rand() % 10; i < 15; i++, chatID = rand() % 10)
	{
		tempUser.Name = userNames[rand() % 15];
		if (i % 2 == 0)
			tempUser.Status = Online;
		else tempUser.Status = Offline;
				tempUser.ChatroomName = FakeChatroomNames[chatID];
		tempUser.UserID = i;
		tempUser.ColorIndex = -1;
		tempUser.ChatroomID = chatID;
		Users.push_back(tempUser);
	}

	//Assign the current User as the first user in Users
	currentUser = Users[0];
	vector<User> usersInSameChatroom(0);
	FindOthersinUsersChatroom(usersInSameChatroom);

	//Create the Fake Chat Messages
	Message tempMessage;
	for (int i = 0; i < 3; i++)
	{
		tempMessage.UserName = usersInSameChatroom[rand() % usersInSameChatroom.size()].Name;
		tempMessage.UserID = usersInSameChatroom[rand() % usersInSameChatroom.size()].UserID;
		tempMessage.Message = "";
		for (int j = 0, randomNum = rand() % 144; j < randomNum; j++)
		{
			tempMessage.Message += rand() % 26 + 65;
		}

		ChatMessages.push_back(tempMessage);
	}
}

int Model::calculateNumUsersInChatRoom(unsigned long desired_chatroom_index)
{
	int count = 0;
	for (User& user : users)
	{
		if (user.getChatRoomIndex() == desired_chatroom_index)
		{
			count++;
		}
	}

	return count;
}

//getters

vector<User*> Model::getUsersInChatRoom(unsigned long desired_chatroom_index)
{
	vector<User*> result;
	for (User& user : users)
	{
		if (user.getChatRoomIndex() == desired_chatroom_index)
		{
			result.push_back(&user);
		}
	}
	return result;
}
