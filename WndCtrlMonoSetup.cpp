#include "WndCtrlMonoSetup.h"
#include "libWin/WinMaker.h"
#include <string>
#include <sstream>
#include <vector>

using std::string;
using std::stringstream;
using std::vector;

namespace Win{
	MonoWndCtrl::MonoWndCtrl() : grating_controller(gratingCombo), mirror_controller(mirrorCombo)
	{				
		_btnForce.LoadBMPs(string("switch"));
		_btnInit.LoadBMPs(string("init"));

		vector<string> gratingItems = vector<string>();
		gratingItems.push_back("300");
		gratingItems.push_back("75");
		gratingItems.push_back("600");

		vector<string> mirrorItems = vector<string>();
		mirrorItems.push_back("Rear");
		mirrorItems.push_back("Side");
		
		RECT rc1, rc2;
		rc1.top = 11;
		rc1.left = 10;
//		rc1.bottom = 0;		//useless since the size is determined by the size of the loaded bitmap
//		rc1.right = 0;
		gratingCombo.Load(string("grating"), gratingItems, rc1);

		rc2.top = 84;
		rc2.left = 10;
//		rc2.bottom = 0;		//same as above
//		rc2.right = 0;
		mirrorCombo.Load(string("mirror"), mirrorItems, rc2);

		string bg_name = string("res/WndCtrlMonoBg.bmp");
		background_bmp = ::LoadImage(NULL, bg_name.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (background_bmp == NULL){
			DWORD dw = GetLastError();
			stringstream stream;
			stream << "Got error #: " << dw;
			::MessageBox(NULL, stream.str().c_str(), "Failed to load background image.", MB_OK | MB_ICONERROR);
		}		
		
		stringstream s;
		for (int i = 0; i < 101; i++){
			s = stringstream();
			s << "res/prog-" << i << ".bmp";
			progress_bmps.push_back(::LoadImage(NULL, s.str().c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
			if (progress_bmps[i] == NULL){
				DWORD dw = GetLastError();
				stringstream stream;
				stream << "Got error #: " << dw;
				::MessageBox(NULL, stream.str().c_str(), "Failed to load progress image.", MB_OK | MB_ICONERROR);
			}
		}
	}

	MonoWndCtrl::~MonoWndCtrl()
	{
		_btnForce.UnSubClass();
		_btnInit.UnSubClass();
		gratingCombo.UnSubClass();			
		mirrorCombo.UnSubClass();		
	}

	bool MonoWndCtrl::GetInitParams()
	{
		init_params = vector<int>();
		init_params.push_back(::SendMessage(gratingCombo.GetHandle(), CB_GETCURSEL, NULL, NULL));
		init_params.push_back(::SendMessage(mirrorCombo.GetHandle(), CB_GETCURSEL, NULL, NULL));
		init_params.push_back(forceState);		
		
		return true;
	};

	HRESULT MonoWndCtrl::OnCTLColorListBox(HDC hdc, HWND hwnd)
	{
//		::SetWindowPos(gratingCombo.GetHandle(), NULL, 10, 41, 0, 0, SWP_NOSIZE);
		return false;
	}

	bool MonoWndCtrl::OnSize(int width, int height, int flag)
	{

		return false;
	}

	bool MonoWndCtrl::OnCommand(WPARAM wParam, LPARAM lParam)
	{
		if (LOWORD(wParam) == 1200){	// run button pressed - notify parent window
			progress = 0;
			initState = initState ^ 1;
			::SendMessage(::GetParent(_hwnd), WM_NOTIFY, 1200, NULL);
//			::InvalidateRect(_hwnd, NULL, TRUE);
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
				grating_controller.Invalidate();					
			}
				break;
			case CBN_SELENDOK:
				gratingCombo.ToggleSelected();
				//check if other combo is selected -> then enable the init button
				if (mirrorCombo.IsSelected()){
					if (!::IsWindowEnabled(_btnInit.GetHandle())){
						::EnableWindow(_btnInit.GetHandle(), TRUE);
						::InvalidateRect(_btnInit.GetHandle(), NULL, TRUE);
					}
				}
				break;
			case CBN_DROPDOWN:				
				gratingCombo.ToggleSelecting();
				break;			
			case CBN_KILLFOCUS:		
				gratingCombo.ToggleSelecting();
				break;
			case CBN_SELENDCANCEL:				
				gratingCombo.ToggleSelecting();
				break;
			}
		}
		if (LOWORD(wParam) == 1101){	//combo box 0 (grating)
			switch (HIWORD(wParam)){
			case CBN_SELCHANGE:
			{
				mirrorCombo.ToggleSelected();		//mirror selection used to be false - now it's true window needs to be resized				
				unsigned int sel = ::SendMessage(mirrorCombo.GetHandle(), CB_GETCURSEL, 0, 0);
				mirrorCombo.Select(sel);
				mirror_controller.Invalidate();
			}
			break;
			case CBN_SELENDOK:
				mirrorCombo.ToggleSelected();
				//check if other combo is selected -> then enable the init button
				if (gratingCombo.IsSelected()){
					if (!::IsWindowEnabled(_btnInit.GetHandle())){
						::EnableWindow(_btnInit.GetHandle(), TRUE);
						::InvalidateRect(_btnInit.GetHandle(), NULL, TRUE);
					}
				}
				break;
			case CBN_DROPDOWN:			
				mirrorCombo.ToggleSelecting();
				break;			
			case CBN_KILLFOCUS:
				mirrorCombo.ToggleSelecting();
				break;
			case CBN_SELENDCANCEL:
				mirrorCombo.ToggleSelecting();
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
		gratingCombo.SubClass(&grating_controller);
		grating_controller.SubList();

		for (unsigned int i = 1; i < 2; i++){
			j = 1100 + i;						// combo control ids: [1100,1101]
			ComboMaker comb(_hwnd, j);
			comb.SetStyle(CBS_OWNERDRAWFIXED | CBS_DROPDOWNLIST);
			comb.Create("");
			comb.Show();
			mirrorCombo.Init(comb, j);
			mirrorCombo.Fill();
			mirrorCombo.SubClass(&mirror_controller);
			mirror_controller.SubList();
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

		::EnableWindow(_btnInit.GetHandle(), FALSE);

		::SetWindowPos(gratingCombo.GetHandle(), NULL, (gratingCombo.GetBasePos()).first, (gratingCombo.GetBasePos()).second, 136, 30, SWP_SHOWWINDOW );
		::SetWindowPos(mirrorCombo.GetHandle(), NULL, (mirrorCombo.GetBasePos()).first, (mirrorCombo.GetBasePos()).second, 136, 30, SWP_SHOWWINDOW);
//		::SetWindowPos(mirrorCombo.GetHandle(), NULL, 10, 84, 136, 30, SWP_SHOWWINDOW);
		//::SetWindowPos(_comboOpts[1]->GetHandle(), NULL, 10, 83, 136, 63, SWP_SHOWWINDOW);
		::SetWindowPos(_btnInit.GetHandle(), NULL, 67, 247, 103, 32, SWP_SHOWWINDOW);
		::SetWindowPos(_btnForce.GetHandle(), NULL, 67, 186, 79, 31, SWP_SHOWWINDOW);
		
		::SendMessage(gratingCombo.GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"300");
		::SendMessage(gratingCombo.GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"75");
		::SendMessage(gratingCombo.GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"600");
		::SendMessage(mirrorCombo.GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"Rear");
		::SendMessage(mirrorCombo.GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"Side");

		::SendMessage(gratingCombo.GetHandle(), CB_SETCURSEL, -1, NULL);
		::SendMessage(mirrorCombo.GetHandle(), CB_SETCURSEL, -1, NULL);

		return true;
	}

	bool MonoWndCtrl::OnDrawItem(LPARAM lParam)
	{		
		DRAWITEMSTRUCT* pDIS = reinterpret_cast<DRAWITEMSTRUCT*>(lParam);

		//DONE: Fix double click button problem - subclassing helped.
		bool res;
		switch (pDIS->CtlID) {
		case 1100:		//grating combo
			res = true;
			gratingCombo.Draw(pDIS->itemID, pDIS);
			break;
		case 1101:		//mirror combo
			res = true;
			mirrorCombo.Draw(pDIS->itemID, pDIS);
			break;
		case 1201:		//force init check button
			if (forceState == 0)
				res = _btnForce.Draw(0, pDIS);
			else
				res = _btnForce.Draw(1, pDIS);
			break;
		case 1200:		//init(start exp) button
			if (::IsWindowEnabled(_btnInit.GetHandle())){
				if (initState == 0)
					res = _btnInit.Draw(0, pDIS);
				else
					res = _btnInit.Draw(1, pDIS);
			} else {
				res = _btnInit.Draw(3, pDIS);
			}
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

		//copy progress bar:
		HBITMAP pro = (HBITMAP)progress_bmps[progress];
		::GetObject(progress_bmps[progress], sizeof(BITMAP), &bm);
		::SelectObject(compHDC, pro);
		::BitBlt(hDC, 23, 158, bm.bmWidth, bm.bmHeight, compHDC, 0, 0, SRCCOPY);

		::DeleteDC(compHDC);

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

	void MonoWndCtrl::UpdateProgress(int by)
	{
		if (progress + by <= 100){
			progress += by;
		} else { 
			progress = 100; 
		}

		::InvalidateRect(_hwnd, NULL, TRUE);
//		::MessageBox(NULL, "1", "Sec", MB_OK);
	}
};
