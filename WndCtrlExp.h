#ifndef CLASSEXPWNDCONTROLLER_H_
#define CLASSEXPWNDCONTROLLER_H_

#include "libWin\ClassChildController.h"
#include "SubCtrlEdit.h"
#include "libWin\WindowControls.h"
//#include "struct.h"

namespace Win
{
	class ExpWndController : public ChildController
	{
	public:
		ExpWndController();
		~ExpWndController();
//		int GetProg(){return _prog;}
//		void ResetProg();
//		void startExp();
		void ReturnExpParams(int*);
		void ReturnSet(int*);
		bool OnCommand(WPARAM, LPARAM);
		bool OnCreate(CreateData const*);
		bool OnSize(int,int,int);
		bool OnNotify(HWND, LPARAM);
		void visibleRun();
		void visibleStop();
	protected:
		EditController	_edtCtrl[20];
		StaticControl	*_stcArray[13];
		EditControl		*_edtArray[20];		
		ButtonControl	*_btnArray[16];
	private:				
		double _interval;
		double _timeConst;
		int _pointCount;
		int _chann;

		double _startPos;
		double _stopPos;
		double _incPos;		
	};
};

#endif