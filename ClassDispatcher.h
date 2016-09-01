//this class dispatches threads for activity that can take some time - like delay line movements

#ifndef CLASSDISPATCHER_H_
#define CLASSDISPATCHER_H_

#include "libWin/ActiveObject.h"

class Synchronizer;

class Dispatcher : public ActiveObject
{
public:
	Dispatcher(DWORD, Synchronizer*, void (Synchronizer::*)());
	~Dispatcher();
	void InitThread(){};
	void Loop();
	void FlushThread(){};
private:
	DWORD _nTarget;
	Synchronizer* mObj;
	void (Synchronizer::* mFuncPtr)();
};

#endif
