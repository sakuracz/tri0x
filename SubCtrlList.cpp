#include "SubCtrlList.h"

namespace Win
{
	void ListController::Init(HWND hWnd, ProcPtr prevProc, Controller* prevCont, HWND parent, RECT& rc)
	{
		SubController::Init(hWnd, prevProc, prevCont);
		rect.bottom = rc.bottom;
		rect.top = rc.top;
		rect.left = rc.left;
		rect.right = rc.right;
		parentHWND = parent;		
	}

	bool ListController::OnNCCalcSize(WPARAM wParam, LPARAM lParam)
	{
		return true;	//has to return true otherwise the ugly frame appears around the list popup
	}

	bool ListController::OnWindowPosChanging(WPARAM wParam, LPARAM lParam)
	{
		WINDOWPOS* wndPos = (WINDOWPOS*)lParam;		
		RECT parRect;		
		::GetWindowRect(parentHWND, &parRect);	//get the combo window bounding rect
		wndPos->x = parRect.left;
		wndPos->y = parRect.bottom - 5;
		wndPos->cx = rect.right - rect.left;
		wndPos->cy = rect.bottom - rect.top;

		return true;
	}
}