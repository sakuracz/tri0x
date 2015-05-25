#include "ClassDispatcher.h"

Dispatcher::Dispatcher(DWORD targetTime, Synchronizer* obj, void (Synchronizer::* funcPtr)())
{
	_nTarget = targetTime;
	mObj = obj;
	mFuncPtr = funcPtr;

	_thread.Resume();
};

Dispatcher::~Dispatcher()
{
	Kill();
};

void Dispatcher::Loop()
{
	while(GetTickCount() < _nTarget){};
	(mObj->*mFuncPtr)();
};