//SubController class definition
//EditController class definition

#ifndef CLASSCONTROLLERSUB_H_
#define CLASSCONTROLLERSUB_H_

#include "ClassController.h"
#include "Procedure.h"

namespace Win
{
	class SubController : public Controller
	{
	public:
		SubController();
		void Init(HWND, ProcPtr, Controller*);
		LRESULT CallPrevProc(UINT, WPARAM, LPARAM);
		ProcPtr GetPrevProc();
		Controller * GetPrevController();
		bool OnLMouseDblClick(){return true;}
		bool OnHotKey(WPARAM, LPARAM) override { return false; }
		bool OnNotify(HWND, LPARAM) override { return false; }
		virtual bool OnTabKeyDown(){return 0;}
		virtual bool OnDrawItem(LPARAM) = 0;
	protected:
		ProcPtr _prevProc;
		Controller* _prevController;
	};
};

#endif