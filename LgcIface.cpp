#include "LgcIface.h"
#include <sstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

#define NOMONO_			//NOMONO - no triax; NOMONO_ - use triax
#define NOHOMO_			//NOHOMO - no lock-in; NOHOMO_ - use lock-in

namespace Logic
{
	LogicIface::LogicIface(int* params)
	{
		_gratingFactors[0] = 4.0;
		_gratingFactors[1] = 16.0;
		_gratingFactors[2] = 2.0;

		if (params[2])
			_force = true;
		else
			_force = false;

		_turret = params[0];
		_mirror = params[1];

		_dev = NULL;

		_comm.ReadIntervalTimeout = 5;
		_comm.ReadTotalTimeoutConstant = 100;
		_comm.ReadTotalTimeoutMultiplier = 100;
		_comm.WriteTotalTimeoutConstant = 10;

		_dcb.DCBlength = sizeof(_dcb);
		_dcb.BaudRate = CBR_115200;
		_dcb.ByteSize = 8;
		_dcb.StopBits = ONESTOPBIT;
		_dcb.Parity = NOPARITY;
		_dcb.fBinary = TRUE;
		_dcb.fOutxCtsFlow = FALSE;
		_dcb.fOutxDsrFlow = FALSE;
		_dcb.fDtrControl = DTR_CONTROL_ENABLE;
		_dcb.fRtsControl = RTS_CONTROL_ENABLE;
		_dcb.fDsrSensitivity = FALSE;
		_dcb.fOutX = FALSE;
		_dcb.fInX = FALSE;
		_dcb.fParity = FALSE;
		_dcb.fNull = TRUE;

		//Commonly used strings:
		stringstream stream;
		stream << "/1" << (char)222;
		_resetStr = stream.str();
		stream = stringstream();
		stream << "/1 ";
		_whereStr = stream.str();
		stream = stringstream();
		stream << "/1O2000" << (char)0x0D;
		_boot2MainStr = stream.str();
		stream = stringstream();
		stream << "/1A";
		_initStr = stream.str();
		stream = stringstream();
		stream << "/2q1" << 0x0d << "q2" << 0x0d << "x1" << 0x0d;
		_dataQuery = stream.str();
		stream = stringstream();
		stream << "/1f0" << (char)0x0D;
		_mirRearStr = stream.str();
		stream = stringstream();
		stream << "/1e0" << (char)0x0D;
		_mirSideStr = stream.str();
		stream = stringstream();
		stream << "/1l";
		_mirCheckStr = stream.str();
		stream = stringstream();
		stream << "/1H0" << (char)0x0D;
		_motorReadStr = stream.str();
		stream = stringstream();
		stream << "/1E";
		_motorBusyStr = stream.str();
		stream = stringstream();
		stream << "/1C0" << (char)0x0D;
		_motorSpeedStr = stream.str();
		stream = stringstream();
		stream << "/1L";
		_motorStopStr = stream.str();
		stream = stringstream();
		stream << "/1Z452,0,0,0" << (char)0x0D;
		_turPosStr = stream.str();
		stream = stringstream();
		stream << "/1Z453,0,0,0" << (char)0x0D;
		_turStatusStr = stream.str();
		stream = stringstream();
		stream << "/1Z62,0" << (char)0x0D;
		_absPosStr = stream.str();
		// end of common string

#ifndef NOMONO
		Init();
#endif
	};

	LogicIface::~LogicIface()
	{
		if (_dev)
			CloseHandle(_dev);
		_dev = nullptr;
	};

