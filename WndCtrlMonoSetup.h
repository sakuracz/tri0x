#ifndef MONOSETUPWINDOWCONTROLLER_H_
#define MONOSETUPWINDOWCONTROLLER_H_

#include "libWin/ClassChildController.h"
#include "SubCtrlButton.h"
#include "SubCtrlCombo.h"
#include "libWin/WindowControls.h"
#include "CustomControls.h"
#include "struct.h"

namespace Win{

	class MonoWndCtrl : public ChildController
	{
	public:
		friend class Synchronizer;
		MonoWndCtrl();
		~MonoWndCtrl();
		bool OnCreate(CreateData const *);
		bool OnCommand(WPARAM, LPARAM);
		HRESULT OnCTLColorListBox(HDC, HWND) override;
		bool OnSize(int, int, int);		
		bool OnKeyDown(WPARAM, LPARAM) override { return false; }
		bool OnDrawItem(LPARAM) override;
		bool OnNCPaint(WPARAM, LPARAM) override { return false; }
		bool OnMeasureItem(WPARAM, LPARAM) override;
		bool OnEraseBG(HDC) override;
		bool GetInitParams();
		void ZeroInit(){ initState = 0; }

	private:
		void UpdateProgress(int);		
		CustomButton _btnForce, _btnInit;
		ButtonController button_controller;
		CustomCombo gratingCombo, mirrorCombo;
		ComboController grating_controller, mirror_controller;		
		HANDLE background_bmp;
		vector<HANDLE> progress_bmps;
		vector<int> init_params;
		int forceState = 1, initState = 0;
		int progress = 0; //percentage of init completion		
	};
}

#endif
