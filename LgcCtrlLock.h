#ifndef LGCCTRLLOCK_H_
#define LGCCTRLLOCK_H_

#include <Windows.h>
#include <memory>
#include <vector>
#include <complex>

namespace Logic
{
	class LockInterface
	{
	public:		
		LockInterface();
		~LockInterface();
		
	private:
		void Init();
		void Close();
		void GetVals(){}
		void SetParams(){}
		int GetDataCount();

	public:
		void SetLockInterfaceParams(int,int,int,int);
		double GetMeasuredValues();
		int* GetLockInterfaceParams(){}
		void StartAcquisition();
		void StopAcquisition();
		void ResetLock();

	private:
		HANDLE		_dev;
		DCB			_dcb;
		COMMTIMEOUTS _comm;
	};
};

#endif