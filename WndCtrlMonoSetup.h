#ifndef MONOSETUPWINDOWCONTROLLER_H_
#define MONOSETUPWINDOWCONTROLLER_H_

#include "libWin\ClassChildController.h"
#include "libWin\WindowControls.h"

namespace Win{

	class MonoWndController : ChildController
	{
	public:
		MonoWndController();
		bool OnCreate(CreateData const *);
		bool OnCommand(WPARAM, LPARAM);
	};
}

#endif