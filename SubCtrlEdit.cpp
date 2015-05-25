#include "SubCtrlEdit.h"

namespace Win
{
	bool EditController::OnLMouseButtonUp()
	{
		::SetFocus(_hwnd);

		return true;
	};
};