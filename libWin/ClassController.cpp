#include "ClassController.h"
#include "WinMaker.h"

namespace Win
{
	Controller::Controller() : _hwnd(0)
	{};

	Controller::Controller(HWND hwnd, CreateData * create) : _hwnd(hwnd)
	{};

	Controller::~Controller()
	{
		PostQuitMessage(0);
	};

	bool Controller::OnCreate(CreateData const *)
	{
		 return false;
	};
};
