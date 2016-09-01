#ifndef LISTCONTROLLER_H_
#define LISTCONTROLLER_H_

#include "libWin\ClassControllerSub.h"
#include "SubCtrlCombo.h"

namespace Win
{
	class ListController : public SubController
	{
	public:
		void Init(HWND, ProcPtr, Controller*, HWND parent);
	private:
		bool OnEraseBG(HDC) override;
		bool OnMove(WPARAM, LPARAM) override;
		bool OnNCCalcSize(WPARAM, LPARAM) override;
//		bool OnNCPaint(WPARAM, LPARAM) override;
//		bool OnPaint() override;
		bool OnWindowPosChanging(WPARAM, LPARAM) override;
		HWND parentHWND;
		ComboController* parent_controller;

	};
};

#endif