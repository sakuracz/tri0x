#include "WndCtrlMonoSetup.h"
#include "libWin\WinMaker.h"
#include <string>
#include <sstream>
#include <vector>

using std::string;
using std::stringstream;
using std::vector;

namespace Win{
	MonoWndCtrl::MonoWndCtrl() : combo_controller(gratingCombo)
	{
		itemIndex = 0;		
		for (int i = 0; i < 2; i++){
			_comboOpts[i] = new ComboControl(0);
		}
		
		_btnForce.LoadBMPs(string("switch"));
		_btnInit.LoadBMPs(string("init"));

		vector<string> items = vector<string>();
		items.push_back("300");
		items.push_back("75");
		items.push_back("600");

		RECT rc1;
		rc1.top = 11;
		rc1.left = 10;
		rc1.bottom = 41;
		rc1.right = 146;
		gratingCombo.Load(string("grating"),items, rc1);

		string bg_name = string("WndCtrlMonoBg.bmp");
		background_bmp = ::LoadImage(NULL, bg_name.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (background_bmp == NULL){
			DWORD dw = GetLastError();
			stringstream stream;
			stream << "Got error #: " << dw;
			::MessageBox(NULL, stream.str().c_str(), "Failed to load background image.", MB_OK | MB_ICONERROR);
		}
	}

	MonoWndCtrl::~MonoWndCtrl()
	{
		_btnForce.UnSubClass();
		gratingCombo.UnSubClass();
		
		lc = new ListController();

		for (unsigned int i = 0; i < combo_count; i++){
			delete _comboOpts[i];
		}				
	}

	bool MonoWndCtrl::GetInitParams(int *outArr)
	{
		outArr[0] = ::SendMessage(gratingCombo.GetHandle(), CB_GETCURSEL, NULL, NULL);
		outArr[1] = ::SendMessage(_comboOpts[1]->GetHandle(), CB_GETCURSEL, NULL, NULL);
		outArr[2] = forceState;
		
		return true;
	};

	HRESULT MonoWndCtrl::OnCTLColorListBox(HDC hdc, HWND hwnd)
	{
//		::SetWindowPos(gratingCombo.GetHandle(), NULL, 10, 41, 0, 0, SWP_NOSIZE);
		return false;
	}

	bool MonoWndCtrl::OnNotify(HWND hFrom, LPARAM lParam)
	{
		return false;
	}

	bool MonoWndCtrl::OnSize(int width, int height, int flag)
	{

		return false;
	}

	bool MonoWndCtrl::OnCommand(WPARAM wParam, LPARAM lParam)
	{
		if (LOWORD(wParam) == 1200){	// run button pressed - notify parent window
			initState = initState ^ 1;
			::SendMessage(::GetParent(_hwnd), WM_NOTIFY, 1200, NULL);
		}
		if (LOWORD(wParam) == 1201){	//switch the state of the "Force init" button
			forceState = forceState ^ 1;
		}

		if (LOWORD(wParam) == 1100){	//combo box 0 (grating)
			switch (HIWORD(wParam)){
			case CBN_SELCHANGE:
			{
				gratingCombo.ToggleSelected();		//grating selection used to be false - now it's true window needs to be resized				
				unsigned int sel = ::SendMessage(gratingCombo.GetHandle(), CB_GETCURSEL, 0, 0);
				gratingCombo.Select(sel);
				combo_controller.Invalidate();
			}
//				combo_controller.Invalidate();
				break;
			case CBN_SELENDOK:
//				combo_controller.Invalidate();
				gratingCombo.ToggleSelecting();
				break;
			case CBN_SETFOCUS:
//				combo_controller.Invalidate();
//				::MessageBox(NULL, "SETFOCUS", "Break", MB_OK);
				break;
			case CBN_CLOSEUP:				
//				combo_controller.Invalidate();
				break;
			case CBN_DROPDOWN:
			{				
				gratingCombo.ToggleSelecting();
				COMBOBOXINFO comboInfo;
				comboInfo.cbSize = sizeof(COMBOBOXINFO);
				::GetComboBoxInfo(gratingCombo.GetHandle(), &comboInfo);
				
				if (!subclassed){					
					LONG listProc = ::GetWindowLong(comboInfo.hwndList, GWL_WNDPROC);
					LONG comboProc = ::GetWindowLong(comboInfo.hwndCombo, GWL_WNDPROC);
/*					stringstream sss;
					sss << "Combo: " << comboProc << " List: " << listProc << " List(hex): " << std::hex << listProc << std::endl;										
					sss << "Reiterpreted: " << reinterpret_cast<ProcPtr>(listProc) << std::endl;
					sss << "Reiterpreted: " << reinterpret_cast<ProcPtr>(listProc) << std::endl;
					::MessageBox(NULL, sss.str().c_str(), "H", MB_OK);	*/					

					ListController* pL = new ListController();
					pL->Init(comboInfo.hwndList, reinterpret_cast<ProcPtr>(listProc), &combo_controller, gratingCombo);
					::SetWindowLong(comboInfo.hwndList, GWL_USERDATA, reinterpret_cast<LONG>(pL));
					::SetWindowLong(comboInfo.hwndList, GWL_WNDPROC, reinterpret_cast<LONG>(SpecialListProc));

/*					stringstream sss;
					sss << "&l: " << pL << " &l(hex): " << std::hex << pL << std::endl;
					sss << "Reiterpreted: " << reinterpret_cast<LONG>(pL) << std::endl;					
					::MessageBox(NULL, sss.str().c_str(), "H", MB_OK);
					*/
					subclassed = true;
				};

//				stringstream sss;
//				sss << "Top: " << comboInfo.rcItem.top << " Bottom: " << comboInfo.rcItem.bottom << " Left: " << comboInfo.rcItem.left << " Right: " << comboInfo.rcItem.right << std::endl;
//				sss << "Top: " << comboInfo.rcButton.top << " Bottom: " << comboInfo.rcButton.bottom << " Left: " << comboInfo.rcButton.left << " Right: " << comboInfo.rcButton.right << std::endl;
//				sss << "ListHwnd: " << std::hex << comboInfo.hwndList << " ComboHwnd: " << comboInfo.hwndCombo << " ItemHwnd: " << comboInfo.hwndItem << std::endl;
//				::MessageBox(NULL, sss.str().c_str(), "H", MB_OK);

				RECT rc;
				::GetWindowRect(comboInfo.hwndList, &rc);

				stringstream sss;
				sss << "Top: " << rc.top << " Bottom: " << rc.bottom << " Left: " << rc.left << " Right: " << rc.right << std::endl;
//				sss << "Top: " << comboInfo.rcButton.top << " Bottom: " << comboInfo.rcButton.bottom << " Left: " << comboInfo.rcButton.left << " Right: " << comboInfo.rcButton.right << std::endl;
				sss << "ListHwnd: " << std::hex << comboInfo.hwndList << " ComboHwnd: " << comboInfo.hwndCombo << " ItemHwnd: " << comboInfo.hwndItem << std::endl;
//				::MessageBox(NULL, sss.str().c_str(), "H", MB_OK);

//				::SetActiveWindow(comboInfo.hwndList);
//				::SetForegroundWindow(comboInfo.hwndList);
//				::MoveWindow(comboInfo.hwndList, rc.left, rc.top-4, 136, 90, TRUE);
//				::SetWindowPos(comboInfo.hwndList, HWND_TOPMOST, rc.left, rc.top-5, 136, 90, SWP_NOACTIVATE);
				break;
			}
			case CBN_KILLFOCUS:		
				gratingCombo.ToggleSelecting();
				break;
			case CBN_SELENDCANCEL:				
				gratingCombo.ToggleSelecting();
				break;
			}
		}
		return true;
	}

	bool MonoWndCtrl::OnCreate(CreateData const* create)
	{
		RECT rect, client_rect;
		::SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
		int maxX = rect.right;
		int maxY = rect.bottom;
		int width = 175, height = 290;	//window parameters
		client_rect.top = (maxY - height) / 2;
		client_rect.bottom = client_rect.top + height;
		client_rect.left = (maxX - width) / 2;
		client_rect.right = client_rect.left + width;
		::AdjustWindowRect(&client_rect, ::GetWindowLong(_hwnd, GWL_STYLE), FALSE);
		height = client_rect.bottom - client_rect.top;
		width = client_rect.right - client_rect.left;

		::SetWindowPos(_hwnd, NULL, (maxX - width) / 2, (maxY - height) / 2, width, height, SWP_SHOWWINDOW);
		
		int j = 1100;
		ComboMaker comb(_hwnd, j);
		comb.SetStyle(CBS_OWNERDRAWFIXED | CBS_DROPDOWNLIST );
		comb.Create("");
		comb.Show();
		gratingCombo.Init(comb, j);
		gratingCombo.Fill();
		gratingCombo.SubClass(&combo_controller);
		

		for (unsigned int i = 1; i < 2; i++){
			j = 1100 + i;						// combo control ids: [1100,1101]
			ComboMaker comb(_hwnd, j);
			comb.Create("");
			comb.Show();
			_comboOpts[i]->Init(comb, j);
		}
	
		j = 1200;						// button control id: {1200} - init button
		ButtonMaker butto(_hwnd, j);
		butto.SetStyle(BS_OWNERDRAW);
		butto.Create("Init");
		butto.Show();

		_btnInit.Init(butto, j);

		j++;							// button control id: {1201} - checkbox
		ButtonMaker check(_hwnd, j);		
		check.SetStyle(BS_OWNERDRAW);
		check.Create("Force init");
		check.Show();

		_btnForce.Init(check, j);
		_btnForce.SubClass(&button_controller);		

		::SetWindowPos(gratingCombo.GetHandle(), NULL, (gratingCombo.GetBasePos()).first, (gratingCombo.GetBasePos()).second, 136, 30, SWP_SHOWWINDOW );
		::SetWindowPos(_comboOpts[1]->GetHandle(), NULL, 10, 83, 136, 63, SWP_SHOWWINDOW);
		::SetWindowPos(_btnInit.GetHandle(), NULL, 67, 247, 103, 32, SWP_SHOWWINDOW);
		::SetWindowPos(_btnForce.GetHandle(), NULL, 67, 186, 79, 31, SWP_SHOWWINDOW);

		::SendMessage(gratingCombo.GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"300");
		::SendMessage(gratingCombo.GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"75");
		::SendMessage(gratingCombo.GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"600");
		::SendMessage(_comboOpts[1]->GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"Rear");
		::SendMessage(_comboOpts[1]->GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"Side");

		::SendMessage(gratingCombo.GetHandle(), CB_SETCURSEL, -1, NULL);
		::SendMessage(_comboOpts[1]->GetHandle(), CB_SETCURSEL, 0, NULL);

		return true;
	}

	bool MonoWndCtrl::OnDrawItem(LPARAM lParam)
	{		
		DRAWITEMSTRUCT* pDIS = reinterpret_cast<DRAWITEMSTRUCT*>(lParam);

		//DONE: Fix double click button problem - subclassing helped.
		bool res;
		switch (pDIS->CtlID) {
		case 1100:		//grating combo
		{
			res = true;
			gratingCombo.Draw(pDIS->itemID, pDIS);
			break;
		}
		case 1201:		//force init check button
			if (forceState == 0)
				res = _btnForce.Draw(1, pDIS);
			else
				res = _btnForce.Draw(0, pDIS);
			break;
		case 1200:		//init(start exp) button
			if (initState == 0)
				res = _btnInit.Draw(1, pDIS);
			else
				res = _btnInit.Draw(0, pDIS);
			break;
		}
		return res;
	}

	bool MonoWndCtrl::OnEraseBG(HDC hDC)
	{
		HDC compHDC = ::CreateCompatibleDC(hDC);
		BITMAP bm;
		HBITMAP bg = (HBITMAP)background_bmp;
		::GetObject(background_bmp, sizeof(BITMAP), &bm);
		::SelectObject(compHDC, bg);
		::BitBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight, compHDC, 0, 0, SRCCOPY);
		DeleteDC(compHDC);
		return true;
	}

	bool MonoWndCtrl::OnMeasureItem(WPARAM wParam, LPARAM lParam)
	{
		LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT)lParam;
		UINT from = (UINT)wParam;
		switch (from){
		case 1100:	//grating combo
			lpmis->itemHeight = 30;
			break;
		case 1101:	//mirror combo
			lpmis->itemHeight = 30;
			break;
		}

		return true;
	}
};