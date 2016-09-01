#ifndef BUTTONSUBCONTROLLER_H_
#define BUTTONSUBCONTROLLER_H_

#include "libWin\ClassControllerSub.h"
#include <string>

using std::string;

namespace Win
{
	class ButtonController : public SubController
	{
	public:
		bool OnLMouseDblClick() override;
	};
}

#endif