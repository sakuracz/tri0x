#include "ClassSynchro.h"
#include <sstream>
#include "libWin\WinClassMaker.h"
#include "libWin\WinMaker.h"

Synchronizer::Synchronizer(Win::ExpWndController& exp)
	: _exp(exp), _iface()
{
	_Disp = NULL;
	_dataX = NULL;
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

void Synchronizer::SetSlitWithUpdate(int slit)
{
	int frontSlit = _exp.GetEditVal(1);
	int rearSlit = _exp.GetEditVal(3);
	//	stringstream str;
	//	str << frontSlit << "\t" << rearSlit;
	//	::MessageBoxA(NULL, str.str().c_str(), "Set slit with update", MB_OK);
	int outVal = 0;
	if (frontSlit > 2300)
		frontSlit = 2300;
	else if (frontSlit < 0)
		frontSlit = 0;
	if (rearSlit > 2300)
		rearSlit = 2300;
	else if (frontSlit < 0)
		rearSlit = 0;
	stringstream pos;
	switch (slit){
	case 0:
		_iface.SetSlit(slit, frontSlit);
		while (_iface.isMotorMoving()){
			outVal = _iface.GetSlitPos(0);
			pos << outVal;
			_exp.setEditVal(0, pos.str());
			pos = stringstream();
		};
		outVal = _iface.GetSlitPos(0);
		pos << outVal;
		_exp.setEditVal(0, pos.str());
		break;
	case 1:
		break;
	case 2:
		_iface.SetSlit(slit, rearSlit);
		while (_iface.isMotorMoving()){
			outVal = _iface.GetSlitPos(2);
			pos << outVal;
			_exp.setEditVal(2, pos.str());
			pos = stringstream();
		};
		outVal = _iface.GetSlitPos(2);
		pos << outVal;
		_exp.setEditVal(2, pos.str());
		break;

	case 3:
		break;
	}

};

void Synchronizer::GoToAndUpdate(double wavelength)
{
	_iface.Goto(wavelength);
	double current = _iface.GetPos();
	stringstream text;
	text << current;
	_exp.setEditVal(10, text.str());
	text = stringstream();
	text << 1239.8384 / current;
	_exp.setEditVal(4, text.str());
}

double Synchronizer::GetTargetEV()
{
	return _exp.GetEditVal(5);
}

double Synchronizer::GetTargetNM()
{
	return _exp.GetEditVal(11);
}

bool Synchronizer::InitDev(int* params)
{
	_iface.paramSet(params[0], params[1], params[2]);

		stringstream initParam;
		initParam << params[0] << "\t" << params[1] << "\t" << params[2];

		::MessageBox(NULL, initParam.str().c_str(), "Init parameters", MB_OK);

	_iface.InitMono();
	GoToAndUpdate(1000);


	double posNM = _iface.GetPos();
	double posEV = 1239.8384 / posNM;
	int frontSlit = _iface.GetSlitPos(0);
	int exitSlit = _iface.GetSlitPos(2);

	//	stringstream vals;
	//	vals << posEV << "\t" << frontSlit << "\t" << exitSlit;
	//	::MessageBoxA(NULL, vals.str().c_str(), "Position and slits read from mono", MB_OK);

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
};

void Synchronizer::Idle()		//funct tab[0]
{
	//	_program = _line.GetProg();
	//	if(_program == 0)
	//		_program = _exp.GetProg();	
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
};

void Synchronizer::Measure()	//func tab[3]
{
	if(point == 0){
		_iface.Goto(1239.8384/start);
		if (inc != 0){
			//			::MessageBox(NULL, "KL", "op", MB_OK);
			int pCount = (start - stop) / inc + 1;
			if ((_dataCh1 == NULL) && (pCount != 0)) {
				_dataX = new double[pCount];
				_dataCh1 = new double[pCount];
				_dataCh2 = new double[pCount];
				_dataX1 = new double[pCount];
			}
		}
	};

	if((start - inc*point < stop)){
		_program = 4;
		return;
	};

	if(::GetTickCount() - time < waitTime){
		return;
	} else {
		if(point != 0){
			double data[3];
			double average[4] = { 0.0, 0.0, 0.0, 0.0 };
			for (unsigned int i = 0; i < numPoints; i++){
				_iface.queryData(data);
				::Sleep(interval);
				average[1] += data[0] / (i*1.0);
				average[2] += data[1] / (i*1.0);
				average[3] += data[2] / (i*1.0);
			}

			_dataX[point-1] = start + inc*point;
			_dataCh1[point - 1] = average[0];
			_dataCh2[point - 1] = average[1];
			_dataX1[point - 1] = average[2];

			double nextPos = 1239.8384 / (1239.8384 / _iface.GetPos() - inc);
			_iface.Goto(nextPos);
			_exp.UpdatePos(_iface.GetPos());
			_exp.UpdateEditBox(average, 4);
			//			_dataY[point-1] = _lockIface.GetMeasuredValues();
			//			::MessageBox(NULL, "Przed", "MB", MB_OK);
			//			_outCtrl->UpdateData(_dataX, _dataCh1, point);
			//			::MessageBox(NULL, "Po", "MB", MB_OK);
		}
		point++;
		//		_lockIface.StartAcquisition();
		time = ::GetTickCount();
		//		::MessageBox(NULL, "Working", "Step3", MB_OK);		
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
};

void Synchronizer::CheckMovement()			// func tab[5]
{
};

void Synchronizer::GoHome()				// func tab[6]
{
	_program = 0;
};

/*void Synchronizer::SetOutputWindow(Win::ImgWndController* ctrl)
{
	_outCtrl = ctrl;
};*/

void Synchronizer::StartExp()			// func tab[8]
{
	toggleRunning();
	_exp.visibleStop();
	updateSettings();

	_program = 3;
};

void Synchronizer::updateSettings()
{
	double params[6];
	_exp.ReturnExpParams(params);

	start = params[0];
	stop = params[1];
	inc = params[2];
	waitTime = (unsigned int)params[3];			// wait time in [ms]
	numPoints = (unsigned int)params[4];
	interval = (unsigned int)params[5];			// interval in [ms]
};

void Synchronizer::progLineHome()
{
	_program = 6;
};

void Synchronizer::progLineParams()
{
	_program = 1;

};

void Synchronizer::progLockParams()
{
	_program = 7;
};

void Synchronizer::progGoTo()
{
	_program = 2;
};

void Synchronizer::progStopExp()
{
	_program = 4;
};

void Synchronizer::progMeasure()
{
	_program = 3;
};

void Synchronizer::progStartExp()
{
	_program = 8;
};

void Synchronizer::StopLineMovement()
{
	_program = 4;
};

void Synchronizer::toggleRunning()
{
	running = !running;
};

void Synchronizer::ShutdownDev()
{	
}