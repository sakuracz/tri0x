#include "WndCtrlMonoSetup.h"
#include "libWin\WinMaker.h"

namespace Win{
	MonoWndCtrl::MonoWndCtrl()
	{
		itemIndex = 0;
		for (int i = 0; i < 3; i++){
			_staticArr[i] = new StaticControl(0);
		}
		
		for (int i = 0; i < 2; i++){
			_comboOpts[i] = new ComboControl(0);
		}
		
		_btnSelect = new ButtonControl(0);
		_btnForce = new ButtonControl(0);
	}

	bool MonoWndCtrl::GetInitParams(int *outArr)
	{
		outArr[0] = ::SendMessage(_comboOpts[0]->GetHandle(), CB_GETCURSEL, NULL, NULL);
		outArr[1] = ::SendMessage(_comboOpts[1]->GetHandle(), CB_GETCURSEL, NULL, NULL);
		outArr[2] = (::IsDlgButtonChecked(_btnForce->GetHandle(), 1201) ? 1 : 0);

		return true;
	};

	bool MonoWndCtrl::OnNotify(HWND hFrom, LPARAM lParam)
	{

		return true;
	}

	bool MonoWndCtrl::OnSize(int width, int height, int flag)
	{

		return true;
	}

	bool MonoWndCtrl::OnCommand(WPARAM wParam, LPARAM lParam)
	{
		if (LOWORD(wParam) == 1200){
			::SendMessage(::GetParent(_hwnd), WM_NOTIFY, 1200, NULL);
		}

		return true;
	}

	bool MonoWndCtrl::OnCreate(CreateData const* create)
	{
		RECT rect;
		::SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
		int maxX = rect.right;
		int maxY = rect.bottom;
		int width = 90, height = 200;	//window parameters

		::SetWindowPos(_hwnd, NULL, (maxX - width) / 2, (maxY - height) / 2, 175, 220, SWP_SHOWWINDOW);

		int j = 1000;
		for (int i = 0; i < 3; i++){
			j += i;						// static control ids:[1000,1002]
			StaticMaker stat(_hwnd, j);		
			stat.AddExStyle(WS_EX_TRANSPARENT);
			stat.AddStyle(WS_CLIPSIBLINGS);
			stat.Create("");
			stat.Show();

			_staticArr[i]->Init(stat, j);
		}
		
		j = 1100;
		for (int i = 0; i < 2; i++){
			j += i;						// combo control ids: [1100,1101]
			ComboMaker comb(_hwnd, j);
			comb.Create("");
			comb.Show();

			_comboOpts[i]->Init(comb, j);
		}

		j = 1200;						// button control id: {1200} - init button
		ButtonMaker butto(_hwnd, j);
		butto.Create("Init");
		butto.Show();

		_btnSelect->Init(butto, j);

		j++;							// button control id: {1201} - checkbox
		ButtonMaker check(_hwnd, j);
		check.AddStyle(BS_CHECKBOX | BS_AUTOCHECKBOX);
		check.Create("Force init");
		check.Show();

		_btnForce->Init(check, j);

		::SetWindowPos(_staticArr[0]->GetHandle(), NULL, 10, 20, 65, 20, SWP_SHOWWINDOW);
		::SetWindowPos(_staticArr[1]->GetHandle(), NULL, 10, 60, 65, 20, SWP_SHOWWINDOW);
		::SetWindowPos(_staticArr[2]->GetHandle(), NULL, 10, 100, 65, 20, SWP_SHOWWINDOW);
		::SetWindowPos(_comboOpts[0]->GetHandle(), NULL, 85, 20, 65, 20, SWP_SHOWWINDOW);
		::SetWindowPos(_comboOpts[1]->GetHandle(), NULL, 85, 60, 65, 20, SWP_SHOWWINDOW);
		::SetWindowPos(_btnSelect->GetHandle(), NULL, 85, 120, 65, 30, SWP_SHOWWINDOW);
		::SetWindowPos(_btnForce->GetHandle(), NULL, 10, 155, 90, 20, SWP_SHOWWINDOW);

		::SendMessage(_staticArr[0]->GetHandle(), WM_SETTEXT, NULL, (LPARAM)"Grating:");
		::SendMessage(_staticArr[1]->GetHandle(), WM_SETTEXT, NULL, (LPARAM)"Mirror:");
		::SendMessage(_staticArr[2]->GetHandle(), WM_SETTEXT, NULL, (LPARAM)"Status");

		::SendMessage(_comboOpts[0]->GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"300");
		::SendMessage(_comboOpts[0]->GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"75");
		::SendMessage(_comboOpts[0]->GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"600");
		::SendMessage(_comboOpts[1]->GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"Rear");
		::SendMessage(_comboOpts[1]->GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"Side");

		::SendMessage(_comboOpts[0]->GetHandle(), CB_SETCURSEL, 0, NULL);
		::SendMessage(_comboOpts[1]->GetHandle(), CB_SETCURSEL, 0, NULL);



		return true;
	}
};