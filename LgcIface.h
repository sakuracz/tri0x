#ifndef LOGICINTERFACE_H_
#define LOGICINTERFACE_H_

#include <Windows.h>
#include <string>

namespace Logic
{
	class LogicIface
	{
	public:
		LogicIface();
		LogicIface(int*);
		~LogicIface();
		void InitMono();
		int GetSlitPos(int);
		double GetPos();
		int GetTurret();
		void queryData(double*);
		void Goto(double);
		void SetTurret(int);
		void SetSlit(int, int);
		void paramSet(int, int, int);
		bool isMotorMoving();
		bool isTurretBusy();
	private:
		void SetHandle(HANDLE dev){ _dev = dev; }

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