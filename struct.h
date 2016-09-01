#ifndef STRUCT_H_
#define STRUCT_H_

#include <Windows.h>
#include <string>

using std::string;

struct tabList{
	HWND wnd;
	tabList* next;
};

#endif