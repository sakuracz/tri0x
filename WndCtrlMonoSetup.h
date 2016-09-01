#ifndef MONOSETUPWINDOWCONTROLLER_H_
#define MONOSETUPWINDOWCONTROLLER_H_

#include "libWin\ClassChildController.h"
#include "SubCtrlButton.h"
#include "libWin\WindowControls.h"
#include "struct.h"

namespace Win{

	class MonoWndCtrl : public ChildController
	{
	public:
		MonoWndCtrl();
		~MonoWndCtrl();
		bool OnCreate(CreateData const *);
		bool OnCommand(WPARAM, LPARAM);
		bool OnSize(int, int, int);
		bool OnNotify(HWND, LPARAM) override;
		bool OnKeyDown(WPARAM, LPARAM) override { return false; }
		bool OnDrawItem(LPARAM) override;
		bool OnEraseBG(HDC) override;
		bool GetInitParams(int*);
		void ZeroInit(){ initState = 0; }

	private:
		unsigned int itemIndex;
		const unsigned int combo_count = 2;
		ComboControl *_comboOpts[2];
		CustomButton _btnForce;
		CustomButton _btnInit;
		ButtonController button_controller;
		CustomButton forceBtn, initButton;
		HANDLE background_bmp;
		int forceState = 1, initState = 0;
	};
}

#endif