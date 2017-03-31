#ifndef CONTROLLER_H
#define CONTROLLER_H 2016

#include "model.h"
#include "view.h"

class Controller
{
public:
	Controller();
	void login();
	void run();

private:
	
	void ncursesLoop();
	void openSpliceLoop();
};

#endif