#ifndef ACTIVEOBJECT_H_
#define ACTIVEOBJECT_H_

#include <process.h>
#include <windows.h>
#include "Thread.h"

class ActiveObject
{
public:
	ActiveObject();
	virtual ~ActiveObject(){}
	void Kill();

protected:
	virtual void InitThread() = 0;
	virtual void Loop() = 0;
	virtual void FlushThread() = 0;

	int _isDying;

	static DWORD WINAPI ThreadEntry(void *pArg);
	Thread _thread;

};

#endif
