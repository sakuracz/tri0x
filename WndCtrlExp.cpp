#include "WndCtrlExp.h"
#include "libWin\WinMaker.h"
#include <sstream>
#include <iomanip>

namespace Win
{
	ExpWndController::ExpWndController()
	{
		InitMinXY(515, 568);

//		_prog = 0;
		
		for(int i = 0; i < 15; i++){
			_stcArray[i] = new StaticControl(0);
		};
		
		for(int i = 0; i < 20; i++){
			_edtArray[i] = new EditControl(0);
		};

		for(int i = 0; i < 16; i++){
			_btnArray[i] = new ButtonControl(0);
		};
	};

	ExpWndController::~ExpWndController()
	{		
		for(int i = 0; i < 10; i++){
			if(_stcArray[i] != NULL) delete _stcArray[i];
		};
		
		for(int i = 0; i < 4; i++){
			if(_edtArray[i] != NULL) delete _edtArray[i];
		};
		
		for(int i = 0; i < 4; i++){
			if(_btnArray[i] != NULL) delete _btnArray[i];
		};
	};

	bool ExpWndController::OnCommand(WPARAM wParam, LPARAM lParam)
	{
		switch(LOWORD(wParam))
		{
		case 3300:		//first tab's 'Set' button			
			::SendMessage(::GetParent(_hwnd), WM_NOTIFY, 3300, NULL);
			break;
		case 3301:		//second tab's 'Generic 1' button
			break;
		case 3302:		//second tab's 'Generic 2' button
			break;
		case 3303:		//second tab's 'Run' button
//			::MessageBox(NULL, "Starting", "Step1", MB_OK);			
			::SendMessage(::GetParent(_hwnd), WM_NOTIFY, 3303, NULL);
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
		for(int i = 0; i < 10; i++){
			int j = 3100 + i;
			StaticMaker stat(_hwnd, j);
			stat.NoBG();
			stat.AddExStyle(WS_EX_TRANSPARENT);
			stat.AddStyle(WS_CLIPSIBLINGS);
			stat.Create("");
			stat.Show();
			_stcArray[i]->Init(stat, j);
		};

		::SendMessage(_stcArray[0]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Selection:");		//Tab1 
		::SendMessage(_stcArray[1]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Time const");		//Tab1
		::SendMessage(_stcArray[2]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Sensitivity");		//Tab1
		::SendMessage(_stcArray[3]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Slope");			//Tab1
		::SendMessage(_stcArray[4]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Channel");			//Tab1
		::SendMessage(_stcArray[5]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Set to:");			//Tab2
		::SendMessage(_stcArray[6]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Start pos");		//Tab2
		::SendMessage(_stcArray[7]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"End pos");			//Tab2
		::SendMessage(_stcArray[8]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Increment");		//Tab2
		::SendMessage(_stcArray[9]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Interval");		//Tab2

		//edit controls:
		for(int i = 0; i < 20; i++){
			int j = 3200 + i;
			EditMaker edit(_hwnd, j);
			edit.Create("");
			edit.Show();
			_edtArray[i]->Init(edit, j);
//			_edtArray[i]->SubClass(&_edtCtrl[i]);
		};

		::SendMessageA(_edtArray[0]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"100000");
		::SendMessageA(_edtArray[1]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"600000");
		::SendMessageA(_edtArray[2]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"1000");
		::SendMessageA(_edtArray[3]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"200");

		//button controls:
		for(int i = 0; i < 4; i++){
			int j = 3300 + i;
			ButtonMaker butt(_hwnd, j);
			butt.Create("");
			butt.Show();
			_btnArray[i]->Init(butt, j);
		};

		::SendMessage(_btnArray[0]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Set");			//tab1
		::SendMessage(_btnArray[1]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Gen1");		//tab2
		::SendMessage(_btnArray[2]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Gen2");		//tab2
		::SendMessage(_btnArray[3]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Run");			//tab2
		


		return true;
	};

	bool ExpWndController::OnSize(int width, int height, int flags)
	{
	
		int dx = 10, dy = 10, sx = 75, sy = 25, tdy = 30;
		int r00x = dx, r00y = dy + tdy, r01x = r00x + sx + dx, r01y = r00y, r02x = r01x + sx + dx, r02y = r01y;
		int r10x = r00x, r10y = r00y + sy + dy, r11x = r01x, r11y = r10y, r12x = r02x, r12y = r10y;
		int r20x = r10x, r20y = r10y + sy + dy, r21x = r11x, r21y = r20y, r22x = r12x, r22y = r20y;
		int r30x = r20x, r30y = r20y + sy + dy, r31x = r21x, r31y = r30y, r32x = r22x, r32y = r30y;
		int r40x = r30x, r40y = r30y + sy + dy, r41x = r31x, r41y = r40y, r42x = r32x, r42y = r40y;

		::SetWindowPos(_stcArray[0]->GetHandle(), HWND_TOP, r01x, r01y, sx,sy, SWP_SHOWWINDOW);			//tab1
		::SetWindowPos(_stcArray[1]->GetHandle(), HWND_TOP, r10x, r10y, sx,sy, SWP_SHOWWINDOW);			//tab1
		::SetWindowPos(_stcArray[2]->GetHandle(), HWND_TOP, r20x, r20y, sx,sy, SWP_SHOWWINDOW);			//tab1
		::SetWindowPos(_stcArray[3]->GetHandle(), HWND_TOP, r30x, r30y, sx,sy, SWP_SHOWWINDOW);			//tab1
		::SetWindowPos(_stcArray[4]->GetHandle(), HWND_TOP, r40x, r40y, sx,sy, SWP_SHOWWINDOW);			//tab1
		::SetWindowPos(_stcArray[5]->GetHandle(), HWND_TOP, r01x, r01y, sx,sy, SWP_SHOWWINDOW);			//tab2
		::SetWindowPos(_stcArray[6]->GetHandle(), HWND_TOP, r10x, r10y, sx,sy, SWP_SHOWWINDOW);			//tab2
		::SetWindowPos(_stcArray[7]->GetHandle(), HWND_TOP, r20x, r20y, sx,sy, SWP_SHOWWINDOW);			//tab2
		::SetWindowPos(_stcArray[8]->GetHandle(), HWND_TOP, r30x, r30y, sx,sy, SWP_SHOWWINDOW);			//tab2
		::SetWindowPos(_stcArray[9]->GetHandle(), HWND_TOP, r40x, r40y, sx,sy, SWP_SHOWWINDOW);			//tab2
	
		::SetWindowPos(_edtArray[0]->GetHandle(), HWND_TOP, r11x, r11y, sx, sy, SWP_SHOWWINDOW);			//tab2
		::SetWindowPos(_edtArray[1]->GetHandle(), HWND_TOP, r21x, r21y, sx, sy, SWP_SHOWWINDOW);			//tab2
		::SetWindowPos(_edtArray[2]->GetHandle(), HWND_TOP, r31x, r31y, sx, sy, SWP_SHOWWINDOW);			//tab2
		::SetWindowPos(_edtArray[3]->GetHandle(), HWND_TOP, r41x, r41y, sx, sy, SWP_SHOWWINDOW);			//tab2

		::SetWindowPos(_btnArray[0]->GetHandle(), HWND_TOP, r42x, r42y, sx, sy, SWP_SHOWWINDOW);			//tab1
		::SetWindowPos(_btnArray[1]->GetHandle(), HWND_TOP, r22x, r22y, sx, sy, SWP_SHOWWINDOW);			//tab2
		::SetWindowPos(_btnArray[2]->GetHandle(), HWND_TOP, r32x, r32y, sx, sy, SWP_SHOWWINDOW);			//tab2
		::SetWindowPos(_btnArray[3]->GetHandle(), HWND_TOP, r42x, r42y, sx, sy, SWP_SHOWWINDOW);			//tab2		

		return true;
	};

	bool ExpWndController::OnNotify(HWND hFrom, LPARAM lParam)
	{
		return false;
	}

	void ExpWndController::ReturnExpParams(int* params)
	{
//		params[0] = _startPos;
//		params[1] = _stopPos;
//		params[2] = _incPos;
//		params[3] = _interval;
		return;
	};

	void ExpWndController::ReturnSet(int* params)
	{
//		params[0] = _timeConst;
//		params[1] = _sens;
//		params[2] = _slope;
//		params[3] = _chann;
	};

	void ExpWndController::visibleRun()
	{
		::SendMessage(_btnArray[3]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Run");
	};

	void ExpWndController::visibleStop()
	{
		::SendMessage(_btnArray[3]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Stop");
	};

//	void ExpWndController::startExp()
//	{
//		_prog = 3;
//	};

//	void ExpWndController::ResetProg()
//	{
//		_prog = 0;
//	};
};