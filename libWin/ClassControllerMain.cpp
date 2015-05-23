#include "ClassControllerMain.h"
#include "WinClassMaker.h"
#include "WinMaker.h"
#include "ChildProcedure.h"
#include <sstream>

namespace Win
{
	MainController::MainController(HWND hwnd, CreateData *create)
		: _main(hwnd), _monoDow(0)
	{
		//window class names:
		char classMonoName[] = "Monochromator";
	
		//window class maker:
		Win::ChildClassMaker monoClass(childProc, classMonoName, _main.GetInstance());
	
		//registering classes:
		monoClass.Register();
	
		//window makers:
		ChildMaker monoWinMaker(classMonoName, _main, 1, monoCtrl);
	
		//creating the windows:
		monoWinMaker.Create("Select device");
	
		//initiating windows:
		_monoDow.Init(monoWinMaker);

		//show created windows:
//		selWinMaker.Show();

//		::SetFocus(_expWnd);

//		::SetWindowPos(_selDev, HWND_TOP, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	};

	MainController::~MainController()
	{

	};

	bool MainController::OnCreate(CreateData const* create)
	{
		RECT rect;
		::SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
		int maxX = rect.right;
		int maxY = rect.bottom;
		
		::SetWindowPos(_main, HWND_TOP, 0, 0, maxX/2, maxY/2, SWP_SHOWWINDOW); 
		 
		return true;
	};

	bool MainController::OnNotify(WPARAM wParam, LPARAM lParam)
	{
		switch(wParam)
		{
			break;
		}

		return true;
	};
};