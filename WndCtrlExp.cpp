#include "WndCtrlExp.h"
#include "libWin\WinMaker.h"
#include <windowsx.h>
#include <sstream>
#include <iomanip>

namespace Win
{
	ExpWndController::ExpWndController()
	{
		InitMinXY(565, 568);

		//		_prog = 0;

		for (int i = 0; i < 13; i++){
			_stcArray[i] = new StaticControl(0);
		};

		for (int i = 0; i < 20; i++){
			_edtArray[i] = new EditControl(0);
		};

		for (int i = 0; i < 16; i++){
			_btnArray[i] = new ButtonControl(0);
		};
	};

	ExpWndController::~ExpWndController()
	{
		for (int i = 0; i < 13; i++){
			if (_stcArray[i] != NULL) delete _stcArray[i];
		};

		for (int i = 0; i < 20; i++){
			if (_edtArray[i] != NULL) delete _edtArray[i];
		};

		for (int i = 0; i < 16; i++){
			if (_btnArray[i] != NULL) delete _btnArray[i];
		};
	};

	bool ExpWndController::OnCommand(WPARAM wParam, LPARAM lParam)
	{
		switch (LOWORD(wParam))
		{
		case 2211:		//Back button				
			::SendMessage(::GetParent(_hwnd), WM_NOTIFY, 2211, NULL);
			break;
		case 2212:		//Stop button
			visibleRun();
			::SendMessage(::GetParent(_hwnd), WM_NOTIFY, 2212, NULL);
			break;
		case 2213:		//Run button
			visibleStop();
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

		::SetWindowPos(_hwnd, NULL, 330, 50, _minX, _minY, SWP_SHOWWINDOW);

		//static controls:

		for (int i = 0; i < 13; i++){
			int j = 2000 + i;
			StaticMaker stat(_hwnd, j);
			stat.NoBG();
			stat.AddExStyle(WS_EX_TRANSPARENT);
			stat.AddStyle(WS_CLIPSIBLINGS);
			stat.Create("");
			stat.Show();
			_stcArray[i]->Init(stat, j);
		};

		//edit controls:		
		for (int i = 0; i < 19; i++){
			int j = 2100 + i;
			EditMaker edit(_hwnd, j);
			edit.Create("");
			edit.Show();
			_edtArray[i]->Init(edit, j);
			_edtArray[i]->SubClass(&_edtCtrl[i]);
		};

		EditMaker edit(_hwnd, 2119);
		edit.AddStyle(ES_MULTILINE | ES_AUTOVSCROLL);
		edit.Create("");
		edit.Show();
		_edtArray[19]->Init(edit, 2119);
		_edtArray[19]->SubClass(&_edtCtrl[19]);

		for (int i = 0; i < 18; i += 2)
			Edit_Enable(_edtArray[i]->GetHandle(), false);
		Edit_Enable(_edtArray[19]->GetHandle(), false);

		//button controls:		
		for (int i = 0; i < 11; i++){
			int j = 2200 + i;
			ButtonMaker butt(_hwnd, j);
			if ((i == 2) || (i == 6) || (i == 10))
				butt.AddStyle(WS_GROUP);
			butt.AddStyle(BS_AUTORADIOBUTTON | WS_TABSTOP);
			butt.Create("");
			butt.Show();
			_btnArray[i]->Init(butt, j);
		};

		for (int i = 11; i < 14; i++){
			int j = 2200 + i;
			ButtonMaker butt(_hwnd, j);
			butt.Create("");
			butt.Show();
			_btnArray[i]->Init(butt, j);
		}

		for (int i = 14; i < 16; i++){
			int j = 2200 + i;
			ButtonMaker butt(_hwnd, j);
			butt.AddStyle(BS_GROUPBOX | WS_EX_TRANSPARENT);
			butt.Create("");
			butt.Show();
			_btnArray[i]->Init(butt, j);
		}

		::SendMessage(_stcArray[0]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Front slit [um]:");
		::SendMessage(_stcArray[1]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Exit slit [um]:");
		::SendMessage(_stcArray[2]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Start Point [eV]");
		::SendMessage(_stcArray[3]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"End Point [eV]");
		::SendMessage(_stcArray[4]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Increment [eV]");
		::SendMessage(_stcArray[5]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Set point [nm]");
		::SendMessage(_stcArray[6]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Y1");
		::SendMessage(_stcArray[7]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Y2");
		::SendMessage(_stcArray[8]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Y3");
		::SendMessage(_stcArray[9]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Time Const [s]");
		::SendMessage(_stcArray[10]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Point Count");
		::SendMessage(_stcArray[11]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Interval [s]");
		::SendMessage(_stcArray[12]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Output File:");

		::SendMessage(_btnArray[0]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Ch1");
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
		::SendMessage(_btnArray[11]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Back");
		::SendMessage(_btnArray[12]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Stop");
		::SendMessage(_btnArray[13]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Run");
		::SendMessage(_btnArray[14]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Mono settings");
		::SendMessage(_btnArray[15]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Homo settings");

		::SendMessage(_btnArray[0]->GetHandle(), BM_SETCHECK, BST_CHECKED, NULL);
		::SendMessage(_btnArray[4]->GetHandle(), BM_SETCHECK, BST_CHECKED, NULL);
		::SendMessage(_btnArray[9]->GetHandle(), BM_SETCHECK, BST_CHECKED, NULL);

		Button_Enable(_btnArray[12]->GetHandle(), false);

		return true;
	};

	bool ExpWndController::OnSize(int width, int height, int flags)
	{
		int xOff = 30, yOff = 30, xSpace = 10, ySpace = 10;	//offset
		int dxStatic = 95, dxEdit = 65, dyStatic = 20, dyEdit = 25;
		int xCol1 = xOff;
		int xCol2 = xCol1 + dxStatic + xSpace;
		int xCol3 = xCol2 + dxEdit + xSpace;
		int xCol4 = xCol3 + dxEdit + xSpace;
		int xCol5 = xCol4 + dxStatic + xSpace;
		int xCol6 = xCol5 + dxEdit + xSpace;

		int yRow[13];
		yRow[0] = 0;
		yRow[1] = yOff;
		for (int i = 2; i < 13; i++)
			yRow[i] = yOff + (i - 1)*dyEdit + (i - 1)*ySpace;

		::SetWindowPos(_btnArray[0]->GetHandle(), HWND_TOP, xCol4 + (dxStatic - dxEdit), yRow[2], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[1]->GetHandle(), HWND_TOP, xCol4 + (dxStatic - dxEdit), yRow[3], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[2]->GetHandle(), HWND_TOP, xCol4 + (dxStatic - dxEdit), yRow[4], dxEdit, dyEdit, SWP_SHOWWINDOW);

		::SetWindowPos(_btnArray[3]->GetHandle(), HWND_TOP, xCol5, yRow[2], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[4]->GetHandle(), HWND_TOP, xCol5, yRow[3], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[5]->GetHandle(), HWND_TOP, xCol5, yRow[4], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[6]->GetHandle(), HWND_TOP, xCol5, yRow[5], dxEdit, dyEdit, SWP_SHOWWINDOW);

		::SetWindowPos(_btnArray[7]->GetHandle(), HWND_TOP, xCol6, yRow[2], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[8]->GetHandle(), HWND_TOP, xCol6, yRow[3], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[9]->GetHandle(), HWND_TOP, xCol6, yRow[4], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[10]->GetHandle(), HWND_TOP, xCol6, yRow[5], dxEdit, dyEdit, SWP_SHOWWINDOW);

		::SetWindowPos(_btnArray[11]->GetHandle(), HWND_TOP, xCol4 + (dxStatic - dxEdit), yRow[9], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[12]->GetHandle(), HWND_TOP, xCol5, yRow[9], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[13]->GetHandle(), HWND_TOP, xCol6, yRow[9], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[14]->GetHandle(), HWND_TOP, xCol1 - 10, yRow[0], 2 * dxEdit + dxStatic + 3 * xSpace + 3, yRow[7] + 5, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[15]->GetHandle(), HWND_TOP, xCol4 - 5, yRow[0], 2 * dxEdit + dxStatic + 3 * xSpace, yRow[9] - 5, SWP_SHOWWINDOW);

		::SetWindowPos(_stcArray[0]->GetHandle(), HWND_TOP, xCol1, yRow[1], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Front slit"
		::SetWindowPos(_stcArray[1]->GetHandle(), HWND_TOP, xCol1, yRow[2], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Exit slit"
		::SetWindowPos(_stcArray[2]->GetHandle(), HWND_TOP, xCol1, yRow[3], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Start point"
		::SetWindowPos(_stcArray[3]->GetHandle(), HWND_TOP, xCol1, yRow[4], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"End point"
		::SetWindowPos(_stcArray[4]->GetHandle(), HWND_TOP, xCol1, yRow[5], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Increment"
		::SetWindowPos(_stcArray[5]->GetHandle(), HWND_TOP, xCol1, yRow[6], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Set point"
		::SetWindowPos(_stcArray[6]->GetHandle(), HWND_TOP, xCol4 + (dxStatic - dxEdit), yRow[1], dxEdit, dyStatic, SWP_SHOWWINDOW);	//"Y1"
		::SetWindowPos(_stcArray[7]->GetHandle(), HWND_TOP, xCol5, yRow[1], dxEdit, dyStatic, SWP_SHOWWINDOW);	//"Y2"
		::SetWindowPos(_stcArray[8]->GetHandle(), HWND_TOP, xCol6, yRow[1], dxEdit, dyStatic, SWP_SHOWWINDOW);	//"Y3"
		::SetWindowPos(_stcArray[9]->GetHandle(), HWND_TOP, xCol4, yRow[6], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Time Const"
		::SetWindowPos(_stcArray[10]->GetHandle(), HWND_TOP, xCol4, yRow[7], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Point Count"
		::SetWindowPos(_stcArray[11]->GetHandle(), HWND_TOP, xCol4, yRow[8], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Interval"
		::SetWindowPos(_stcArray[12]->GetHandle(), HWND_TOP, xCol1, yRow[9] + 10, dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Output file"
		//		::SetWindowPos(_stcArray[13]->GetHandle(), HWND_TOP, xCol1, yRow[11], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Output"

		::SetWindowPos(_edtArray[0]->GetHandle(), HWND_TOP, xCol2, yRow[1], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[1]->GetHandle(), HWND_TOP, xCol3, yRow[1], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[2]->GetHandle(), HWND_TOP, xCol2, yRow[2], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[3]->GetHandle(), HWND_TOP, xCol3, yRow[2], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[4]->GetHandle(), HWND_TOP, xCol2, yRow[3], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[5]->GetHandle(), HWND_TOP, xCol3, yRow[3], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[6]->GetHandle(), HWND_TOP, xCol2, yRow[4], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[7]->GetHandle(), HWND_TOP, xCol3, yRow[4], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[8]->GetHandle(), HWND_TOP, xCol2, yRow[5], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[9]->GetHandle(), HWND_TOP, xCol3, yRow[5], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[10]->GetHandle(), HWND_TOP, xCol2, yRow[6], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[11]->GetHandle(), HWND_TOP, xCol3, yRow[6], dxEdit, dyEdit, SWP_SHOWWINDOW);

		::SetWindowPos(_edtArray[12]->GetHandle(), HWND_TOP, xCol5, yRow[6], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[13]->GetHandle(), HWND_TOP, xCol6, yRow[6], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[14]->GetHandle(), HWND_TOP, xCol5, yRow[7], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[15]->GetHandle(), HWND_TOP, xCol6, yRow[7], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[16]->GetHandle(), HWND_TOP, xCol5, yRow[8], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[17]->GetHandle(), HWND_TOP, xCol6, yRow[8], dxEdit, dyEdit, SWP_SHOWWINDOW);

		::SetWindowPos(_edtArray[18]->GetHandle(), HWND_TOP, xCol1, yRow[10], xCol6 + 3 * xSpace, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[19]->GetHandle(), HWND_TOP, xCol1, yRow[11], xCol6 + 3 * xSpace, yRow[4], SWP_SHOWWINDOW);

		return true;
	};

	bool ExpWndController::OnNotify(HWND hFrom, LPARAM lParam)
	{
		stringstream text;
		char readBuff[255];
		if (hFrom == _edtArray[1]->GetHandle()){			//Front slit
			::SendMessage(_edtArray[1]->GetHandle(), EM_GETLINE, NULL, (LPARAM)readBuff);
			text << readBuff;
			int val;
			text >> val;
			text = stringstream();
			text << val;
////TODO: should send notification to parent window to change monos' front slit size
		}
		else if (hFrom == _edtArray[3]->GetHandle()){		//Exit slit
			::SendMessage(_edtArray[3]->GetHandle(), EM_GETLINE, NULL, (LPARAM)readBuff);
			text << readBuff;
			int val;
			text >> val;
			text = stringstream();
			text << val;
//TODO: should send notification to parent window to change monos' rear slit size
		}
		else if (hFrom == _edtArray[5]->GetHandle()){		//Start point
			::SendMessage(_edtArray[5]->GetHandle(), EM_GETLINE, NULL, (LPARAM)readBuff);
			text << readBuff;
			double val;
			text >> val;
			text = stringstream();
			text << setprecision(4) << fixed << val;
			text >> _startPos;
//TODO: should send notification to parent window to move mono
		}
		else if (hFrom == _edtArray[7]->GetHandle()){		//End point
			::SendMessage(_edtArray[7]->GetHandle(), EM_GETLINE, NULL, (LPARAM)readBuff);
			text << readBuff;
			double val;
			text >> val;
			text = stringstream();
			text << setprecision(4) << fixed << val;
			text >> _stopPos;
		}
		else if (hFrom == _edtArray[9]->GetHandle()){		//Increment
			::SendMessage(_edtArray[9]->GetHandle(), EM_GETLINE, NULL, (LPARAM)readBuff);
			text << readBuff;
			double val;
			text >> val;
			text = stringstream();
			text << setprecision(4) << fixed << val;
			text >> _incPos;
		}
		else if (hFrom == _edtArray[11]->GetHandle()){		//Set point
			::SendMessage(_edtArray[11]->GetHandle(), EM_GETLINE, NULL, (LPARAM)readBuff);
			text << readBuff;
			double val;
			text >> val;
			text = stringstream();
			text << setprecision(4) << fixed << val;
////TODO: should send notification to parent window to move mono
		}
		else if (hFrom == _edtArray[13]->GetHandle()){		//Time const
			::SendMessage(_edtArray[13]->GetHandle(), EM_GETLINE, NULL, (LPARAM)readBuff);
			text << readBuff;
			double val;
			text >> val;
			text = stringstream();
			text << setprecision(4) << fixed << val;
			text >> _timeConst;
		}
		else if (hFrom == _edtArray[15]->GetHandle()){		//point count
			::SendMessage(_edtArray[15]->GetHandle(), EM_GETLINE, NULL, (LPARAM)readBuff);
			text << readBuff;
			int val;
			text >> val;
			text = stringstream();
			text << setprecision(4) << fixed << val;
			text >> _pointCount;
		}
		else if (hFrom == _edtArray[17]->GetHandle()){		//interval
			::SendMessage(_edtArray[17]->GetHandle(), EM_GETLINE, NULL, (LPARAM)readBuff);
			text << readBuff;
			double val;
			text >> val;
			text = stringstream();
			text << setprecision(4) << fixed << val;
			text >> _interval;
		}

		return true;
	}

	void ExpWndController::ReturnExpParams(double* params)
	{
		params[0] = _startPos;
		params[1] = _stopPos;
		params[2] = _incPos;
		params[3] = _timeConst;
		params[4] = _pointCount;
		params[5] = _interval;
		return;
	};

	void ExpWndController::ReadExpParams()
	{
		stringstream params;
	};

	void ExpWndController::setEditVal(int editNum, string text)
	{
		::SendMessage(_edtArray[editNum]->GetHandle(), WM_SETTEXT, 0, (LPARAM)text.c_str());
		return;
	};

	void ExpWndController::UpdateEditBox(double* valArr, int num)
	{
		stringstream valStream;
		for (int i = 0; i < num; i++)
		{
			valStream << valArr[i] << "\t";
		}
		valStream << endl;

		::SendMessage(NULL, WM_SETTEXT, 0, (LPARAM)valStream.str().c_str());

		return;
	};

	void ExpWndController::visibleRun()
	{
		Button_Enable(_btnArray[12]->GetHandle(), false);
		Button_Enable(_btnArray[11]->GetHandle(), true);

		for (int i = 0; i < 19; i++)
			Edit_Enable(_edtArray[i]->GetHandle(), true);

		return;
	};

	void ExpWndController::visibleStop()
	{
		Button_Enable(_btnArray[12]->GetHandle(), true);
		Button_Enable(_btnArray[11]->GetHandle(), false);

		for (int i = 0; i < 20; i++)
			Edit_Enable(_edtArray[i]->GetHandle(), false);

		return;
	};
}