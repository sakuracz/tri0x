#include "ClassControllerMain.h"
#include "WinClassMaker.h"
#include "WinMaker.h"
#include "ChildProcedure.h"
#include <sstream>

namespace Win
{
	MainController::MainController(HWND hwnd, CreateData *create)
		: _main(hwnd), _monoDow(0), _expDow(0), _synch(expCtrl)
	{
		//window class names:
		char classMonoName[] = "Monochromator";
		char classExpName[] = "Experiment";
	
		//window class maker:
		Win::ChildClassMaker monoClass(childProc, classMonoName, _main.GetInstance());
		Win::ChildClassMaker expClass(childProc, classExpName, _main.GetInstance());
	
		//registering classes:
		monoClass.Register();
		expClass.Register();
	
		//window makers:
		ChildMaker monoWinMaker(classMonoName, _main, 1, monoCtrl);
		ChildMaker expWinMaker(classExpName, _main, 2, expCtrl);

		monoWinMaker.AddExStyle(WS_EX_COMPOSITED);
		expWinMaker.AddExStyle(WS_EX_COMPOSITED);

		//creating the windows:
		monoWinMaker.Create("Select device");
		expWinMaker.Create("Set up experiment");
	
		//initiating windows:
		_monoDow.Init(monoWinMaker);
		_expDow.Init(expWinMaker);

		//show created windows:
		expWinMaker.Show();
		monoWinMaker.Show();
//		::SetFocus(_expWnd);

		::SetWindowPos(_expDow, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_HIDEWINDOW);
		::SetWindowPos(_monoDow, HWND_TOP, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
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
		
		::SetWindowPos(_main, HWND_TOP, 0, 0, maxX, maxY, SWP_SHOWWINDOW); 
		 
		return true;
	};

	bool MainController::OnNotify(WPARAM wParam, LPARAM lParam)
	{
		switch (wParam)
		{
		case 1200:
			int params[3];
			monoCtrl.GetInitParams(params);
			_synch.InitDev(params);
			::SetWindowPos(_monoDow, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_HIDEWINDOW);
			::SetWindowPos(_expDow, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
			break;
		}

		return true;
	};
};