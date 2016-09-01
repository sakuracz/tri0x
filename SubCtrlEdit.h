#ifndef EDITSUBCONTROLLER_H_
#define EDITSUBCONTROLLER_H_

#include "libWin\ClassControllerSub.h"

namespace Win
{
	class EditController : public SubController
	{
	public:
		bool OnLMouseButtonUp(WPARAM, LPARAM);
		bool OnKeyDown(WPARAM, LPARAM);
//		bool OnDrawItem(LPARAM) override { return false; }				
		bool OnEraseBG(HDC) override { return false; }		
	};
};

#endif