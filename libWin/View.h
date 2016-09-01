// View class definition

#ifndef VIEW_H_
#define VIEW_H_

#include <windows.h>
#include "Window.h"

class View
{
public:
	View(HINSTANCE hInst, int cmdShow);
	~View();
private:
	Win::Dow _main; //main window	
};

#endif
