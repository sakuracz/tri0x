#ifndef STRUCT_H_
#define STRUCT_H_

#include <Windows.h>
#include <string>

using std::string;

struct tabList{
	HWND wnd;
	tabList* next;
};

class CustomButton {
public:
	void Load(const string&, const string&);
	bool Draw(const int&, DRAWITEMSTRUCT*);
	~CustomButton();
private:
	HANDLE bmapPressed = 0;
	HANDLE bmapDepressed = 0;
};

#endif