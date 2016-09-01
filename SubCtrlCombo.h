#ifndef COMBOSUBCONTROLLER_H_
#define COMBOSUBCONTROLLER_H_

#include <memory>
#include "libWin\ClassControllerSub.h"

using std::unique_ptr;

namespace Win
{
	class ComboController : public SubController
	{
	public:
		friend class SubListController;
		ComboController(CustomCombo&);
		~ComboController();
		void Invalidate();
		void SubList();
	private:		
		bool OnPaint() override;		
		CustomCombo& combo;
		const unique_ptr<SubListController> sublist_controller;
		COMBOBOXINFO comboInfo;
	};

	class SubListController : public SubController
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
}

#endif