#ifndef CLASSEXPWNDCONTROLLER_H_
#define CLASSEXPWNDCONTROLLER_H_

#include "libWin\ClassChildController.h"
#include "SubCtrlEdit.h"
#include "libWin\WindowControls.h"
#include <string>
#include <vector>
#include <list>
//#include "struct.h"

using namespace std;

namespace Win
{
	class ExpWndController : public ChildController
	{
	public:
		friend class Synchronizer;
		ExpWndController();
		~ExpWndController();
		void ReturnExpParams(vector<double>&);
		bool OnCommand(WPARAM, LPARAM) override;
		bool OnCreate(CreateData const*) override;
		bool OnSize(int, int, int) override;
		bool OnNotify(HWND, LPARAM) override;	//reads input parameters since edit boxes trigger this message
		bool OnEraseBG(HDC) override { return false; }
		void setEditVal(int, string);
		void visibleRun();
		void visibleStop();
		void UpdateEditBox(vector<double>&, int);
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

		list<HWND> tabList;
		list<HWND>::const_iterator tabIter;

		double _startPos;
		double _stopPos;
		double _incPos;
	};
};

#endif