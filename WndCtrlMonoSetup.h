#ifndef MONOSETUPWINDOWCONTROLLER_H_
#define MONOSETUPWINDOWCONTROLLER_H_

#include "libWin\ClassChildController.h"
#include "libWin\WindowControls.h"

namespace Win{

	class MonoWndCtrl : public ChildController
	{
	public:
		MonoWndCtrl();
		bool OnCreate(CreateData const *);
		bool OnCommand(WPARAM, LPARAM);
		bool OnSize(int, int, int);
		bool OnNotify(HWND, LPARAM);

	private:
		unsigned int itemIndex;
		ComboControl *_comboOpts;
		ButtonControl *_btnSelect;
	};
}

#endif