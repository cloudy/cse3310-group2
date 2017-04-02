#ifndef VIEW_H
#define VIEW_H

#include <ncurses.h>
#include <string>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <panel.h>

#include "model.h"

//Global Data
namespace GUI_DATA
{
	enum class Window { Login, Chatroom, Settings };
}

using namespace std;
using namespace GUI_DATA;

class View //CHANGE: Basically moved everything into a class. Made it easier to access model as an common attribute rather than passing reference between each function. 
{
private:
	Model& chat_building;
public:
	//CHANGE: Constructor; basically gives you reference to the model that controller is using so any changes you make to it here will be reflected in the model used by controller class.
	View(Model& parameter_chat_building) : chat_building(parameter_chat_building), current_window(Window::Login) {}; //this assigns model in this class to the model in controller when an instance of this class is made in controller.

	Window current_window;

	//- - - - - - - - - - - CALCULATION FUNCTIONS - - - - - - - - - - -
	WINDOW* MakeWindow(int Height, int Width, int Yposition, int Xposition, string Title)
	{
		//Create the Window
		WINDOW* returnWindow = newwin(Height, Width, Yposition, Xposition);

		//Draw Borders around the window
		box(returnWindow, 0, 0);

		//Print the title if there is one
		if (Title != "")
		{
			mvwchgat(returnWindow, 1, 1, Width - 2, A_NORMAL, 1, NULL);
			wattron(returnWindow, A_BOLD | COLOR_PAIR(1));
			mvwprintw(returnWindow, 1, Width / 2 - Title.length() / 2, Title.c_str());
			wattroff(returnWindow, A_BOLD | COLOR_PAIR(1));
		}

		refresh();

		return returnWindow;
	}

	//- - - - - - - - - - - SETTINGS WINDOW - - - - - - - - - - -

	void Settings_TopBar()
	{
		//Make the window
		WINDOW *window = MakeWindow(LINES, COLS, 0, 0, "");

		//Print the text inside top bar window
		mvwprintw(window, 1, 1, "ENTER - Save and Return\t\tF4 - Change User Nick\t\tF5 - Change Chatroom Name\t\tF6 - Cancel and Return");

		//Refresh the Window
		wrefresh(window);
		delwin(window);
	}

	void Settings_ChangeUserName(string new_nick)
	{
		//Make the window
		int window_width = COLS / 2;

		WINDOW *window = MakeWindow(10, window_width - 1, 4, 1, "Change User Nick");

		//Print Columns "Current UserName" and "New Username"
		wattron(window, A_BOLD);
		mvwprintw(window, 2, window_width / 2 - 8, "Current Username");
		mvwprintw(window, 6, window_width / 2 - 6, "New Username");
		wattroff(window, A_BOLD);

		//Print the Current Username
		wattron(window, COLOR_PAIR(9));
		string current_user_name = chat_building.users[0].getNickName(); //CHANGE: access through model
		mvwprintw(window, 3, window_width / 2 - current_user_name.length() / 2, current_user_name.c_str()); //CHANGE: access through model
		wattroff(window, COLOR_PAIR(9));

		//Input box for New Username
		mvwchgat(window, 7, window_width / 2 - 10, 20, A_NORMAL, 4, NULL);
		mvwprintw(window, 8, window_width / 2 - 8, "%d characters only", MAX_USER_NICK_SIZE);

		wattron(window, COLOR_PAIR(4));
		mvwprintw(window, 7, window_width / 2 - 10, new_nick.c_str());
		wattroff(window, COLOR_PAIR(4));

		//Refresh the Window
		wrefresh(window);
		delwin(window);
	}

	void Settings_ChangeChatroomName(string new_chatroom_name)
	{
		//Make the window
		int window_width = COLS / 2;

		WINDOW *window = MakeWindow(10, window_width, 4, window_width, "Change Chatroom Name");

		//Print Columns "Current UserName" and "New Username"
		wattron(window, A_BOLD);
		mvwprintw(window, 2, window_width / 2 - 8, "Current Chatroom Name");
		mvwprintw(window, 6, window_width / 2 - 6, "New Chatroom Name");
		wattroff(window, A_BOLD);

		//Print the Current Username
		wattron(window, COLOR_PAIR(9));
		string current_user_chatroom_name = chat_building.calculateCurrentChatRoomName(); //CHANGE: access through model
		mvwprintw(window, 3, window_width / 2 - current_user_chatroom_name.length() / 2, current_user_chatroom_name.c_str()); //CHANGE: access through model
		wattroff(window, COLOR_PAIR(9));

		//Input box for New Chatroom name
		mvwchgat(window, 7, window_width / 2 - 8, 20, A_NORMAL, 4, NULL);
		mvwprintw(window, 8, window_width / 2 - 7, "%d characters only", MAX_CHATROOM_NAME_SIZE);

		wattron(window, COLOR_PAIR(4));
		mvwprintw(window, 7, window_width / 2 - 8, new_chatroom_name.c_str());
		wattroff(window, COLOR_PAIR(4));

		//Refresh the Window
		wrefresh(window);
		delwin(window);
	}

