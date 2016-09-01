#ifndef CLASSCONTROLLERMAIN_H_
#define CLASSCONTROLLERMAIN_H_

#include <Windows.h>
#include "../WndCtrlExp.h"
#include "../WndCtrlImg.h"
#include "../WndCtrlMonoSetup.h"
#include "../ClassSynchro.h"
#include "ClassController.h"
#include "Window.h"

namespace Win
{
	class MainController : public Controller
	{
	public:
		MainController(HWND, CreateData*);
		~MainController();
		bool OnCreate(CreateData const*) override;
		bool OnHotKey(WPARAM, LPARAM) override { return false; }
		bool OnNotify(HWND, LPARAM) override { return false; }
		bool OnNotify(WPARAM, LPARAM);
	private:
		//controllers:
		MonoWndCtrl monoCtrl;
		ExpWndController expCtrl;
//		ImgWndController *_outCtrl;

		//windows:
		Dow _main;
		Dow _monoDow;
		Dow _expDow;
//		Dow *_outWnd;

		Synchronizer _synch;
	};
};

#endif
