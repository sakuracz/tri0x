#ifndef THREAD_H_
#define THREAD_H_

#include <windows.h>
#include <process.h>

class Thread
{
public:
	Thread(DWORD (WINAPI * pFun) (void *pArg), void *pArg)
	{
		_handle = ::CreateThread(0, 0, pFun, pArg, CREATE_SUSPENDED, &_tid); 
	}

	~Thread(){ ::CloseHandle(_handle); }
	void Resume() { ::ResumeThread(_handle); }
	void WaitForDeath() { ::WaitForSingleObject(_handle, 2000); }

private:
	HANDLE _handle;
	DWORD _tid;
};

class Mutex
{
	friend class Lock;

public:
	Mutex() { InitializeCriticalSection(&_critSection); }
	~Mutex() { DeleteCriticalSection(&_critSection); }

private:
	void Aquire() 
	{
		EnterCriticalSection(&_critSection);
	}

	void Release()
	{
		LeaveCriticalSection(&_critSection);
	}

	CRITICAL_SECTION _critSection;
};

class Lock
{
public:
	Lock ( Mutex& mutex)
		: _mutex(mutex)
	{
		_mutex.Aquire();
	}

	~Lock()
	{
		_mutex.Release();
	}

private:
	Mutex& _mutex;
};

class Event
{
public:
	Event()
	{
		_handle = CreateEvent(0, TRUE, FALSE, 0);
	}

	~Event()
	{
		CloseHandle(_handle);
	}

	//put into signaled state:
	void GreenLight() { SetEvent(_handle); }
	//put into non-signaled state:
	void RedLight() { ResetEvent(_handle); } 
	void Wait()
	{
		WaitForSingleObject(_handle, INFINITE);
	}

private:
	HANDLE _handle;
};

class AtomicCounter
{
public:
	AtomicCounter() : _counter(0) {}

	long Inc()
	{
		//return the sign (or zero) of the new value
		return InterlockedIncrement(&_counter);
	}

	long Dec()
	{
		return InterlockedDecrement(&_counter);
	}

	BOOL IsNonZeroReset()
	{
		return InterlockedExchange(&_counter, 0) != 0;
	}

private:
	long _counter;
};

#endif
