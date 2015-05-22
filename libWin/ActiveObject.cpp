#include "ActiveObject.h"

ActiveObject::ActiveObject()
	: _isDying(0), 
#pragma warning(disable: 4355) //'this' used before initialized
	_thread(ThreadEntry, this)
#pragma warning(default: 4355)
{
}

void ActiveObject::Kill()
{
	_isDying++;
	FlushThread();
	_thread.WaitForDeath();
}

DWORD WINAPI ActiveObject::ThreadEntry(void* pArg)
{
	ActiveObject * pActive = (ActiveObject *) pArg;
	pActive->InitThread();
	pActive->Loop();
	return 0;
}