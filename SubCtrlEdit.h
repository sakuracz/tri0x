#ifndef EDITSUBCONTROLLER_H_
#define EDITSUBCONTROLLER_H_

#include "libWin\ClassControllerSub.h"

namespace Win
{
	class EditController : public SubController
	{
	public:
		bool OnLMouseButtonUp();
		bool OnKeyDown(WPARAM, LPARAM);
	};
};

#endif