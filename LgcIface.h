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
		void Close();
	private:			
		void Goto(double);
		void SetTurret(int);
		void SetSlit(int, int);
		void SetHandle(HANDLE dev){ _dev = dev; }
		double GetSlit();
		double GetPos();
		double GetTurret();
		void queryData(void);

		HANDLE		_dev;
		DCB			_dcb;
		COMMTIMEOUTS _comm;

		std::string _resetStr, _whereStr, _boot2MainStr, _initStr, _dataQuery;
		std::string _mirSideStr, _mirRearStr, _mirCheckStr, _motorBusyStr, _motorReadStr;
		std::string _motorSpeedStr, _motorStopStr, _turStatusStr, _turPosStr, _absPosStr;

		double _gratingFactors[3];

		bool _force;
		int _turret;
		int _mirror;
	private:
		bool checkBusy(char);
		bool checkStatus(char);
		void Init();
	};

}

#endif 