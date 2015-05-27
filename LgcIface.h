#ifndef LOGICINTERFACE_H_
#define LOGICINTERFACE_H_

#include <Windows.h>
#include <string>

namespace Logic
{
	class LogicIface
	{
	public:
		LogicIface(int*);
		~LogicIface();
		void InitMono();
	private:			
		void Goto(double);
		void SetTurret(int);
		void SetSlit(int, int);
		void SetHandle(HANDLE dev){ _dev = dev; }
		void queryData(void);

		HANDLE		_dev;
		DCB			_dcb;
		COMMTIMEOUTS _comm;

		std::string _resetStr, _whereStr, _boot2MainStr, _initStr, _dataQuery;

		bool _force;
		int _turret;
		int _mirror;
	private:
		void Init();
	};

}

#endif 