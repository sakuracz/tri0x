#include "SubCtrlEdit.h"

namespace Win
{
	bool EditController::OnLMouseButtonUp(WPARAM wParam, LPARAM lParam)
	{
		::SetFocus(_hwnd);

		return true;
	};
	bool EditController::OnKeyDown(WPARAM wParam, LPARAM lParam)
	{
		if ((wParam == VK_RETURN) || (wParam == VK_TAB))
		{
			NMHDR nmh;
			nmh.code = VK_RETURN;
			nmh.idFrom = GetDlgCtrlID(_hwnd);
			nmh.hwndFrom = _hwnd;
			::SendMessage(::GetParent(_hwnd), WM_NOTIFY, nmh.idFrom, (LPARAM)&nmh);
			return true;
		}
		return false;
	}
};