	void Settings_AllUsers()
	{
		//Make the window
		WINDOW *window = MakeWindow(20, COLS - 2, 14, 1, "All Users");

		//Create the Columns "Users", "Status", "Chatroom", "Time Online"
		wattron(window, A_BOLD);
		mvwprintw(window, 2, 1, "%-8s\t\t\t%-8s\t\t\t%-10s\t\t\t%s", "User", "Status", "Chatroom", "Time Online");
		wattroff(window, A_BOLD);

		//Print the User Profiles
		for (int i = 0; i < chat_building.users.size(); i++) //CHANGE: access through model
		{
			User temp_user = chat_building.users[i];  //CHANGE: access through model
													  //Print User Name
			mvwprintw(window, 3 + i, 1, "%-8s\t\t\t", temp_user.getNickName().c_str());  //CHANGE: access through model
			if (temp_user.getStatus() == Online)
			{
				//Print Online Status
				wattron(window, COLOR_PAIR(2));
				wprintw(window, "%-8s\t\t\t", "Online");
				wattroff(window, COLOR_PAIR(2));
				//Print ChatroomName and Time Online
				wprintw(window, "%-10s\t\t\t%s", chat_building.chat_rooms[temp_user.getChatRoomIndex()].getName().c_str(), temp_user.timeToString().c_str()); //CHANGE: access through model and added time functionality
			}
			else
			{
				//Print Offline Status
				wattron(window, COLOR_PAIR(3));
				wprintw(window, "%-8s\t\t\t", "Offline");
				wattroff(window, COLOR_PAIR(3));
				//Print Blanks for ChatroomName and Time Online Fields
				wprintw(window, "%-10s\t\t\t%s", "----------", "----------");
			}
		}

		//Refresh the Window
		wrefresh(window);
		delwin(window);
	}

	void Settings_Draw()
	{
		string new_user_nick = chat_building.users[0].getNickName(), new_chatroom_name = chat_building.calculateCurrentChatRoomName();  //CHANGE: access through model
		int input_char;

		Settings_TopBar();
		Settings_ChangeUserName("New Nick");
		Settings_ChangeChatroomName("New Chatroom Name");
		Settings_AllUsers();

		int SaveAndReturn = 10; //Enter key
		int ChangeUserNickFKey = KEY_F(4);
		int ChangeChatroomNameFKey = KEY_F(5);
		int Cancel = KEY_F(6); 

		int window_char, input;
		input = getch();
		while (window_char = input)
		{
			//Change the User's Name
			if (window_char == ChangeUserNickFKey)
			{
				new_user_nick = "";
				Settings_ChangeUserName(new_user_nick);

				input = getch();
				while ((input > 31 && input < 127) && new_user_nick.size() < MAX_USER_NICK_SIZE)
				{
					new_user_nick += input;
					Settings_ChangeUserName(new_user_nick);
					input = getch();
				}
			}
			//Change the Chatroom Name
			else if (window_char == ChangeChatroomNameFKey)
			{
				new_chatroom_name = "";
				Settings_ChangeChatroomName(new_chatroom_name);

				input = getch();
				while ((input > 31 && input < 127) && new_chatroom_name.size() < MAX_CHATROOM_NAME_SIZE)
				{
					new_chatroom_name += input;
					Settings_ChangeChatroomName(new_chatroom_name);
					input = getch();
				}
			}
			else if (window_char == Cancel)
			{
				current_window = Window::Chatroom;
				break;
			}
			else if (window_char == SaveAndReturn) //CHANGE: changed logic so we don't send chatroom info to other computers if name hasn't changed
			{
				current_window = Window::Chatroom;
				//update username even if it didnt change because it isn't too slower than checking. don't publish manually since it will be included in heartbeat
				if (!new_user_nick.empty())
					chat_building.users[0].setName(new_user_nick); //CHANGE: access through model

				ChatRoom& current_chat_room = chat_building.chat_rooms[chat_building.users[0].getChatRoomIndex()];
				//update and publish chat room name if user actually changed chat room name
				if (current_chat_room.getName() != new_chatroom_name)
				{
					//Check if the Chatroom is not Public, if it is not then you can rename it
					if (current_chat_room.getChatRoomIndex() != 0)
					{
						current_chat_room.setName(new_chatroom_name);
						chat_building.chat_room_outbox.push_back(current_chat_room);
					}
				}
				break;
			}
			else
				input = getch();
		}
	}

