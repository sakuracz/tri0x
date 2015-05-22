#ifndef CLASSCONTROLLERMAIN_H_
#define CLASSCONTROLLERMAIN_H_

#include <Windows.h>
//#include "../ClassSynchro.h"

//#include "../WndCtrlSelect.h"
//#include "../WndCtrlLine.h"
//#include "../WndCtrlExp.h"
//#include "../WndCtrlImg.h"
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
//		SelectWndController selCtrl;
//		LineWndController lineCtrl;
//		ExpWndController expCtrl;
//		ImgWndController *_outCtrl;

		//windows:
		Dow _main;
//		Dow _selDev;

//		Synchronizer _synch;
	};
};

#endif
