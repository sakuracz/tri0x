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
		virtual bool OnHotKey(WPARAM, LPARAM){return false;}
		virtual bool OnLButtonDown(WPARAM, int, int){return false;}
		virtual bool OnKillFocus(HWND){return false;}
		virtual bool OnSetFocus(HWND){return false;}
		virtual bool OnMoving(RECT*){return false;}
		virtual bool OnSize(int w, int h, int f){return false;}
		virtual bool OnHotkey(WPARAM wParam,LPARAM lParam){return false;}
		void InitMinXY(int, int);
	protected:		
		int _minX;
		int _minY;
	};
};

#endif