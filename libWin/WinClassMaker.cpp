#include "WinClassMaker.h"
#include <windows.h>

namespace Win
{
	ClassMaker::ClassMaker
		(WNDPROC WinProcedure, const char *className, HINSTANCE hInst)
	{
		lpfnWndProc = WinProcedure;
		hInstance = hInst;
		lpszClassName = className;
		cbSize = sizeof(WNDCLASSEX);
		hCursor = ::LoadCursor(0, IDC_ARROW);
		hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);
		style = 0;
		cbClsExtra = 0;
		cbWndExtra = 0;
		hIcon = 0;
		hIconSm = 0;
		lpszMenuName = 0;
	};

	void ClassMaker::Register()
	{
		if(::RegisterClassEx(this) == 0)
			throw "RegisterClass failed";
	};

	void ClassMaker::SetIcons(int id)
	{
		_stdIcon.Load(hInstance, id);
		_smallIcon.Load(hInstance, id);
		hIcon = _stdIcon;
		hIconSm = _smallIcon;
	};

	ChildClassMaker::ChildClassMaker(WNDPROC WinProcedure, const char *className, HINSTANCE hInst)
		: ClassMaker(WinProcedure, className, hInst)
	{
		hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW+1);
		hCursor = ::LoadCursor(0, IDC_CROSS);
		
	}
}