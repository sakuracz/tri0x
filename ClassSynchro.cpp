#include "ClassSynchro.h"
#include <sstream>
#include "libWin\WinClassMaker.h"
#include "libWin\WinMaker.h"

Synchronizer::Synchronizer( Win::ExpWndController& exp)
	: _exp(exp)
{
	_Disp = NULL;
	_dataX = NULL;
	_dataY = NULL;

	running = false;
	_program = 0;
	point = 0;

	funcTab[0] = &Synchronizer::Idle;
	funcTab[1] = &Synchronizer::SetLineParams;
	funcTab[2] = &Synchronizer::MoveLine;
	funcTab[3] = &Synchronizer::Measure;
	funcTab[4] = &Synchronizer::StopExp;
	funcTab[5] = &Synchronizer::CheckMovement;
	funcTab[6] = &Synchronizer::GoHome;
	funcTab[7] = &Synchronizer::SetLockParams;
	funcTab[8] = &Synchronizer::StartExp;

	if(!CreateOpenKey())
		::MessageBox(NULL, "Failed to create or open registry entry", "Error", MB_ICONERROR | MB_OK);

	_thread.Resume();
};

Synchronizer::~Synchronizer()
{
	Kill();
};

bool Synchronizer::CreateOpenKey()
{

	DWORD disp, lRv;

	lRv = ::RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\KCorp", NULL, KEY_WRITE, &_regKey);
	if(lRv != ERROR_SUCCESS)
	{

		lRv = ::RegCreateKeyEx(HKEY_CURRENT_USER, 
								"Software\\KCorp", 
								NULL, 
								NULL,
								REG_OPTION_NON_VOLATILE,
								KEY_ALL_ACCESS,
								NULL, 
								&_regKey, 
								&disp);

		if((disp == REG_CREATED_NEW_KEY) || (disp == REG_OPENED_EXISTING_KEY))
			return true;

		return false;
	} else {
		return true;
	}
};

bool Synchronizer::InitDevLine(unsigned int dev)
{
	_selectedDevice = dev;
//	if(!_lineIface.Init(dev))
//		return false;

//	_line.UpdateSet(_lineIface.GetHSpeed(), _lineIface.GetLSpeed(), _lineIface.GetAccel());

//	_lineIface.InitHome();

//	_line.UpdatePos(_lineIface.GetPos());

	return true;
};

void Synchronizer::Loop(void)
{
	while(1){
		(this->*funcTab[_program])();
	};
	return;
};

void Synchronizer::Idle()		//funct tab[0]
{
//	_program = _line.GetProg();
//	if(_program == 0)
//		_program = _exp.GetProg();
	return;
};

void Synchronizer::SetLineParams()		//funct tab[1]
{
	int params[3];
//	_line.ReturnSet(params);

//	_lineIface.SetHSpeed(params[0]);
//	_lineIface.SetLSpeed(params[1]);
//	_lineIface.SetAccel(params[2]);

//	_line.UpdateSet(params[0], params[1], params[2]);

//	_line.ResetProg();
	_program = 0;
	return;
};

void Synchronizer::SetLockParams()
{
	int params[4];
	_exp.ReturnSet(params);

//	_lockIface.SetLockInterfaceParams(params[0], params[1], params[2], params[3]);
	::GetTickCount();
//	_exp.ResetProg();
	_program = 0;
	return;
};

void Synchronizer::MoveLine()	//funct tab[2]
{
//	_line.ResetProg();
	
	int param;

//	_line.ReturnPos(&param);

//	if(_Disp)
//		delete _Disp;

//	_lineIface.GoTo(param);
//	_Disp = new Dispatcher(0, this, &Synchronizer::CheckMovement);
	_program = 0;

	return;
};

void Synchronizer::Measure()	//funct tab[3]
{
	if(point == 0){
//		_lineIface.GoTo(start);
		int pCount = (stop - start)/inc+1;
		if(_dataX == NULL) {
			_dataX = new double[pCount];
			_dataY = new double[pCount];
		}
	};

	if((start + inc*point > stop)){		
		_program = 4;			//wersja napierdalacza
//		point = 0;
		return;
	};

	if( ::GetTickCount() - time < interval){
		return;
	} else {
		if(point != 0){
//			_lockIface.StopAcquisition();
//			_lineIface.GoTo(_lineIface.GetPos() + inc);
//			_line.UpdatePos(_lineIface.GetPos());
			_dataX[point-1] = (start + inc*point)*1.0;
//			_dataY[point-1] = _lockIface.GetMeasuredValues();
//			::MessageBox(NULL, "Przed", "MB", MB_OK);
			_outCtrl->UpdateData(_dataX, _dataY, point);
//			::MessageBox(NULL, "Po", "MB", MB_OK);
		}
		point++;
//		_lockIface.StartAcquisition();
		time = ::GetTickCount();
//		::MessageBox(NULL, "Working", "Step3", MB_OK);
		return;
	}
};

void Synchronizer::SetOutputWindow(Win::ImgWndController* ctrl)
{
	_outCtrl = ctrl;
};

void Synchronizer::StartExp()
{
//	_exp.startExp();



	toggleRunning();
	_exp.visibleStop();
	updateSettings();	

	_program = 3;
	return;
};

void Synchronizer::StopExp()	//func tab[4]
{
//	_line.ResetProg();
	
	_exp.visibleRun();

	toggleRunning();

	point = 0;
	time = ::GetTickCount();

//	_lineIface.Stop();
//	_lockIface.StopAcquisition();
	_dataX = NULL;
	_dataY = NULL;
//	_line.UpdatePos(_lineIface.GetPos());
	_program = 0;
	return;
};

void Synchronizer::CheckMovement()
{
//	::MessageBoxA(NULL, "Mov", "Check", MB_OK);

//	while(_lineIface.isMoving()){Sleep(500);_line.UpdatePos(_lineIface.GetPos());}
//	_line.UpdatePos(_lineIface.GetPos());
//	_lineIface.Stop();

	return;
};

void Synchronizer::GoHome()
{
//	_line.ResetProg();

//	_lineIface.InitHome();
//	_line.UpdatePos(_lineIface.GetPos());

//	if(_Disp)
//		delete _Disp;

//	_Disp = new Dispatcher(0, this, &Synchronizer::CheckMovement);
	_program = 0;
	return;
};

void Synchronizer::updateSettings()
{
	int params[4];
	_exp.ReturnExpParams(params);

	start = params[0];
	stop = params[1];
	inc = params[2];
	interval = params[3];
};

void Synchronizer::progLineHome()
{
	_program = 6;
	return;
};

void Synchronizer::progLineParams()
{
	_program = 1;
	return;
};

void Synchronizer::progLockParams()
{
	_program = 7;
	return;
};

void Synchronizer::progGoTo()
{
	_program = 2;
};

void Synchronizer::progStopExp()
{	
	_program = 4;
	return;
};

void Synchronizer::progMeasure()
{
	_program = 3;
	return;
};

void Synchronizer::progStartExp()
{
	_program = 8;
	return;
};

void Synchronizer::StopLineMovement()
{
	_program = 4;
	return;
};

void Synchronizer::toggleRunning()
{
	running = !running;
};