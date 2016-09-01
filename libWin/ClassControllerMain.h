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
		HRESULT OnCTLColorListBox(HDC, HWND) override { return false; };
		bool OnHotKey(WPARAM, LPARAM) override { return false; }
		bool OnMove(WPARAM, LPARAM) override { return false; }
		bool OnNotify(HWND, LPARAM) override { return false; }
		bool OnNotify(WPARAM, LPARAM);
		bool OnEraseBG(HDC) override { return false; }
		bool OnLMouseButtonUp(WPARAM, LPARAM) override { return false; }
		bool OnLMouseButtonDown(WPARAM, LPARAM) override { return false; };
		bool OnLMouseDblClick() override { return false; };
		bool OnNCCalcSize(WPARAM, LPARAM) override { return false; };
		bool OnNCPaint(WPARAM, LPARAM) override { return false; }
		bool OnWindowPosChanging(WPARAM, LPARAM) override { return false;  }
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
