#ifndef COMBOSUBCONTROLLER_H_
#define COMBOSUBCONTROLLER_H_

#include "libWin\ClassControllerSub.h"

namespace Win
{
	class ComboController : public SubController
	{
	public:
		friend class ListController;
		ComboController(CustomCombo&);
		void Invalidate();
	private:
		bool OnPaint() override;
		bool OnLMouseDblClick() override { return false; }
		bool OnLMouseButtonUp(WPARAM, LPARAM) override;
		bool OnLMouseButtonDown(WPARAM, LPARAM) override;
		bool OnCommand(WPARAM, LPARAM) override;
		bool OnNCCalcSize(WPARAM, LPARAM) override;
		CustomCombo& combo;
	};
}

#endif