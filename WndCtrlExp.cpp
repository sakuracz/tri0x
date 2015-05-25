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
		
		for(int i = 0; i < 10; i++){
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
		
		for(int i = 0; i < 20; i++){
			if(_edtArray[i] != NULL) delete _edtArray[i];
		};
		
		for(int i = 0; i < 16; i++){
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
		int j = 2000;
		for(int i = 0; i < 10; i++){
			j += i;
			StaticMaker stat(_hwnd, j);
			stat.NoBG();
			stat.AddExStyle(WS_EX_TRANSPARENT);
			stat.AddStyle(WS_CLIPSIBLINGS);
			stat.Create("");
			stat.Show();
			_stcArray[i]->Init(stat, j);
		};

		::SendMessage(_stcArray[0]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Front slit:");		
		::SendMessage(_stcArray[1]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Exit slit:");		
		::SendMessage(_stcArray[2]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Start Point");		
		::SendMessage(_stcArray[3]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"End Point");			
		::SendMessage(_stcArray[4]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Increment");			
		::SendMessage(_stcArray[5]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Time Const");			
		::SendMessage(_stcArray[6]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Point Count");		
		::SendMessage(_stcArray[7]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Interval");			
		::SendMessage(_stcArray[8]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"OutputFile");		
		::SendMessage(_stcArray[9]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Interval");		

		//edit controls:
		j = 2100;
		for(int i = 0; i < 20; i++){
			j += i;
			EditMaker edit(_hwnd, j);
			if (i % 2)
				edit.AddStyle(WS_DISABLED);
			edit.Create("");
			edit.Show();
			_edtArray[i]->Init(edit, j);
//			_edtArray[i]->SubClass(&_edtCtrl[i]);
			::SendMessageA(_edtArray[i]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"0");		
		};

		//button controls:
		j = 2200;
		for(int i = 0; i < 16; i++){
			j += i;
			ButtonMaker butt(_hwnd, j);
			butt.Create("");
			butt.Show();
			_btnArray[i]->Init(butt, j);
		};

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