#ifndef CONTROLLER_H
#define CONTROLLER_H 2016

#include "model.h"
#include "view.h"
#include "osdds_io.h"

class Controller
{
public:
	Controller();
	void login();
	void run();
	//chatroom_data chatRoom ( (char*) "chatroom" );
	//user_data User ( (char*) "user" );
	//message_data Message ( (char*) "msg" );

private:
	Model chat_building;
	//View ncurses;

	void ncursesLoop();
	void openSpliceLoop();



};

#endif