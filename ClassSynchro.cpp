#include "ClassSynchro.h"
#include <sstream>
#include "libWin\WinClassMaker.h"
#include "libWin\WinMaker.h"

Synchronizer::Synchronizer( Win::ExpWndController& exp)
	: _exp(exp)
{
	_Disp = NULL;
	_dataCh1 = NULL;
	_dataCh2 = NULL;
	_dataX1 = NULL;

	running = false;
	_program = 0;
	point = 0;

	funcTab[0] = &Synchronizer::Idle;
	funcTab[1] = &Synchronizer::SetLineParams;
	funcTab[2] = &Synchronizer::MoveMono;
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

bool Synchronizer::InitDev(int* params)
{
	_iface = new Logic::LogicIface(params);
	_iface->InitMono();

	double posEV = _iface->GetPos();
	double posNM = 1238.0 / posEV;
	int frontSlit = _iface->GetSlitPos(0);
	int exitSlit = _iface->GetSlitPos(2);

	stringstream text;
	text << frontSlit;
	_exp.setEditVal(0, text.str());
	_exp.setEditVal(1, "0");

	text = stringstream();
	text << exitSlit;
	_exp.setEditVal(2, text.str());
	_exp.setEditVal(3, "0");

	text = stringstream();
	text << posEV;
	_exp.setEditVal(4, text.str());
	_exp.setEditVal(5, "0.000");

	_exp.setEditVal(6, "0");
	_exp.setEditVal(7, "0.000");

	_exp.setEditVal(8, "0");
	_exp.setEditVal(9, "0.000");

	text = stringstream();
	text << posNM;
	_exp.setEditVal(10, text.str());
	_exp.setEditVal(11, "0.00");

	_exp.setEditVal(12, "not used");
	_exp.setEditVal(13, "0.3");

	_exp.setEditVal(14, "not used");
	_exp.setEditVal(15, "1");

	_exp.setEditVal(16, "not used");
	_exp.setEditVal(17, "0.1");



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

void Synchronizer::SetLineParams()		// func tab[1]
{
//	int params[3];
//	_line.ReturnSet(params);

//	_lineIface.SetHSpeed(params[0]);
//	_lineIface.SetLSpeed(params[1]);
//	_lineIface.SetAccel(params[2]);

//	_line.UpdateSet(params[0], params[1], params[2]);

//	_line.ResetProg();
	_program = 0;
	return;
};

void Synchronizer::MoveMono()	//func tab[2]
{
//	_line.ResetProg();
	
//	int param;

//	_line.ReturnPos(&param);

//	if(_Disp)
//		delete _Disp;

//	_lineIface.GoTo(param);
//	_Disp = new Dispatcher(0, this, &Synchronizer::CheckMovement);
	_program = 0;

	return;
};

void Synchronizer::Measure()	//func tab[3]
{
	if(point == 0){
//		_lineIface.GoTo(start);
		int pCount = (stop - start)/inc+1;
		if(_dataCh1 == NULL) {
			_dataCh1 = new double[pCount];
			_dataCh2 = new double[pCount];
			_dataX1 = new double[pCount];
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
			_dataCh1[point-1] = (start + inc*point)*1.0;
//			_dataY[point-1] = _lockIface.GetMeasuredValues();
//			::MessageBox(NULL, "Przed", "MB", MB_OK);
			_outCtrl->UpdateData(_dataCh1, _dataCh2, point);
//			::MessageBox(NULL, "Po", "MB", MB_OK);
		}
		point++;
//		_lockIface.StartAcquisition();
		time = ::GetTickCount();
//		::MessageBox(NULL, "Working", "Step3", MB_OK);
		return;
	}
};

void Synchronizer::StopExp()	//func tab[4]
{
	_exp.visibleRun();

	toggleRunning();

	point = 0;
	time = ::GetTickCount();

	_dataCh1 = NULL;
	_dataCh2 = NULL;
	_dataX1 = NULL;

	_program = 0;
	return;
};

void Synchronizer::CheckMovement()			// func tab[5]
{
	//	::MessageBoxA(NULL, "Mov", "Check", MB_OK);

	//	while(_lineIface.isMoving()){Sleep(500);_line.UpdatePos(_lineIface.GetPos());}
	//	_line.UpdatePos(_lineIface.GetPos());
	//	_lineIface.Stop();

	return;
};

void Synchronizer::GoHome()				// func tab[6]
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

void Synchronizer::SetLockParams()		// func tab[7]
{
	int params[4];
	_exp.ReturnSet(params);

	//	_lockIface.SetLockInterfaceParams(params[0], params[1], params[2], params[3]);
	::GetTickCount();
	//	_exp.ResetProg();
	_program = 0;
	return;
};

void Synchronizer::SetOutputWindow(Win::ImgWndController* ctrl)
{
	_outCtrl = ctrl;
};

void Synchronizer::StartExp()			// func tab[8]
{
//	_exp.startExp();

	toggleRunning();
	_exp.visibleStop();
	updateSettings();	

	_program = 3;
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

void Synchronizer::ShutdownDev()
{
	_iface->Close();

	return;
}