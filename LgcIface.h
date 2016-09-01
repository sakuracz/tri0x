#ifndef LOGICINTERFACE_H_
#define LOGICINTERFACE_H_

#include <Windows.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace Logic
{
	class LogicIface
	{
	public:		
		LogicIface();
		LogicIface(int*);
		~LogicIface();
		void InitMono();
		int GetSlitPos(int);	//return slit width [um], input which slit
		double GetPos();		//return wavelength position (uses turret position)
		int GetTurret();		//return turret position
		void queryData(vector<double> &);
		void Goto(double);
		void SetTurret(int);
		void SetSlit(int, int);
		void paramSet(int, int, int);
		bool isMotorMoving();
		bool isTurretBusy();
	private:
		void SetHandle(HANDLE dev){ _dev = dev; }

		HANDLE		_dev = nullptr;
		DCB			_dcb;
		COMMTIMEOUTS _comm;

		string _resetStr, _whereStr, _boot2MainStr, _initStr, _dataQuery;
		string _mirSideStr, _mirRearStr, _mirCheckStr, _motorBusyStr, _motorReadStr;
		string _motorSpeedStr, _motorStopStr, _turStatusStr, _turPosStr, _absPosStr;

		double _gratingFactors[3];

		bool _force = false;
		int _turret = 0;
		int _mirror = 0;
	private:
		bool checkBusy(char);
		bool checkStatus(char);
		void Init();
	};

}

#endif 