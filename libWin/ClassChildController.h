#ifndef CHILDCONTROLLER_H_
#define CHILDCONTROLLER_H_

#include "ClassController.h"

namespace Win
{
	class ChildController : public Controller
	{
	public:
		ChildController();
		void SetWindowHandle(HWND win){_hwnd = win;}
//		bool OnLMouseButtounUp();
		bool OnSizing(RECT*);
		bool OnMove(WPARAM, LPARAM) override { return false; }
		bool OnHotKey(WPARAM, LPARAM) override { return false; }
		bool OnNotify(HWND, LPARAM) override { return false; }
		HRESULT OnCTLColorEdit(HDC, HWND) { return false; }
		HRESULT OnCTLColorListBox(HDC, HWND) override { return false; };
		virtual bool OnLButtonDown(WPARAM, int, int){return false;}
		virtual bool OnKillFocus(HWND){return false;}
		virtual bool OnSetFocus(HWND){return false;}
		virtual bool OnMoving(RECT*){return false;}
		virtual bool OnSize(int, int, int){return false;}		
		virtual bool OnDrawItem(LPARAM){ return false; }		
		bool OnLMouseButtonUp(WPARAM, LPARAM) override { return false; }
		bool OnLMouseButtonDown(WPARAM, LPARAM) override { return false; };
		bool OnLMouseDblClick() override { return false; };
		bool OnNCCalcSize(WPARAM, LPARAM) override { return false; };
		bool OnNCPaint(WPARAM, LPARAM) override { return false; }
		bool OnWindowPosChanging(WPARAM, LPARAM) override { return false; }
		bool OnEraseBG(HDC) override { return false; }
		void InitMinXY(int, int);
	protected:		
		int _minX;
		int _minY;
	};
}

#endif
