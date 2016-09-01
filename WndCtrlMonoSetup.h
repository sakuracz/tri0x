#ifndef MONOSETUPWINDOWCONTROLLER_H_
#define MONOSETUPWINDOWCONTROLLER_H_

#include "libWin\ClassChildController.h"
#include "libWin\WindowControls.h"
#include "struct.h"

namespace Win{

	class MonoWndCtrl : public ChildController
	{
	public:
		MonoWndCtrl();
		bool OnCreate(CreateData const *);
		bool OnCommand(WPARAM, LPARAM);
		bool OnSize(int, int, int);
		bool OnNotify(HWND, LPARAM) override;
		bool OnKeyDown(WPARAM, LPARAM) override { return false; }
		bool OnDrawItem(LPARAM) override;
		bool GetInitParams(int*);

	private:
		unsigned int itemIndex;
		StaticControl *_staticArr[3];
		ComboControl *_comboOpts[2];
		ButtonControl *_btnSelect, *_btnForce;
		CustomButton forceBtn;
		int forceState = 0;
	};
}

#endif