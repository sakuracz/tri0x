#include "LgcCtrlLock.h"
#include <sstream>
#include <iostream>

#define NOHOMO		//NOHOMO - no lock-in device; NOHOMO_ - using lock-in
#define SR810

namespace Logic
{
	LockInterface::LockInterface()
	{
		_dev = NULL;

		_comm.ReadIntervalTimeout = 5;
		_comm.ReadTotalTimeoutConstant = 0;
		_comm.ReadTotalTimeoutMultiplier = 0;
		_comm.WriteTotalTimeoutConstant = 10;

		_dcb.DCBlength = sizeof(_dcb);
		_dcb.BaudRate = CBR_19200;
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

	LockInterface::~LockInterface()
	{
#ifndef NOHOMO
		Close();
#endif
	};

	void LockInterface::Close()
	{
		CloseHandle(_dev);
	};
	
	int LockInterface::GetDataCount()
	{
#ifdef NOHOMO
		return 1;
#endif
		int ret;
		std::stringstream msg, count, rep;
		char message[255], buffer[255];
		DWORD dwBytesWritten, dwBytesRead;

		msg << "SPTS?" << (char)0x0D;

		strcpy_s(message, msg.str().c_str());
		::WriteFile(_dev, message, 6, &dwBytesWritten, NULL);
		::ReadFile(_dev, buffer, 255, &dwBytesRead, NULL);

		unsigned int i = 0;
		while( i < dwBytesRead)
		{
			if(buffer[i] == (char)0x0D)
				buffer[i] = 0x00;
			i++;
		};
		count << buffer;
		count >> ret;

		rep << buffer << "\n BytesRead: " << dwBytesRead << "\n Read#: " << ret;

//		::MessageBox(NULL, rep.str().c_str(), "Kur", MB_OK);
		return ret;
	};

	double LockInterface::GetMeasuredValues()
	{
#ifdef NOHOMO
		return rand()*1.0/RAND_MAX-0.5;
#endif

		int count = GetDataCount();
		if(count <= 0)
			return 0;
//		std::unique_ptr<std::vector<std::complex<double> > > vPtr(new std::vector<std::complex<double> >);
//		vPtr->resize(count);

		double *readArr = new double(count);
		double single = 0, sum = 0, average = 0;
		char buffer[15];

		std::stringstream msg;
		char message[255];
		DWORD dwBytesWritten, dwBytesRead;
		
#ifdef SR830
		msg << "TRCA?1,0," << count << (char)0x0D;
#endif
#ifdef SR810
		msg << "TRCA?0," << count << (char)0x0D;
#endif
		strcpy_s(message, msg.str().c_str());
		::WriteFile(_dev, message, msg.str().length(), &dwBytesWritten, NULL);
		

		int i = 0, j = 0;		// j - number count
		do{
			i = 0;
			j++;
			buffer[14] = 0x00;
			do{
				::ReadFile(_dev, &buffer[i], 1, &dwBytesRead, NULL);
				i++;
			} while((buffer[i-1] != 0x2C) && (buffer[i-1] != 0x0D));
			if(buffer[i-1] != 0x0D){
				std::stringstream readVal;
				readVal << buffer;
				readVal >> single;
				sum += single;
			};
		} while(buffer[i-1] != 0x0D);
		j--;		//j now carries number of read values
		average = sum/j*1.0;

//		return vPtr.release();
		return average;
	};

	void LockInterface::Init()
	{
		_dev = ::CreateFile("COM3", GENERIC_READ | GENERIC_WRITE,
							0, 0, 
							OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
							NULL);

		if(_dev == INVALID_HANDLE_VALUE){
			if(GetLastError() == ERROR_FILE_NOT_FOUND){
				//do some error output "No port" or something...				
				MessageBox(NULL, "Could not open port COM3", "Error", MB_OK);
				PostQuitMessage(0);
			} else {
				char msg[255];
				sprintf_s(msg, "Failed open port COM3. Error #%d", GetLastError(), MB_OK);
				MessageBox(NULL, msg, "Error", MB_OK);
				PostQuitMessage(0);
			}
		}

		if(!SetCommState(_dev, &_dcb)){
			MessageBox(NULL, "Failed to set proper comm state", "Error", MB_OK);
			PostQuitMessage(0);
		} else {
			
		}
		if(!SetCommTimeouts(_dev, &_comm)){
			MessageBox(NULL, "Failed to set comm timeouts", "Error", MB_OK);
		};

		//initialization string follows, starting from the first command - setting the comm type to RS232:
		std::stringstream msg;
		msg << "OUTX0" << (char)0x0D;
		DWORD dwBytesWritten;
		char message[255];
		::WriteFile(_dev, message, msg.str().length(), &dwBytesWritten, NULL);
	};

	void LockInterface::SetLockInterfaceParams(int tConst, int sens, int slope, int chann)
	{
#ifdef NOHOMO
		return;
#endif
		std::stringstream msg;		
		msg <<  "SENS" << sens << ";OFLT" << tConst << ";OFSL" << slope << ";DDEF1," << chann << ",0" << (char)0x0D; 		

		DWORD dwBytesWritten;
		char message[255];

		strcpy_s(message, msg.str().c_str());
//		::MessageBox(NULL, msg.str().c_str(), "Msg", MB_OK);
		::WriteFile(_dev, message, msg.str().length(), &dwBytesWritten, NULL);
	};

	void LockInterface::StartAcquisition()
	{
#ifdef NOHOMO
		return;
#endif

		std::stringstream msg;
		char message[255];
		DWORD dwBytesWritten;

		msg << "REST;STRT" << (char)0x0D;

		strcpy_s(message, msg.str().c_str());
		::WriteFile(_dev, message, 10, &dwBytesWritten, NULL);

		return;
	};

	void LockInterface::StopAcquisition()
	{
#ifdef NOHOMO
		return;
#endif
		std::stringstream msg;
		char message[255];
		DWORD dwBytesWritten;

		msg << "PAUS" << (char)0x0D;

		strcpy_s(message, msg.str().c_str());
		::WriteFile(_dev, message, 5, &dwBytesWritten, NULL);

		return;
	};

	void LockInterface::ResetLock()
	{
#ifdef NOHOMO
		return;
#endif
		std::stringstream msg;
		char message[255];
		DWORD dwBytesWritten;

		msg << "PAUS;REST" << (char)0x0D;

		strcpy_s(message, msg.str().c_str());
		::WriteFile(_dev, message, 10, &dwBytesWritten, NULL);

		return;
	};
};