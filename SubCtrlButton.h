#ifndef BUTTONSUBCONTROLLER_H_
#define BUTTONSUBCONTROLLER_H_

#include "libWin\ClassControllerSub.h"

namespace Win
{
	class ButtonController : public SubController
	{
	public:
		bool OnDrawItem(LPARAM){ return false; }
	};
}



#endif