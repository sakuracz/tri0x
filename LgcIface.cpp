#include "LgcIface.h"
#include <sstream>

using namespace std;

#define NOHOMO_			//NOHOMO - no lock-in nor triax; NOHOMO_ - use devs

namespace Logic
{
	LogicIface::LogicIface(int* params)		
	{
		_dev = NULL;

		_comm.ReadIntervalTimeout = 5;
		_comm.ReadTotalTimeoutConstant = 0;
		_comm.ReadTotalTimeoutMultiplier = 0;
		_comm.WriteTotalTimeoutConstant = 10;

		_dcb.DCBlength = sizeof(_dcb);
		_dcb.BaudRate = CBR_115200;
		_dcb.ByteSize = 8;
		_dcb.StopBits = ONESTOPBIT;
		_dcb.Parity = NOPARITY;
		_dcb.fBinary = TRUE;
		_dcb.fOutxCtsFlow = FALSE;
		_dcb.fOutxDsrFlow = FALSE;
		_dcb.fDtrControl = DTR_CONTROL_DISABLE;
		_dcb.fRtsControl = RTS_CONTROL_DISABLE;
		_dcb.fDsrSensitivity = FALSE;
		_dcb.fOutX = FALSE;
		_dcb.fInX = FALSE;
		_dcb.fParity = FALSE;
		_dcb.fNull = TRUE;

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

	void LogicIface::InitMono(bool bForce)
	{
		std::stringstream sstream;
		DWORD dwBytesWritten, dwBytesRead;
		char readBuffer[255];
		WriteFile(_dev, "/1 ", 3, &dwBytesWritten, NULL);
		ReadFile(_dev, readBuffer, 1, &dwBytesRead, NULL);

		if (readBuffer[0] == '*')
		{
			sstream << "/1" << (char)247;
			WriteFile(_dev, sstream.str().c_str(), 1, &dwBytesWritten, NULL);
			ReadFile(_dev, readBuffer, 1, &dwBytesRead, NULL);
			if (readBuffer[0] != '=')
				return;
		}

		else if (readBuffer[0] != 'B')	//if so then hung;
		{
			sstream << "/1O2000" << 0x00;
			WriteFile(_dev, sstream.str().c_str(), 8, &dwBytesWritten, NULL);
			ReadFile(_dev, readBuffer, 1, &dwBytesRead, NULL);
		}
		if (readBuffer[0] == 'F')
		{
			if (bForce)
			{
				WriteFile(_dev, "/1A", 3, &dwBytesWritten, NULL);
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

	void LogicIface::queryData()
	{
		DWORD dwBytesWritten, dwBytesRead;
		stringstream sStream;
		char readBuff[255];
		double q1, q2, x1;
		sStream << "/2q1" << 0x0d << "q2" << 0x0d << "x1" << 0x0d;
#ifndef NOHOMO
		WriteFile(_dev, sStream.str().c_str(), sStream.str().length(), &dwBytesWritten, NULL);
		ReadFile(_dev, readBuff, 255, &dwBytesRead, NULL);
		sStream << readBuff;
		sStream >> q1 >> q2 >> x1;
#else
		q1 = 123.1;
		q2 = 321.2;
		x1 = 231.3;
#endif

		return;
	};

	void LogicIface::Goto(double target)
	{

		return;
	};

	void LogicIface::SetTurret(int turret)
	{

		return;
	};

	void LogicIface::SetSlit(int slit, int size)
	{

		return;
	};

};