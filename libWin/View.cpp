#include "View.h"
#include "WinMaker.h"
#include "WinClassMaker.h"

View::View(HINSTANCE hInst, int cmdShow)
	: _main(0)
{
	char classMainName[] = "Photoreflection";

	Win::ClassMaker mainClass(Win::Procedure, classMainName, hInst);
	mainClass.Register();

	Win::Maker mainWndMaker(classMainName, hInst);
	mainWndMaker.Create("Photoreflection measurement setup");
	_main.Init(mainWndMaker);
	mainWndMaker.Show(cmdShow);
};

View::~View()
{
};
