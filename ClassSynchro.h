#ifndef CLASSSYNCHRO_H_
#define CLASSSYNCHRO_H_

#include "libWin/ActiveObject.h"
#include "libWin/Window.h"
#include "LgcIface.h"
#include "ClassDispatcher.h"
#include "WndCtrlExp.h"
#include "WndCtrlMonoSetup.h"
//#include "WndCtrlImg.h"
#include <memory>

class Synchronizer : public ActiveObject
{
public:	
	Synchronizer(Win::ExpWndController&, Win::MonoWndCtrl&);
	~Synchronizer();
	void Update(void){ ; }
	typedef void (Synchronizer::*funcPtr)();	
	void SetSlitWithUpdate(int);
	void GoToAndUpdate(double);
	double GetTargetNM();
	double GetTargetEV();
	void ShutdownDev();

	void UpdateSettings();
	bool isRunning(){ return running; }
//	void SetOutputWindow(Win::ImgWndController*);
	//program switching functions:
	void progIdle(){ _program = 0; }
	void progSetLineParams(){ _program = 1; }
	void progMoveMono(){ _program = 2; }
	void progMeasure(){ _program = 3; }
	void progStopExp(){ _program = 4; }
	void progCheckMovement(){ _program = 5; }
	void progGoHome() { _program = 6; }		
	void progStartExp(){ _program = 7; }		
	void progInitDevs(){ _program = 8; }
	

private:
	HKEY _regKey;
	HANDLE _hDevLine;
	Win::ExpWndController& _exp;
	Win::MonoWndCtrl& _mono;
	Logic::LogicIface _iface;
	void Loop(void);
	void InitThread(){};
	void FlushThread(){};

	vector<funcPtr> funcTab;

	//functions from the function tab:
	unsigned int _program;
	void Idle();			//function to probe for changes made by the user in the interface
	void SetLineParams();	//two functions to set parameters of both devices:
	void MoveMono();
	void Measure();
	void StartExp();
	void StopExp();
	void CheckMovement();
	void GoHome();
	void InitDev();

	void PerSecUpdate();
	bool CreateOpenKey();

private:					// experiment control variables:
	void ToggleRunning();
	bool running;
	DWORD time;				// timestamp

	int point;				// point counter
	unsigned int numPoints;			// points per average
	double start;			// starting position
	double stop;			// end position
	double inc;				// increment position
	unsigned int interval;	// time interval between measurements in [ms]
	unsigned int waitTime;	// lock-in time constant
	//	std::unique_ptr<std::vector<std::complex<double> > > vData;

private:					// output windows and helper functions
//	Win::ImgWndController	*_outCtrl;

private:		//data vector
	typedef vector<vector<double>> vvect;
	vvect data;
//public:
//	double *_dataX;
//	double *_dataCh1;
//	double *_dataCh2;
//	double *_dataX1;
};

#endif
