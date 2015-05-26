#ifndef LOGICINTERFACE_H_
#define LOGICINTERFACE_H_

#include <Windows.h>

namespace Logic
{
	class LogicIface
	{
	public:
		LogicIface(int*);
		~LogicIface();
	private:	
		void InitMono(bool);
		void Goto(double);
		void SetTurret(int);
		void SetSlit(int, int);
		void SetHandle(HANDLE dev){ _dev = dev; }
		void queryData(void);

		HANDLE		_dev;
		DCB			_dcb;
		COMMTIMEOUTS _comm;

	private:
		void Init();
	};

}

#endif 