	void LogicIface::Init()
	{
		_dev = ::CreateFile("COM1", GENERIC_READ | GENERIC_WRITE,
			0, 0,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (_dev == INVALID_HANDLE_VALUE){
			if (GetLastError() == ERROR_FILE_NOT_FOUND){
				//do some error output "No port" or something...				
				MessageBox(NULL, "Could not open port COM1", "Error", MB_OK);
				PostQuitMessage(0);
			}
			else {
				char msg[255];
				sprintf_s(msg, "Failed open port COM1. Error #%d", GetLastError(), MB_OK);
				MessageBox(NULL, msg, "Error", MB_OK);
				PostQuitMessage(0);
			}
		}

		if (!SetCommState(_dev, &_dcb)){
			MessageBox(NULL, "Failed to set proper comm state", "Error", MB_OK);
			PostQuitMessage(0);
		}
		else {

		}
		if (!SetCommTimeouts(_dev, &_comm)){
			MessageBox(NULL, "Failed to set comm timeouts", "Error", MB_OK);
		};

		return;
	};

	void LogicIface::InitMono()
	{
#ifdef NOMONO
		return;
#endif

		std::stringstream sstream;
		DWORD dwBytesWritten, dwBytesRead;
		char readBuffer[255];
		//reset string send

		WriteFile(_dev, _resetStr.c_str(), _resetStr.length(), &dwBytesWritten, NULL);
		ReadFile(_dev, readBuffer, 1, &dwBytesRead, NULL);

		Sleep(500);

		dwBytesRead = 0;
		while (dwBytesRead == 0){
			WriteFile(_dev, _whereStr.c_str(), _whereStr.length(), &dwBytesWritten, NULL);
			ReadFile(_dev, readBuffer, 1, &dwBytesRead, NULL);
		}
		while ((readBuffer[0] != 'B') && (readBuffer[0] != 'F')){
			WriteFile(_dev, _whereStr.c_str(), _whereStr.length(), &dwBytesWritten, NULL);
			ReadFile(_dev, readBuffer, 1, &dwBytesRead, NULL);
		}

		if (readBuffer[0] == 'B')	//if so then hung;
		{
			WriteFile(_dev, _boot2MainStr.c_str(), _boot2MainStr.length(), &dwBytesWritten, NULL);
			Sleep(500);
		}

		ZeroMemory(readBuffer, 255);
		while (readBuffer[0] != 'F'){
			WriteFile(_dev, _whereStr.c_str(), _whereStr.length(), &dwBytesWritten, NULL);
			ReadFile(_dev, readBuffer, 1, &dwBytesRead, NULL);
		}

		if ((readBuffer[0] == 'F') || (readBuffer[0] == '*'))
		{
			if (_force){
				WriteFile(_dev, _initStr.c_str(), _initStr.length(), &dwBytesWritten, NULL);
				for (int i = 0; i < 100; i++)
					Sleep(1000);
				return;
			}

			if (GetTurret() != _turret)
			{
				sstream = stringstream();
				sstream << "/1Z451,0,0,0," << _turret << (char)0x0D;
				ZeroMemory(readBuffer, 255);
				while (readBuffer[0] != 'o'){
					WriteFile(_dev, sstream.str().c_str(), sstream.str().length(), &dwBytesWritten, NULL);
					ReadFile(_dev, readBuffer, 1, &dwBytesRead, NULL);
				}
				while (isTurretBusy()){
					Sleep(500);
				}
			}

			return;

		}
		else
		{
			sstream << (char)248;
			WriteFile(_dev, sstream.str().c_str(), 1, &dwBytesWritten, NULL);
			sstream << (char)222;
			WriteFile(_dev, sstream.str().c_str(), 1, &dwBytesWritten, NULL);
			WriteFile(_dev, "/1A", 3, &dwBytesWritten, NULL);
		}

		return;
	};

	void LogicIface::queryData(double* outArr)
	{
#ifndef NOMONO
		DWORD dwBytesWritten, dwBytesRead;
		char readBuff[255];
		std::stringstream inpStream;

		WriteFile(_dev, _dataQuery.c_str(), _dataQuery.length(), &dwBytesWritten, NULL);
		ReadFile(_dev, readBuff, 255, &dwBytesRead, NULL);
		inpStream << readBuff;
		inpStream >> outArr[0] >> outArr[1] >> outArr[2];
#else
		outArr[0] = rand()/(RAND_MAX*1.0);
		outArr[1] = rand()/(RAND_MAX*1.0);
		outArr[2] = rand()/(RAND_MAX*1.0);
#endif

		return;
	};

	void LogicIface::Goto(double target)		// target in nm
	{
#ifdef NOMONO
		return;
#endif
		DWORD dwBytesWritten, dwBytesRead;
		char readBuffer[255];
		char readBuff = 0;
		ZeroMemory(readBuffer, 255);
		double val = target / _gratingFactors[_turret];

		//TODO: check motor moving and position		
		double currentVal = GetPos() / _gratingFactors[_turret];		//GetPos() return absolute values in nm (that's why it's being divided);

		stringstream msgStream, dVal;
		dVal.precision(3);
		dVal << fixed << val;
		msgStream << "/1Z61,0," << dVal.str() << (char)0x0D;
		msgStream << readBuffer;

		msgStream >> currentVal;

		msgStream = stringstream();
		int watchdog = 0;
		if (currentVal > val){		// movement in the wrong direction - need to add offset 120
			//			MessageBox(NULL, "Target wavelenght < current wavelength", "DUH", MB_OK);
			double offsetVal = val - 120;
			msgStream << "/1Z61,0," << offsetVal << (char)0x0D;
			watchdog = 0;
			readBuff = 0;
			while (readBuff != 'o'){
				WriteFile(_dev, msgStream.str().c_str(), msgStream.str().length(), &dwBytesWritten, NULL);
				ReadFile(_dev, &readBuff, 1, &dwBytesRead, NULL);
				watchdog++;
				if (watchdog > 100){
					::MessageBox(NULL, "We may be stuck in an infinite loop", "Set wavelength failed", MB_OK | MB_ICONERROR);
					break;
				}
			}
			while (isMotorMoving()){
				//TODO: send notification to parent window(?) to update position - or just simply wait
				Sleep(100);
			}
		}
		// movement in the right direction - no need for offset			
		msgStream << "/1Z61,0," << val << (char)0x0D;
		watchdog = 0;
		readBuff = 0;
		while (readBuff != 'o'){
			WriteFile(_dev, msgStream.str().c_str(), msgStream.str().length(), &dwBytesWritten, NULL);
			ReadFile(_dev, &readBuff, 1, &dwBytesRead, NULL);
			watchdog++;
			if (watchdog > 100){
				::MessageBox(NULL, "We may be stuck in an infinite loop", "Set wavelength failed", MB_OK | MB_ICONERROR);
				break;
			}
		}
		while (isMotorMoving()){
			//TODO: send notification to parent window(?) to update position - or just simply wait
			Sleep(100);
		}

		return;
	};


	double LogicIface::GetPos()
	{
#ifdef NOMONO
		return rand();
#endif
		PurgeComm(_dev, PURGE_RXCLEAR);

		char readBuffer[255];
		DWORD dwBytesRead, dwBytesWritten;
		ZeroMemory(readBuffer, 255);

		WriteFile(_dev, _absPosStr.c_str(), _absPosStr.length(), &dwBytesWritten, NULL);
		ReadFile(_dev, &readBuffer, 9, &dwBytesRead, NULL);
		
		double output = atof(&readBuffer[1]);
		output = output*_gratingFactors[_turret];


		return output;
	};

	int LogicIface::GetTurret()
	{
#ifdef NOMONO
		return 1;
#endif
		char readBuff = 0;
		char readBuffer[255];
		DWORD dwBytesRead, dwBytesWritten;
		ZeroMemory(readBuffer, 255);
		stringstream msgStream;

		int watchdog = 0;
		while (readBuffer[0] != 'o'){
			WriteFile(_dev, _turPosStr.c_str(), _turPosStr.length(), &dwBytesWritten, NULL);
			ReadFile(_dev, readBuffer, 2, &dwBytesRead, NULL);
			watchdog++;
			if (watchdog > 100){
				::MessageBox(NULL, "Wea may be stuck in an infinite loop", "Get turret position failed", MB_OK | MB_ICONERROR);
				break;
			}
		}
		int output = atoi(&readBuffer[1]);

		return output;
	};

	void LogicIface::SetTurret(int turret)
	{
#ifdef NOMONO
		return;
#endif
		DWORD dwBytesWritten, dwBytesRead;
		char readBuffer[255];
		ZeroMemory(readBuffer, 255);
		stringstream msgStream;

		msgStream << "/1Z451,0,0,0," << turret << (char)0x0D;
		int watchdog = 0;
		while (readBuffer[0] != 'o'){
			WriteFile(_dev, msgStream.str().c_str(), msgStream.str().length(), &dwBytesWritten, NULL);
			ReadFile(_dev, readBuffer, 1, &dwBytesRead, NULL);
			if (watchdog > 100){
				::MessageBox(NULL, "We may be stuck in an infinite loop", "Set turret failed", MB_OK | MB_ICONERROR);
				break;
			}
		}

		return;
	};

	int LogicIface::GetSlitPos(int slit)
	{
#ifdef NOMONO
		return rand();
#endif
		PurgeComm(_dev, PURGE_RXCLEAR);

		char readBuff = 0;
		char readBuffer[255];
		DWORD dwBytesRead, dwBytesWritten;
		ZeroMemory(readBuffer, 255);
		stringstream msgStream;

		msgStream << "/1j0," << slit << (char)0x0D;

		int watchdog = 0;
		while (readBuffer[0] != 'o'){
			WriteFile(_dev, msgStream.str().c_str(), msgStream.str().length(), &dwBytesWritten, NULL);
			ReadFile(_dev, readBuffer, 7, &dwBytesRead, NULL);
			watchdog++;
			if (watchdog > 100){
				::MessageBox(NULL, "We may be stuck in an infinite loop", "Get slit position failed", MB_OK | MB_ICONERROR);
				break;
			}
		}
		int output = atoi(&readBuffer[1]);
		//		msgStream << readBuffer << endl << output;
		//		::MessageBox(NULL, msgStream.str().c_str(), "Read slit position", MB_OK | MB_ICONERROR);
		//	int output;

		//		msgStream >> output;



		return output;
	};

	void LogicIface::SetSlit(int slit, int size)
	{
#ifdef NOMONO
		return;
#endif
		DWORD dwBytesWritten, dwBytesRead;
		char readBuffer[255];
		ZeroMemory(readBuffer, 255);
		stringstream msgStream;

		int currVal = GetSlitPos(slit);

		msgStream << "/1k0," << slit << "," << size - currVal << (char)0x0D;
		int watchdog = 0;
		while (readBuffer[0] != 'o'){
			WriteFile(_dev, msgStream.str().c_str(), msgStream.str().length(), &dwBytesWritten, NULL);
			ReadFile(_dev, readBuffer, 1, &dwBytesRead, NULL);
			if (watchdog > 100){
				::MessageBox(NULL, "We may be stuck in an infinite loop", "Set slit failed", MB_OK | MB_ICONERROR);
				break;
			}
		}

		return;
	};

	bool LogicIface::isTurretBusy()
	{
#ifdef NOMONO
		return false;
#endif
		PurgeComm(_dev, PURGE_RXCLEAR);

		//		stringstream msg;
		//		msg << "/1Z453,0,0,0" << (char)0x0D;
		DWORD dwBytesWritten, dwBytesRead;
		char readBuffer[10];
		ZeroMemory(readBuffer, 10);

		int watchdog = 0;
		while (readBuffer[0] != 'o'){
			WriteFile(_dev, _turStatusStr.c_str(), _turStatusStr.length(), &dwBytesWritten, NULL);
			ReadFile(_dev, readBuffer, 2, &dwBytesRead, NULL);
			if (watchdog > 100){
				::MessageBox(NULL, "We may be stuck in an infinite loop", "Check motor state failed", MB_OK | MB_ICONERROR);
				break;
			}
		}

		return checkBusy(readBuffer[1]);
	}

	bool LogicIface::isMotorMoving()
	{
#ifdef NOMONO
		return false;
#endif
		PurgeComm(_dev, PURGE_RXCLEAR);

		DWORD dwBytesWritten, dwBytesRead;
		char readBuffer[10];
		char readBuff = 0;
		ZeroMemory(readBuffer, 10);

		int watchdog = 0;
		while (readBuffer[0] != 'o'){
			WriteFile(_dev, _motorBusyStr.c_str(), _motorBusyStr.length(), &dwBytesWritten, NULL);
			ReadFile(_dev, readBuffer, 2, &dwBytesRead, NULL);
			if (watchdog > 100){
				::MessageBox(NULL, "We may be stuck in an infinite loop", "Check motor state failed", MB_OK | MB_ICONERROR);
				break;
			}
		}

		return checkBusy(readBuffer[1]);
	};

	bool LogicIface::checkBusy(char inp)
	{
		if (inp == 'q')
			return true;
		if (inp == 'z')
			return false;
		else {
			//		::MessageBoxA(NULL, "Wrong read at check motor busy", "ERR", MB_OK);
			return true;
		}
	};

	bool LogicIface::checkStatus(char inp)
	{
		if (inp == 'o')
			return true;
		else
			return false;
	};
};