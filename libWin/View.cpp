#include "View.h"
#include "WinMaker.h"
#include "WinClassMaker.h"

View::View(HINSTANCE hInst, int cmdShow)
	: _main(0)
{
	char classMainName[] = "THz Exp";

	Win::ClassMaker mainClass(Win::Procedure, classMainName, hInst);
	mainClass.Register();

	Win::Maker mainWndMaker(classMainName, hInst);
	mainWndMaker.Create("THz Reflection Geometry Setup");
	_main.Init(mainWndMaker);
	mainWndMaker.Show(cmdShow);
};

View::~View()
{
};
