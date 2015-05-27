#include "LgcIface.h"
#include <sstream>
#include <iomanip>

using namespace std;

#define NOHOMO			//NOHOMO - no lock-in nor triax; NOHOMO_ - use devs

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
		stream << (char)222;
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
		stream << "f0" << (char)0x0D; 
		_mirRearStr = stream.str();
		stream = stringstream();
		stream << "e0" << (char)0x0D;
		_mirSideStr = stream.str();
		stream = stringstream();
		stream << "l";
		_mirCheckStr = stream.str();
		stream = stringstream();
		stream << "H0" << (char)0x0D;
		_motorReadStr = stream.str();
		stream = stringstream();
		stream << "E";
		_motorBusyStr = stream.str();
		stream = stringstream();
		stream << "C0" << (char)0x0D;
		_motorSpeedStr = stream.str();
		stream = stringstream();
		stream << "L";
		_motorStopStr = stream.str();
		stream = stringstream();
		stream << "Z452,0,0,0" << (char)0x0D;
		_turPosStr = stream.str();
		stream = stringstream();
		stream << "Z453,0,0,0" << (char)0x0D;
		_turStatusStr = stream.str();
		stream = stringstream();
		stream << "Z62,0" << (char)0x0D;
		_absPosStr = stream.str();
		// end of common string
		
#ifndef NOHOMO
		Init();
#endif
	};

	LogicIface::~LogicIface()
	{

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
#ifdef NOHOMO
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

		if (readBuffer[0] != 'B')	//if so then hung;
		{
			WriteFile(_dev, _boot2MainStr.c_str(), _boot2MainStr.length(), &dwBytesWritten, NULL);
			ReadFile(_dev, readBuffer, 1, &dwBytesRead, NULL);
		}
		if (readBuffer[0] == 'F')
		{
			if (_force)
			{
				WriteFile(_dev, _initStr.c_str(), _initStr.length(), &dwBytesWritten, NULL);
				return;
			}
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
		DWORD dwBytesWritten, dwBytesRead;
		char readBuff[255];
		std::stringstream inpStream;

#ifndef NOHOMO
		WriteFile(_dev, _dataQuery.c_str(), _dataQuery.length(), &dwBytesWritten, NULL);
		ReadFile(_dev, readBuff, 255, &dwBytesRead, NULL);
		inpStream << readBuff;
		inpStream >> outArr[0] >> outArr[1] >> outArr[2];
#else
		outArr[0] = 123.1;
		outArr[1] = 321.2;
		outArr[2] = 231.3;
#endif

		return;
	};

	void LogicIface::Goto(double target)
	{
		DWORD dwBytesWritten, dwBytesRead;
		char readBuffer[255];
		ZeroMemory(readBuffer, 255);
		stringstream msgStream;		
		double val = target / _gratingFactors[_turret];

		msgStream.precision(2);
		
		//TODO: checking movement direction
		msgStream << "/1Z61,0," << val << (char)0x0D;
		int watchdog = 0;
		while (readBuffer[0] != 'o'){
			WriteFile(_dev, msgStream.str().c_str(), msgStream.str().length(), &dwBytesWritten, NULL);
			ReadFile(_dev, readBuffer, 1, &dwBytesRead, NULL);
			watchdog++;
			if (watchdog > 100){
				::MessageBox(NULL, "We may be stuck in an infinite loop", "Set wavelength failed", MB_OK | MB_ICONERROR);
				break;
			}
		}

		return;
	};

	int LogicIface::GetSlitPos(int slit)
	{
		char readBuff = 0;
		char readBuffer[255];
		DWORD dwBytesRead, dwBytesWritten;
		ZeroMemory(readBuffer, 255);
		stringstream msgStream;

		msgStream << "/1j0," << slit << (char)0x0D;

		int watchdog = 0;
		while (readBuff != 'o'){
			WriteFile(_dev, msgStream.str().c_str(), msgStream.str().length(), &dwBytesWritten, NULL);
			ReadFile(_dev, &readBuff, 1, &dwBytesRead, NULL);
			ReadFile(_dev, &readBuffer, 4, &dwBytesRead, NULL);
			watchdog++;
			if (watchdog > 100){
				::MessageBox(NULL, "We may be stuck in an infinite loop", "Get slit position failed", MB_OK | MB_ICONERROR);
				break;
			}
		}
				
		msgStream << readBuffer;
		int output;

		msgStream >> output;

		return output;
	};

	double LogicIface::GetPos()
	{
		char readBuff = 0;
		char readBuffer[255];
		DWORD dwBytesRead, dwBytesWritten;
		ZeroMemory(readBuffer, 255);
		stringstream msgStream;		

		int watchdog = 0;
		while (readBuff != 'o'){
			WriteFile(_dev, _absPosStr.c_str(), _absPosStr.length(), &dwBytesWritten, NULL);
			ReadFile(_dev, &readBuff, 1, &dwBytesRead, NULL);
			ReadFile(_dev, &readBuffer, 8, &dwBytesRead, NULL);
			watchdog++;
			if (watchdog > 100){
				::MessageBox(NULL, "We may be stuck in an infinite loop", "Get wavelength failed", MB_OK | MB_ICONERROR);
				break;
			}
		}

		msgStream << readBuffer;
		double output;		

		msgStream >> output;
		output = output*_gratingFactors[_turret];

		return output;		
	};

	int LogicIface::GetTurret()
	{
		char readBuff = 0;
		char readBuffer[255];
		DWORD dwBytesRead, dwBytesWritten;
		ZeroMemory(readBuffer, 255);
		stringstream msgStream;

		int watchdog = 0;
		while (readBuff != 'o'){
			WriteFile(_dev, _turPosStr.c_str(), _turPosStr.length(), &dwBytesWritten, NULL);
			ReadFile(_dev, &readBuff, 1, &dwBytesRead, NULL);
			ReadFile(_dev, &readBuffer, 1, &dwBytesRead, NULL);
			watchdog++;
			if (watchdog > 100){
				::MessageBox(NULL, "We may be stuck in an infinite loop", "Get turret position failed", MB_OK | MB_ICONERROR);
				break;
			}
		}

		msgStream << readBuffer;
		int output;

		msgStream >> output;

		return output;
	};

	void LogicIface::SetTurret(int turret)
	{
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

	void LogicIface::SetSlit(int slit, int size)
	{
		DWORD dwBytesWritten, dwBytesRead;
		char readBuffer[255];
		ZeroMemory(readBuffer, 255);
		stringstream msgStream;

		msgStream << "/1i0," << slit << "," << size << (char)0x0D;
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

	void LogicIface::Close()
	{
		if(_dev)
			CloseHandle(_dev);
		_dev = nullptr;

		return;
	};

	bool LogicIface::checkBusy(char inp)
	{
		if (inp == 'q')
			return true;
		if (inp == 'z')
			return false;
	};

	bool LogicIface::checkStatus(char inp)
	{
		if (inp == 'o')
			return true;
		else if (inp == 'z')
			return false;
//		else {
//			::MessageBox(NULL, "Bad status byte received", "Communication error", MB_OK);
//			return false;
//		}

	};
};