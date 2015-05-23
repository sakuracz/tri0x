#ifndef CHILDPROCEDURE_H_
#define CHILDPROCEDURE_H_

#include <Windows.h>

namespace Win
{
		LRESULT CALLBACK childProc
			(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
}

#endif