	//- - - - - - - - - - - CHAT MESSAGE WINDOW - - - - - - - - - - -

	void ChatMessage_TopBar()
	{
		//Make the window
		WINDOW *window = MakeWindow(LINES, COLS, 0, 0, "");


		//Print the text inside top bar window
		mvwprintw(window, 1, 1, "Enter to Send Message \t\t F4 - Chatrooms Menu \t\t F6 - Settings \t\t F7 - Logout");

		//Refresh the Window
		wrefresh(window);
		delwin(window);
	}

	void ChatMessage_Users()
	{
		//Create the Window
		int userHeight = 21, userWidth = 30;
		string header = chat_building.calculateCurrentChatRoomName() + " Users"; //CHANGE: access through model
		WINDOW* window = MakeWindow(userHeight, userWidth, 19, 1, header);

		//Print the text inside the Users Window
		mvwprintw(window, userHeight - 2, userWidth / 2 - 7, "F6 - All Users");


		//Only show the current users in the chatroom
		vector<User> usersInSameChatroom = chat_building.getUsersInChatRoom(chat_building.users[0].getChatRoomIndex()); //CHANGE: moved functionality into model
		for (int i = 0; i < usersInSameChatroom.size(); i++)
		{
			//Print the User's Name and time in chatroom
			mvwprintw(window, 2 + i, 2, usersInSameChatroom[i].getNickName().c_str()); //CHANGE: .name to .getNickName()
			mvwprintw(window, 2 + i, 20, usersInSameChatroom[i].timeToString().c_str());
		}

		//Refresh the Window
		wrefresh(window);
		delwin(window);
	}

	void ChatMessage_Chatrooms(int SelectedIndex)
	{
		int chatHeight = 16, chatWidth = 30;
		string roomNames[10];
		int roomStats[10];

		//Create the Window
		WINDOW *window = MakeWindow(chatHeight, chatWidth, 3, 1, "Chatrooms");

		//Display the Chatroom Footer
		mvwprintw(window, chatHeight - 2, chatWidth / 2 - 14, "'Enter' to Switch Classrooms");

		//CHANGE: Moved functionality for getting info into model
		for (int i = 0; i < 10; i++)
		{
			roomNames[i] = chat_building.chat_rooms[i].getName();
			roomStats[i] = chat_building.calculateNumUsersInChatRoom(i);
		}

		for (int i = 0; i < 10; i++)
		{
			mvwprintw(window, 2 + i, 1, "%s", roomNames[i].c_str());

			//if there is more than one user in the chatroom
			if (roomStats[i] > 1)
				mvwprintw(window, 2 + i, 20, "%d users", roomStats[i]);
			//if there is only one user in the chatroom
			else if (roomStats[i] == 1)
				mvwprintw(window, 2 + i, 20, "%d user", roomStats[i]);
			//there are no users in the chatroom
			else
			{
				mvwchgat(window, 2 + i, 1, chatWidth - 2, A_NORMAL, 8, NULL);
				wattron(window, A_NORMAL | COLOR_PAIR(8));
				mvwprintw(window, 2 + i, 20, "0 users");
				wattroff(window, A_NORMAL | COLOR_PAIR(8));
			}

			//highlight the selected user
			if (SelectedIndex == i)
				mvwchgat(window, 2 + i, 1, chatWidth - 2, A_NORMAL, 9, NULL);
		}

		//Refresh the Window
		wrefresh(window);
		delwin(window);
	}

