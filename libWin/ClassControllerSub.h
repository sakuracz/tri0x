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
		virtual void Init(HWND, ProcPtr, Controller*);
		LRESULT CallPrevProc(UINT, WPARAM, LPARAM);
		ProcPtr GetPrevProc();
		Controller * GetPrevController();	
		HRESULT OnCTLColorEdit(HDC, HWND) { return false; }
		HRESULT OnCTLColorListBox(HDC, HWND) override { return false; }
		bool OnHotKey(WPARAM, LPARAM) override { return false; }
		bool OnLMouseDblClick() override { return false; }
		bool OnLMouseButtonUp(WPARAM, LPARAM) override { return false; }
		bool OnLMouseButtonDown(WPARAM, LPARAM) override { return false; }
		bool OnMove(WPARAM, LPARAM) override { return false; }		
		bool OnNotify(HWND, LPARAM) override { return false; }
		bool OnEraseBG(HDC) override { return false; }
		bool OnNCCalcSize(WPARAM, LPARAM) override { return false; };
		bool OnNCPaint(WPARAM, LPARAM) override { return false; }
		bool OnWindowPosChanging(WPARAM, LPARAM) override { return false; }
		virtual bool OnNCActivate(WPARAM, LPARAM) { return false; }
		virtual bool OnPaint() { return false; }
		virtual bool OnTabKeyDown(){return 0;}
		virtual bool OnKillFocus(WPARAM, LPARAM){ return false; }
//		virtual bool OnDrawItem(LPARAM) = 0;
	protected:
		ProcPtr _prevProc;
		Controller* _prevController;
	};
}

#endif
