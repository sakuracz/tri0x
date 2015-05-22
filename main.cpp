#include <windows.h>
#include "libWin/View.h"

int WINAPI WinMain
	(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdParam, int cmdShow)
{
	View view(hInst, cmdShow);

	MSG msg;
	int status;

	while((status = ::GetMessage(& msg, 0, 0, 0)) != 0)
	{
		if(status == -1)
			return -1;
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	return msg.wParam;
}