	void ChatMessage_ChatHistory()
	{
		int winWidth = COLS - 32;
		int winHeight = LINES - 13;

		//Initialize the Window
		WINDOW *window = MakeWindow(winHeight, winWidth, 3, 31, chat_building.calculateCurrentChatRoomName()); //CHANGE: 

		ChatRoom& current_chat_room = chat_building.chat_rooms[chat_building.users[0].getChatRoomIndex()]; //CHANGE:

																										   //Print the Chat History
		for (int i = 0; i < current_chat_room.message_history.size() && i < MAX_CHAT_HISTORY; i++)
		{
			mvwprintw(window, 2 * i + 2, 2, "%s:", current_chat_room.message_history[i].getAuthorNickName().c_str()); //CHANGE: access through model
			mvwprintw(window, 2 * i + 3, 5, "%s", current_chat_room.message_history[i].getContent().c_str()); //CHANGE: access through model
		}

		//Refresh the Window
		wrefresh(window);
		delwin(window);
	}

	void ChatMessage_SendMessage(string Message)
	{
		int winHeight = 9;
		int winWidth = COLS - 32;
		int charCount = 0;

		//Initialize the Window
		WINDOW *window = MakeWindow(winHeight, winWidth, LINES - winHeight - 1, 31, "Send a Message");

		//Print the "Send a Message" Footer
		mvwprintw(window, winHeight - 2, 1, "Press 'Enter' To Send Message");
		mvwprintw(window, winHeight - 2, winWidth - 26, "%d Characters Remaining", MESSAGE_LENGTH - Message.length());

		//Print the message
		mvwprintw(window, 2, 1, Message.c_str());

		//Refresh the Window
		wrefresh(window);
		delwin(window);
	}

	int ChatMessage_Draw(unsigned long chatroom_index)
	{
		//Paint the Background Window
		WINDOW *mainWin = newwin(LINES, COLS, 0, 0);

		//Assign the user to the passed chatroomIndex
		chat_building.users[0].setChatRoomIndex(chatroom_index); //CHANGE: access through model

		ChatMessage_TopBar();
		ChatMessage_Users();
		ChatMessage_Chatrooms(-1);
		ChatMessage_ChatHistory();
		ChatMessage_SendMessage("");

		//Navigation
		int window_char, sub_char;
		int ChangeChatroomFKey = KEY_F(4);
		int SendMessageFKey = KEY_F(5);
		int SettingsFKey = KEY_F(6);
		int LogoutFKey = KEY_F(7);

		sub_char = SendMessageFKey;
		while (window_char = sub_char)
		{
			//Change the Chatroom
			if (window_char == ChangeChatroomFKey)
			{
				int index = 0;

				//Draw initial
				ChatMessage_Chatrooms(index);

				//Get keyboard for up, down, or other function keys
				do
				{
					sub_char = getch();
					switch (sub_char)
					{
						//Up Key Pressed
					case KEY_UP:
						ChatMessage_Chatrooms(index >= 1 ? --index : 0);
						break;

						//Down key Pressed
					case KEY_DOWN:
						ChatMessage_Chatrooms(index == NUM_CHATROOMS - 1 ? NUM_CHATROOMS - 1 : ++index);
						break;

						//Enter Presed
					case 10:
						//Change user to this index of chatroom
						return index;

						//If the user types something unexpected, then take them to the 'Send a Message' window
					default:
						sub_char = SendMessageFKey;
						break;
					}

				} while (sub_char == KEY_UP || sub_char == KEY_DOWN);
			}

			//Go to the 'Send Message' Window
			else if (window_char == SendMessageFKey)
			{
				//Clear the screen again
				string spaces, user_Message;
				for (int i = 0; i < MESSAGE_LENGTH; i++) spaces += " ";

				//Clear the message and initialize the characters
				user_Message = "";
				do
				{
					ChatMessage_SendMessage(user_Message);
					sub_char = getch();

					//Check what input was
					if (sub_char == 10) //ENTER key
					{
						//Send the message //CHANGE: use message constructor and send through model
						Message newMessage = Message(chat_building.users[0], user_Message);
						chat_building.chat_rooms[chat_building.users[0].getChatRoomIndex()].addMessage(newMessage);
						user_Message = "";

						//Redraw the Chatmessage History
						ChatMessage_ChatHistory();
					}
					else if (sub_char == 127) //Backspace key
					{
						ChatMessage_SendMessage(user_Message);
					}

					//add the character if the message is not longer than MESSAGE_LENGTH and the character is not 'enter'
					if (user_Message.length() < MESSAGE_LENGTH && sub_char != 10)
						user_Message += sub_char;

				} while ((sub_char >= 32 && sub_char <= 127) || sub_char == 10);

				ChatMessage_SendMessage(spaces);
			}

			//Go to Settings Window
			else if (window_char == SettingsFKey)
			{
				current_window = Window::Settings;
				Settings_Draw();
				return chat_building.users[0].getChatRoomIndex();
			}

			//Go to the Logout Window
			else if (window_char == LogoutFKey)
			{
				current_window = Window::Login;
				chat_building.logged_in = false;
				return -1;
			}

			//Get a new key from the user
			else
				sub_char = getch();
		}
	}

