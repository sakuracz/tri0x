#include "WndCtrlExp.h"
#include "libWin/WinMaker.h"
#include <windowsx.h>
#include <sstream>
#include <iomanip>

namespace Win
{
	ExpWndController::ExpWndController() 
		: radio_controller(custom_radio), edit_controller(custom_edit)
	{
		//		_prog = 0;

		run_button.LoadBMPs("run");
		back_button.LoadBMPs("back");
		stop_button.LoadBMPs("stop");

		for (int i = 0; i < 20; i++){
			_edtArray[i] = new EditControl(0);
		};

		for (int i = 1; i < 14; i++){
			_btnArray[i] = new ButtonControl(0);
		};

		string bg_name = string("res/WndCtrlExpBg.bmp");
		background_bmp = ::LoadImage(NULL, bg_name.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (background_bmp == NULL){
			DWORD dw = GetLastError();
			stringstream stream;
			stream << "Got error #: " << dw;
			::MessageBox(NULL, stream.str().c_str(), "Failed to load ExpWnd background image.", MB_OK | MB_ICONERROR);
		}
	};

	ExpWndController::~ExpWndController()
	{
		for (int i = 0; i < 20; i++){
			if (_edtArray[i] != NULL) delete _edtArray[i];
		};

		for (int i = 1; i < 14; i++){
			if (_btnArray[i] != NULL) delete _btnArray[i];
		};
	};

	bool ExpWndController::OnCommand(WPARAM wParam, LPARAM lParam)
	{
		switch (LOWORD(wParam))
		{
		//2200-2210 radio buttons BN_CLICKED notifications
		case 2200:
			if (HIWORD(wParam) == BN_CLICKED){
				
			}
			break;
		case 2201:
			if (HIWORD(wParam) == BN_CLICKED){

			}
			break;
		case 2202:
			if (HIWORD(wParam) == BN_CLICKED){

			}
			break;		
		case 2203:
			if (HIWORD(wParam) == BN_CLICKED){

			}
			break;
		case 2204:
			if (HIWORD(wParam) == BN_CLICKED){

			}
			break;
		case 2205:
			if (HIWORD(wParam) == BN_CLICKED){

			}
			break;
		case 2206:
			if (HIWORD(wParam) == BN_CLICKED){

			}
			break;
		case 2207:
			if (HIWORD(wParam) == BN_CLICKED){

			}
			break;
		case 2208:
			if (HIWORD(wParam) == BN_CLICKED){

			}
			break;
		case 2209:
			if (HIWORD(wParam) == BN_CLICKED){

			}
			break;
		case 2210:
			if (HIWORD(wParam) == BN_CLICKED){

			}
			break;
		case 2211:		//Back button				
			::SendMessage(::GetParent(_hwnd), WM_NOTIFY, 2211, NULL);
			break;
		case 2212:		//Stop button
			stopPressed = !stopPressed;
			VisibleRun();
			::SendMessage(::GetParent(_hwnd), WM_NOTIFY, 2212, NULL);
			if (runPressed){
				runPressed = !runPressed;
				::InvalidateRect(run_button, NULL, TRUE);
			}
			stopPressed = !stopPressed;
			break;
		case 2213:		//Run button
			if (!runPressed)
				runPressed = !runPressed;
			VisibleStop();
			::SendMessage(::GetParent(_hwnd), WM_NOTIFY, 2213, NULL);
			break;
		}
		return true;
	};

	bool ExpWndController::OnCreate(CreateData const* data)
	{
		RECT rect;
		::SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
		int maxX = rect.right;
		int maxY = rect.bottom;

		RECT desired;
		desired.left = 0;
		desired.right = 565;
		desired.top = 0;
		desired.bottom = 568;

		::AdjustWindowRect(&desired, ::GetWindowLong(_hwnd, GWL_STYLE), FALSE);

		int width = desired.right - desired.left;
		int height = desired.bottom - desired.top;
		InitMinXY(width, height);
		::SetWindowPos(_hwnd, NULL, (maxX - width) / 2, (maxY - height) / 2, width, height, SWP_SHOWWINDOW);

		{
			int j = 2100;
			EditMaker edit(_hwnd, j);
			edit.Create("");
			edit.Show();
			custom_edit.Init(edit, j);
			custom_edit.SubClass(&edit_controller);
		}
		//edit controls:		
		for (int i = 1; i < 19; i++){
			int j = 2100 + i;
			EditMaker edit(_hwnd, j);
//			edit.AddExStyle(WS_EX_NOBOR);
			edit.Create("");
			edit.Show();
			_edtArray[i]->Init(edit, j);
//			_edtArray[i]->SubClass(&_edtCtrl[i]);
		};

		EditMaker edit(_hwnd, 2119);
		edit.AddStyle(WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN | ES_READONLY);
		edit.Create("");
		edit.Show();
		_edtArray[19]->Init(edit, 2119);
//		_edtArray[19]->SubClass(&_edtCtrl[19]);

		for (int i = 0; i < 18; i += 2)
			Edit_Enable(_edtArray[i]->GetHandle(), false);
		Edit_Enable(_edtArray[19]->GetHandle(), true);

		//create custom radio button
		ButtonMaker butt(_hwnd, 2200);
		butt.AddStyle(BS_AUTORADIOBUTTON | WS_TABSTOP);
		butt.Create("");
		butt.Show();
		custom_radio.Init(butt, 2200);
		custom_radio.LoadBMPs(string("radio"));
		custom_radio.SubClass(&radio_controller);

		//button controls:		
		for (int i = 1; i < 11; i++){
			int j = 2200 + i;
			ButtonMaker butt(_hwnd, j);
			if ((i == 2) || (i == 6) || (i == 10))
				butt.AddStyle(WS_GROUP);
			butt.AddStyle(BS_AUTORADIOBUTTON | WS_TABSTOP);
			butt.Create("");
			butt.Show();
			_btnArray[i]->Init(butt, j);
		};
		
		int j = 2211;
		{
			ButtonMaker butt(_hwnd, j);
			butt.SetStyle(BS_OWNERDRAW);
			butt.Create("");
			butt.Show();
			back_button.Init(butt, j);
		}
		j++;
		{
			ButtonMaker butt(_hwnd, j);
			butt.SetStyle(BS_OWNERDRAW);
			butt.Create("");
			butt.Show();
			stop_button.Init(butt, j);
		}
		j++;
		{
			ButtonMaker butt(_hwnd, j);
			butt.SetStyle(BS_OWNERDRAW);
			butt.Create("");
			butt.Show();
			run_button.Init(butt, j);
		}

		::SendMessage(custom_radio.GetHandle(), WM_SETTEXT, 0, (LPARAM)"Ch1");
		::SendMessage(_btnArray[1]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Ch2");
		::SendMessage(_btnArray[2]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Inp1");
		::SendMessage(_btnArray[3]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Ch1");
		::SendMessage(_btnArray[4]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Ch2");
		::SendMessage(_btnArray[5]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Inp1");
		::SendMessage(_btnArray[6]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"none");
		::SendMessage(_btnArray[7]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Ch1");
		::SendMessage(_btnArray[8]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Ch2");
		::SendMessage(_btnArray[9]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Inp1");
		::SendMessage(_btnArray[10]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"none");
//		::SendMessage(_btnArray[11]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Back");
//		::SendMessage(_btnArray[12]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Stop");
//		::SendMessage(_btnArray[13]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Run");

		::SendMessage(custom_radio.GetHandle(), BM_SETCHECK, BST_CHECKED, NULL);
		::SendMessage(_btnArray[4]->GetHandle(), BM_SETCHECK, BST_CHECKED, NULL);
		::SendMessage(_btnArray[9]->GetHandle(), BM_SETCHECK, BST_CHECKED, NULL);

		Button_Enable(_btnArray[12]->GetHandle(), false);

		return true;
	};

	bool ExpWndController::OnDrawItem(LPARAM lParam)
	{
		DRAWITEMSTRUCT* pDIS = reinterpret_cast<DRAWITEMSTRUCT*>(lParam);
		switch (pDIS->CtlID)
		{
		case 2211:		//back button:
			if (::IsWindowEnabled(back_button.GetHandle()))
			{
				if (backPressed == 0)
					back_button.Draw(0, pDIS);
				else
					back_button.Draw(1, pDIS);
			} else {
				back_button.Draw(3, pDIS);
			}
			break;		
		case 2212:		//stop button:
			if (::IsWindowEnabled(stop_button.GetHandle()))
			{
				if (stopPressed == 0)
					stop_button.Draw(0, pDIS);
				else
					stop_button.Draw(1, pDIS);
			}
			else {
				stop_button.Draw(3, pDIS);
			}
			break;
		case 2213:		//run button:

				if (runPressed == 0)
					run_button.Draw(0, pDIS);
				else
					run_button.Draw(1, pDIS);
			
			break;
		}

		return true;
	}

	bool ExpWndController::OnEraseBG(HDC hDC)
	{
		HDC compHDC = ::CreateCompatibleDC(hDC);
		BITMAP bm;
		HBITMAP bg = (HBITMAP)background_bmp;
		::GetObject(background_bmp, sizeof(BITMAP), &bm);
		::SelectObject(compHDC, bg);
		::BitBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight, compHDC, 0, 0, SRCCOPY);

		::DeleteDC(compHDC);

		return true;
	}

	bool ExpWndController::OnSize(int width, int height, int flags)
	{		
		int dxShortEdit = 63, dyShortEdit = 26;
		int dxEdit = 107, dyEdit = 27;
		int dxFileEdit = 387, dyFileEdit = 27;
		int dxOutEdit = 507, dyOutEdit = 144;
		int dxRadio = 22, dyRadio = 22;
		int dxButton = 100, dyButton = 30;

		int xCol1 = 147, yRow1 = 32;	//left mono edits
		int xCol2 = 210, yRow2 = 69;	//right mono edits
		int xCol3 = 423, yRow3 = 106;	//left radio group
		int xCol4 = 467, yRow4 = 143;	//mid radio group
		int xCol5 = 510, yRow5 = 180;	//right radio group
		int xCol6 = 426, yRow6 = 217;	//homo edits
		int xCol7 = 50, yRow7 = 254;	//buttons left
		int xCol8 = 161, yRow8 = 291;	//buttons (run) right
		int xCol9 = 147, yRow9 = 342;	//file edit
		int xColA = 27, yRowA = 410;
		//radios:
		::SetWindowPos(custom_radio.GetHandle(), HWND_TOP, xCol3, yRow2 + 3, dxRadio, dyRadio, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[1]->GetHandle(), HWND_TOP, xCol3, yRow3, dxRadio, dyRadio, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[2]->GetHandle(), HWND_TOP, xCol3, yRow4, dxRadio, dyRadio, SWP_SHOWWINDOW);

		::SetWindowPos(_btnArray[3]->GetHandle(), HWND_TOP, xCol4, yRow2, dxRadio, dyRadio, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[4]->GetHandle(), HWND_TOP, xCol4, yRow3, dxRadio, dyRadio, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[5]->GetHandle(), HWND_TOP, xCol4, yRow4, dxRadio, dyRadio, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[6]->GetHandle(), HWND_TOP, xCol4, yRow5, dxRadio, dyRadio, SWP_SHOWWINDOW);

		::SetWindowPos(_btnArray[7]->GetHandle(), HWND_TOP, xCol5, yRow2, dxRadio, dyRadio, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[8]->GetHandle(), HWND_TOP, xCol5, yRow3, dxRadio, dyRadio, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[9]->GetHandle(), HWND_TOP, xCol5, yRow4, dxRadio, dyRadio, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[10]->GetHandle(), HWND_TOP, xCol5, yRow5, dxRadio, dyRadio, SWP_SHOWWINDOW);
		//pushbuttons:
		::SetWindowPos(back_button.GetHandle(), HWND_TOP, xCol7, yRow8 + 3, dxButton, dyButton, SWP_SHOWWINDOW);
		::SetWindowPos(stop_button.GetHandle(), HWND_TOP, xCol7, yRow7 + 3, dxButton, dyButton, SWP_SHOWWINDOW);
		::SetWindowPos(run_button.GetHandle(), HWND_TOP, xCol8, yRow8 + 3, dxButton, dyButton, SWP_SHOWWINDOW);
		//edits:
		::SetWindowPos(custom_edit.GetHandle(), HWND_TOP, xCol1, yRow1, dxShortEdit, dyShortEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[1]->GetHandle(), HWND_TOP, xCol2, yRow1, dxShortEdit, dyShortEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[2]->GetHandle(), HWND_TOP, xCol1, yRow2, dxShortEdit, dyShortEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[3]->GetHandle(), HWND_TOP, xCol2, yRow2, dxShortEdit, dyShortEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[4]->GetHandle(), HWND_TOP, xCol1, yRow3, dxShortEdit, dyShortEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[5]->GetHandle(), HWND_TOP, xCol2, yRow3, dxShortEdit, dyShortEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[6]->GetHandle(), HWND_TOP, xCol1, yRow4, dxShortEdit, dyShortEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[7]->GetHandle(), HWND_TOP, xCol2, yRow4, dxShortEdit, dyShortEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[8]->GetHandle(), HWND_TOP, xCol1, yRow5, dxShortEdit, dyShortEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[9]->GetHandle(), HWND_TOP, xCol2, yRow5, dxShortEdit, dyShortEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[10]->GetHandle(), HWND_TOP, xCol1, yRow6, dxShortEdit, dyShortEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[11]->GetHandle(), HWND_TOP, xCol2, yRow6, dxShortEdit, dyShortEdit, SWP_SHOWWINDOW);

		::SetWindowPos(_edtArray[12]->GetHandle(), HWND_TOP, xCol6, yRow6, dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[13]->GetHandle(), HWND_TOP, xCol6, yRow6, dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[14]->GetHandle(), HWND_TOP, xCol6, yRow7, dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[15]->GetHandle(), HWND_TOP, xCol6, yRow7, dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[16]->GetHandle(), HWND_TOP, xCol6, yRow8, dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[17]->GetHandle(), HWND_TOP, xCol6, yRow8, dxEdit, dyEdit, SWP_SHOWWINDOW);

		::SetWindowPos(_edtArray[18]->GetHandle(), HWND_TOP, xCol9, yRow9, dxFileEdit, dyFileEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[19]->GetHandle(), HWND_TOP, xColA, yRowA, dxOutEdit, dyOutEdit, SWP_SHOWWINDOW);

		::EnableWindow(stop_button.GetHandle(), FALSE);

		return true;
	};

	bool ExpWndController::OnNotify(HWND hFrom, LPARAM lParam)
	{				
		if (hFrom == _edtArray[1]->GetHandle()){			//Front slit
			int width = static_cast<int>(GetEditVal(1));
			::SendMessage(::GetParent(_hwnd), WM_NOTIFY, 2101, (LPARAM)width);
		}
		else if (hFrom == _edtArray[3]->GetHandle()){		//Exit slit
			int width = static_cast<int>(GetEditVal(3));
			::SendMessage(::GetParent(_hwnd), WM_NOTIFY, 2103, (LPARAM)width);
		}
		else if (hFrom == _edtArray[5]->GetHandle()){		//Start point
			_startPos = GetEditVal(5);
			::SendMessage(::GetParent(_hwnd), WM_NOTIFY, 2105, 0);
		}
		else if (hFrom == _edtArray[7]->GetHandle()){		//End point	
			_stopPos = GetEditVal(7);
			stringstream text;
			text << setprecision(4) << fixed << _stopPos;
			::SendMessage(_edtArray[6]->GetHandle(), WM_SETTEXT, NULL, (LPARAM)text.str().c_str());
		}
		else if (hFrom == _edtArray[9]->GetHandle()){		//Increment
			_incPos = GetEditVal(9);
			stringstream text;
			text << setprecision(4) << fixed << _incPos;
			::SendMessage(_edtArray[8]->GetHandle(), WM_SETTEXT, NULL, (LPARAM)text.str().c_str());
		}
		else if (hFrom == _edtArray[11]->GetHandle()){		//Set point
			GetEditVal(11);
			::SendMessage(::GetParent(_hwnd), WM_NOTIFY, 2111, 0);
		}
		else if (hFrom == _edtArray[13]->GetHandle()){		//Time const
			_timeConst = GetEditVal(13);
		}
		else if (hFrom == _edtArray[15]->GetHandle()){		//point count
			_pointCount = static_cast<int>(GetEditVal(15));
		}
		else if (hFrom == _edtArray[17]->GetHandle()){		//interval
			_interval = GetEditVal(17);
		}

		return true;
	}

	void ExpWndController::ReturnExpParams(vector<double>& params)
	{
		params[0] = _startPos;
		params[1] = _stopPos;
		params[2] = _incPos;
		params[3] = 1000 * _timeConst;
		params[4] = _pointCount;
		params[5] = 1000 * _interval;
		return;
	};

	void ExpWndController::SetEditVal(int editNum, string text)
	{
		::SendMessage(_edtArray[editNum]->GetHandle(), WM_SETTEXT, 0, (LPARAM)text.c_str());
		return;
	};

	void ExpWndController::UpdateEditBox(vector<double>& valArr, int num)
	{
		stringstream valStream;
		for (int i = 0; i < num; i++)
		{
			valStream << setprecision(5) << fixed << valArr[i] << "\t";
		}
		valStream << "\r\n";

		::SendMessage(_edtArray[19]->GetHandle(), EM_REPLACESEL, 0, (LPARAM)valStream.str().c_str());

		return;
	};

	void ExpWndController::VisibleRun()
	{
		Button_Enable(stop_button.GetHandle(), false);
		Button_Enable(back_button.GetHandle(), true);
		Button_Enable(run_button.GetHandle(), true);

		for (int i = 1; i < 19; i+=2)
			Edit_Enable(_edtArray[i]->GetHandle(), true);

		return;
	};

	void ExpWndController::VisibleStop()
	{
		Button_Enable(run_button.GetHandle(), false);
		Button_Enable(stop_button.GetHandle(), true);
		Button_Enable(back_button.GetHandle(), false);

		for (int i = 1; i < 20; i+=2)
			Edit_Enable(_edtArray[i]->GetHandle(), false);

		return;
	};

	void ExpWndController::UpdatePos(double energy)
	{
		stringstream textEV, textNM;
		double wavelength = energy / 1238.9;

		textEV << energy;
		textNM << wavelength;

		::SendMessage(_edtArray[4]->GetHandle(), WM_SETTEXT, 0, (LPARAM)textEV.str().c_str());
		::SendMessage(_edtArray[10]->GetHandle(), WM_SETTEXT, 0, (LPARAM)textNM.str().c_str());
	}

	double ExpWndController::GetEditVal(int num)
	{
		stringstream text;
		double val;
		char readBuff[255];

		::SendMessage(_edtArray[num]->GetHandle(), EM_GETLINE, NULL, (LPARAM)readBuff);
		text << readBuff;
		text << setprecision(4) << fixed;
		text >> val;

		return val;
	};
}
