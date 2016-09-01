#include "WndCtrlMonoSetup.h"
#include "libWin\WinMaker.h"
#include <string>
#include <sstream>

using std::string;
using std::stringstream;

namespace Win{
	MonoWndCtrl::MonoWndCtrl()
	{
		itemIndex = 0;		
		for (int i = 0; i < 2; i++){
			_comboOpts[i] = new ComboControl(0);
		}
		
		_btnForce.LoadBMPs(string("switch"));
		_btnInit.LoadBMPs(string("init"));

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

		for (unsigned int i = 0; i < combo_count; i++){
			delete _comboOpts[i];
		}				
	}

	bool MonoWndCtrl::GetInitParams(int *outArr)
	{
		outArr[0] = ::SendMessage(_comboOpts[0]->GetHandle(), CB_GETCURSEL, NULL, NULL);
		outArr[1] = ::SendMessage(_comboOpts[1]->GetHandle(), CB_GETCURSEL, NULL, NULL);
		outArr[2] = forceState;
		
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
		if (LOWORD(wParam) == 1200){	// run button pressed - notify parent window
			initState = initState ^ 1;
			::SendMessage(::GetParent(_hwnd), WM_NOTIFY, 1200, NULL);
		}
		if (LOWORD(wParam) == 1201){	//switch the state of the "Force init" button
			forceState = forceState ^ 1;
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
		for (unsigned int i = 0; i < 2; i++){
			j += i;						// combo control ids: [1100,1101]
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

		::SetWindowPos(_comboOpts[0]->GetHandle(), NULL, 10, 11, 136, 63, SWP_SHOWWINDOW);
		::SetWindowPos(_comboOpts[1]->GetHandle(), NULL, 10, 83, 136, 63, SWP_SHOWWINDOW);
		::SetWindowPos(_btnInit.GetHandle(), NULL, 67, 247, 103, 32, SWP_SHOWWINDOW);
		::SetWindowPos(_btnForce.GetHandle(), NULL, 67, 186, 79, 31, SWP_SHOWWINDOW);

		::SendMessage(_comboOpts[0]->GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"300");
		::SendMessage(_comboOpts[0]->GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"75");
		::SendMessage(_comboOpts[0]->GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"600");
		::SendMessage(_comboOpts[1]->GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"Rear");
		::SendMessage(_comboOpts[1]->GetHandle(), CB_ADDSTRING, NULL, (LPARAM)"Side");

		::SendMessage(_comboOpts[0]->GetHandle(), CB_SETCURSEL, 0, NULL);
		::SendMessage(_comboOpts[1]->GetHandle(), CB_SETCURSEL, 0, NULL);

		return true;
	}

	bool MonoWndCtrl::OnDrawItem(LPARAM lParam)
	{		
		DRAWITEMSTRUCT* pDIS = reinterpret_cast<DRAWITEMSTRUCT*>(lParam);

		//DONE: Fix double click button problem - subclassing helped.
		bool res;
		switch (pDIS->CtlID) {
		case 1201:			
			if (forceState == 0)
				res = _btnForce.Draw(1, pDIS);
			else
				res = _btnForce.Draw(0, pDIS);
			break;
		case 1200:
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
		//TODO: draw background
		RECT rcClient;
		::GetClientRect(_hwnd, &rcClient);
		RECT rcImage;
		BITMAP bm;
		LONG cxBitmap, cyBitmap;
		if (GetObject(background_bmp, sizeof(bm), &bm)){
			cxBitmap = bm.bmWidth;
			cyBitmap = bm.bmHeight;
		}
		CopyRect(&rcImage, &rcClient);
		LONG image_width = rcImage.right - rcImage.left;
		LONG image_height = rcImage.bottom - rcImage.top;
		rcImage.left = (image_width - cxBitmap) / 2;
		rcImage.top = (image_height - cyBitmap) / 2;
		DrawState(hDC, NULL, NULL, (LPARAM)background_bmp, 0, rcImage.left, rcImage.top, rcImage.right - rcImage.left, rcImage.bottom - rcImage.top, DSS_NORMAL | DST_BITMAP);
		return true;
	}
};