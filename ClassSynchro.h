#ifndef CLASSSYNCHRO_H_
#define CLASSSYNCHRO_H_

#include "libWin\ActiveObject.h"
#include "libWin\Window.h"

#include "ClassDispatcher.h"
#include "WndCtrlExp.h"
#include "WndCtrlImg.h"

class Synchronizer : public ActiveObject
{
public:
	Synchronizer(Win::ExpWndController&);
	~Synchronizer();
	void Update(void){;}
	typedef void (Synchronizer::*funcPtr)();
	bool InitDevLine(unsigned int);
	void StopLineMovement();
	void updateSettings();
	bool isRunning(){return running;}
	void SetOutputWindow(Win::ImgWndController*);
	void progLineHome();
	void progLineParams();
	void progLockParams();
	void progGoTo();
	void progMeasure();
	void progStartExp();
	void progStopExp();

private:
	HKEY _regKey;
	HANDLE _hDevLine;
	Dispatcher *_Disp;
	unsigned int _selectedDevice;	
	Win::ExpWndController& _exp;
//	Logic::LineInterface _lineIface;
//	Logic::LockInterface _lockIface;
	void Loop(void);
	void InitThread(){};
	void FlushThread(){};

	funcPtr funcTab[9];

	//functions from the function tab:
	unsigned int _program;
	void Idle();			//function to probe for changes made by the user in the interface
	void SetLineParams();	//two functions to set parameters of both devices:
	void SetLockParams();
	void MoveLine();
	void Measure();
	void StartExp();
	void StopExp();	
	void CheckMovement();
	void GoHome();


	bool CreateOpenKey();

private:					// experiment control variables:
	void toggleRunning();
	bool running;
	DWORD time;				// timestamp
	int point;				// point counter
	int start;				// starting position
	int stop;				// end position
	int inc;				// increment position
	unsigned int interval;	// time interval between measurements in [ms]
//	std::unique_ptr<std::vector<std::complex<double> > > vData;

private:					// output windows and helper functions
	Win::ImgWndController	*_outCtrl;
public:
	double *_dataX;
	double *_dataY;
};

#endif