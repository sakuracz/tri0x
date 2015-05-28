#ifndef CLASSEXPWNDCONTROLLER_H_
#define CLASSEXPWNDCONTROLLER_H_

#include "libWin\ClassChildController.h"
#include "SubCtrlEdit.h"
#include "libWin\WindowControls.h"
#include <string>
//#include "struct.h"

using namespace std;

namespace Win
{
	class ExpWndController : public ChildController
	{
	public:
		ExpWndController();
		~ExpWndController();
		void ReturnExpParams(double*);
		void ReadExpParams();
		bool OnCommand(WPARAM, LPARAM);
		bool OnCreate(CreateData const*);
		bool OnSize(int,int,int);
		bool OnNotify(HWND, LPARAM);
		void setEditVal(int, string);
		void visibleRun();
		void visibleStop();
		void UpdateEditBox(double*, int);
		void UpdatePos(double);
		double GetEditVal(int);
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