#ifndef STRUCT_H_
#define STRUCT_H_

#include <Windows.h>

struct tabList{
	HWND wnd;
	tabList* next;
};

#endif