	//- - - - - - - - - - - START WINDOW - - - - - - - - - - -

	void StartScreen_TopBorder()
	{
		//Make the window
		WINDOW* window = MakeWindow(3, COLS, 0, 0, "");

		//Print the text inside the window
		mvwprintw(window, 1, 1, "Enter Key - Login \t F6 - EXIT ");

		//Refresh the window
		wrefresh(window);
		delwin(window);
	}

	void StartScreen_Username(string userName)
	{
		//Make the window
		WINDOW* window = MakeWindow(LINES - 3, COLS, 3, 0, "Username");

		//Print the limits
		mvwprintw(window, 3, COLS / 2 - 8, "8 Character Limit");
		mvwchgat(window, 2, COLS / 2 - 10, 20, A_NORMAL, 4, NULL);

		wattron(window, COLOR_PAIR(4));
		mvwprintw(window, 2, COLS / 2 - 10, userName.c_str());
		wattroff(window, COLOR_PAIR(4));

		//Refresh the window
		wrefresh(window);
		delwin(window);
	}

	//DISCUSSION: IMPORTANT: make sure logic is right here. 1) in here, when enter is pushed, load user is called, if file doesnt exist, 
	// generate uuid 3) if file exists, use exisitng uuid 4) push new User onto users with this info, set local_user to point to this, set logged_in to true
	// need to keep bool loggedin in model so we don't publish user heartbeat with default info
	void StartScreen_Draw()
	{
		string user_nick = "";
		int input_char;
		unsigned long chat_room_index = 0; //change: tet:

		StartScreen_TopBorder();
		StartScreen_Username(user_nick.c_str());

		int ExitFKey = KEY_F(6);

		//Draw the Login Window
		input_char = getch();
		while ((input_char > 32 && input_char < 128 && input_char != ExitFKey) || input_char == 10)
		{
			StartScreen_TopBorder();
			StartScreen_Username(user_nick.c_str());

			if (input_char == 10) // enter key
			{
				chat_building.logged_in = true;
				current_window = Window::Chatroom;
				do
				{
					//Send the user to the public chatroom
					chat_room_index = ChatMessage_Draw(chat_room_index);
					if (chat_room_index<-1 && chat_room_index>9)
					{
						chat_room_index = 0; // public
					}
				} while (chat_room_index != -1);
				StartScreen_TopBorder();
				StartScreen_Username("");
			}
			else if (user_nick.size() < MAX_USER_NICK_SIZE)
			{
				user_nick += input_char;
			}

			input_char = getch();
		}
	}

	
	//- - - - - - - - - - - MAIN - - - - - - - - - - -
	void RefreshGUI()
	{
		if(current_window == Window::Settings)
		{
		Settings_AllUsers();
		}

		else if(current_window == Window::Chatroom)
		{
		ChatMessage_ChatHistory();

		ChatMessage_Users();
		}
	}

	void StartGUI()
	{
		//initialize ncurses
		initscr();
		start_color();
		cbreak();
		keypad(stdscr, TRUE);
		noecho();

		//Create the Color Pairs - Global Throughout Program
		init_pair(1, COLOR_BLACK, COLOR_WHITE);	 //Inverse
		init_pair(2, COLOR_GREEN, COLOR_BLACK); //Online
		init_pair(3, COLOR_RED, COLOR_BLACK);   //Offline
		init_pair(4, COLOR_WHITE, COLOR_BLUE);	//Textbox
		init_pair(5, COLOR_WHITE, COLOR_BLACK); //Normal
		init_pair(7, COLOR_WHITE, COLOR_YELLOW); //Element of Interest
		init_pair(8, COLOR_YELLOW, COLOR_BLACK);
		init_pair(9, COLOR_BLUE, COLOR_BLACK);
		init_pair(10, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(11, COLOR_CYAN, COLOR_BLACK);
		init_pair(12, COLOR_BLUE, COLOR_WHITE); //selected Index

												//Show the Login Screen
		StartScreen_Draw();

		endwin();
	}
};

//
#endif
