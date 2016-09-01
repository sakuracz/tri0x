#ifndef MONOSETUPWINDOWCONTROLLER_H_
#define MONOSETUPWINDOWCONTROLLER_H_

#include "libWin\ClassChildController.h"
#include "SubCtrlButton.h"
#include "SubCtrlCombo.h"
#include "SubCtrlList.h"
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
		HRESULT OnCTLColorListBox(HDC, HWND) override;
		bool OnSize(int, int, int);
		bool OnNotify(HWND, LPARAM) override;
		bool OnKeyDown(WPARAM, LPARAM) override { return false; }
		bool OnDrawItem(LPARAM) override;
		bool OnNCPaint(WPARAM, LPARAM) override { return false; }
		bool OnMeasureItem(WPARAM, LPARAM) override;
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
		CustomCombo gratingCombo;
		ComboController combo_controller;
		ListController* lc = nullptr;// list_controller;
		HANDLE background_bmp;
		int forceState = 1, initState = 0;
		int progress = 0; //percentage of init completion
		bool subclassed = false;
		ListController l;
	};
}

#endif