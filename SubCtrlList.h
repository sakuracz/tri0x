#ifndef LISTCONTROLLER_H_
#define LISTCONTROLLER_H_

#include "libWin\ClassControllerSub.h"
#include "SubCtrlCombo.h"

namespace Win
{
	class ListController : public SubController
	{
	public:
		void Init(HWND, ProcPtr, Controller*, HWND, RECT&);
	private:				
		bool OnNCCalcSize(WPARAM, LPARAM) override;
		bool OnWindowPosChanging(WPARAM, LPARAM) override;
		HWND parentHWND;
		RECT rect;
		ComboController* parent_controller;
	};
};

#endif