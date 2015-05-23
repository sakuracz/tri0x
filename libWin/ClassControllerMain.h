#ifndef CLASSCONTROLLERMAIN_H_
#define CLASSCONTROLLERMAIN_H_

#include <Windows.h>
#include "Procedure.h"
#include "ChildProcedure.h"
#include "../WndCtrlMonoSetup.h"
#include "ClassController.h"
#include "Window.h"

namespace Win
{
	class MainController : public Controller
	{
	public:
		MainController(HWND, CreateData*);
		~MainController();
		bool OnCreate(CreateData const*);
		bool OnNotify(WPARAM, LPARAM);
	private:
		//controllers:
		MonoWndCtrl monoCtrl;
//		LineWndController lineCtrl;
//		ExpWndController expCtrl;
//		ImgWndController *_outCtrl;

		//windows:
		Dow _main;
		Dow _monoDow;

//		Synchronizer _synch;
	};
};

#endif
