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
		
		for(int i = 0; i < 13; i++){
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
		for(int i = 0; i < 13; i++){
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
		for(int i = 0; i < 13; i++){
			j = 2000 + i;
			StaticMaker stat(_hwnd, j);
			stat.NoBG();
			stat.AddExStyle(WS_EX_TRANSPARENT);			
			stat.Create("");
			stat.Show();
			_stcArray[i]->Init(stat, j);
		};

		::SendMessage(_stcArray[0]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Front slit [um]:");		
		::SendMessage(_stcArray[1]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Exit slit [um]:");		
		::SendMessage(_stcArray[2]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Start Point [eV]");		
		::SendMessage(_stcArray[3]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"End Point [eV]");			
		::SendMessage(_stcArray[4]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Increment [eV]");	
		::SendMessage(_stcArray[5]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Set point [nm]");
		::SendMessage(_stcArray[6]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Y1");
		::SendMessage(_stcArray[7]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Y2");
		::SendMessage(_stcArray[8]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Y3");
		::SendMessage(_stcArray[9]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Time Const");			
		::SendMessage(_stcArray[10]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Point Count");		
		::SendMessage(_stcArray[11]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Interval");				
		::SendMessage(_stcArray[12]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Output File:");
		::SendMessage(_stcArray[13]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Output");

		//edit controls:		
		for(int i = 0; i < 20; i++){
			j = 2100 + i;
			EditMaker edit(_hwnd, j);
//			if (i % 2)
//				edit.AddStyle(ES_READONLY | ES_AUTOVSCROLL);
			edit.Create("");
			edit.Show();
			_edtArray[i]->Init(edit, j);
//			_edtArray[i]->SubClass(&_edtCtrl[i]);
			::SendMessageA(_edtArray[i]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"ksjdtbwk");		
		};

		//button controls:		
		for(int i = 0; i < 16; i++){
			j = 2200 + i;
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
		int xOff = 30, yOff = 30, xSpace = 10, ySpace = 10;	//offset
		int dxStatic = 90, dxEdit = 65, dyStatic = 20, dyEdit = 20;
		int xCol1 = xOff;
		int xCol2 = xCol1 + dxStatic + xSpace;
		int xCol3 = xCol2 + dxEdit + xSpace;
		int xCol4 = xCol3 + dxEdit + xSpace;
		int xCol5 = xCol4 + dxStatic + xSpace;
		int xCol6 = xCol5 + dxEdit + xSpace;

		int yRow[13];
		yRow[0] = 0;
		yRow[1] = yOff;
		for (int i = 0; i < 13; i++)
			yRow[i] = yOff + i*dyEdit + i*ySpace;

		::SetWindowPos(_stcArray[0]->GetHandle(), HWND_TOP, xCol1, yRow[1], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Front slit"
		::SetWindowPos(_stcArray[1]->GetHandle(), HWND_TOP, xCol1, yRow[2], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Exit slit"
		::SetWindowPos(_stcArray[2]->GetHandle(), HWND_TOP, xCol1, yRow[3], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Start point"
		::SetWindowPos(_stcArray[3]->GetHandle(), HWND_TOP, xCol1, yRow[4], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"End point"
		::SetWindowPos(_stcArray[4]->GetHandle(), HWND_TOP, xCol1, yRow[5], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Increment"
		::SetWindowPos(_stcArray[5]->GetHandle(), HWND_TOP, xCol1, yRow[6], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Set point"
		::SetWindowPos(_stcArray[6]->GetHandle(), HWND_TOP, xCol4, yRow[1], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Y1"
		::SetWindowPos(_stcArray[7]->GetHandle(), HWND_TOP, xCol5, yRow[1], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Y2"
		::SetWindowPos(_stcArray[8]->GetHandle(), HWND_TOP, xCol6, yRow[1], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Y3"
		::SetWindowPos(_stcArray[9]->GetHandle(), HWND_TOP, xCol4, yRow[6], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Time Const"
		::SetWindowPos(_stcArray[10]->GetHandle(), HWND_TOP, xCol4, yRow[7], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Point Count"
		::SetWindowPos(_stcArray[11]->GetHandle(), HWND_TOP, xCol4, yRow[8], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Interval"
		::SetWindowPos(_stcArray[12]->GetHandle(), HWND_TOP, xCol1, yRow[9], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Output file"
		::SetWindowPos(_stcArray[13]->GetHandle(), HWND_TOP, xCol1, yRow[11], dxStatic, dyStatic, SWP_SHOWWINDOW);	//"Output"

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

		::SetWindowPos(_edtArray[18]->GetHandle(), HWND_TOP, xCol1, yRow[10], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_edtArray[19]->GetHandle(), HWND_TOP, xCol1, yRow[11], dxEdit, dyEdit, SWP_SHOWWINDOW);

		::SetWindowPos(_btnArray[0]->GetHandle(), HWND_TOP, xCol4, yRow[2], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[1]->GetHandle(), HWND_TOP, xCol4, yRow[3], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[2]->GetHandle(), HWND_TOP, xCol4, yRow[4], dxEdit, dyEdit, SWP_SHOWWINDOW);

		::SetWindowPos(_btnArray[3]->GetHandle(), HWND_TOP, xCol5, yRow[2], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[4]->GetHandle(), HWND_TOP, xCol5, yRow[3], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[5]->GetHandle(), HWND_TOP, xCol5, yRow[4], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[6]->GetHandle(), HWND_TOP, xCol5, yRow[5], dxEdit, dyEdit, SWP_SHOWWINDOW);

		::SetWindowPos(_btnArray[7]->GetHandle(), HWND_TOP, xCol6, yRow[2], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[8]->GetHandle(), HWND_TOP, xCol6, yRow[3], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[9]->GetHandle(), HWND_TOP, xCol6, yRow[4], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[10]->GetHandle(), HWND_TOP, xCol6, yRow[5], dxEdit, dyEdit, SWP_SHOWWINDOW);

		::SetWindowPos(_btnArray[11]->GetHandle(), HWND_TOP, xCol4, yRow[9], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[12]->GetHandle(), HWND_TOP, xCol5, yRow[9], dxEdit, dyEdit, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[13]->GetHandle(), HWND_TOP, xCol6, yRow[9], dxEdit, dyEdit, SWP_SHOWWINDOW);

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
//		::SendMessage(_btnArray[3]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Run");
	};

	void ExpWndController::visibleStop()
	{
//		::SendMessage(_btnArray[3]->GetHandle(), WM_SETTEXT, 0, (LPARAM)"Stop");
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
