#include "SubCtrlEdit.h"

namespace Win
{
	EditController::EditController(CustomEdit& theEdit)
		: edit(theEdit)
	{
	}

	HRESULT EditController::OnCTLColorEdit(HDC hdc, HWND win)
	{
		return (HRESULT)::GetSysColorBrush(4);
	}

	HRESULT EditController::OnCTLColorStatic(HDC hdc, HWND win)
	{
//		return (HRESULT)::CreateSolidBrush(RGB(236,233,230));
		return (HRESULT)::GetStockObject(GRAY_BRUSH);
	}

	bool EditController::OnEraseBG(HDC hdc)
	{
		HDC compHDC = ::CreateCompatibleDC(hdc);
		BITMAP bm;
		HBITMAP bg = (HBITMAP)edit.bmapBack;
		::GetObject(edit.bmapBack, sizeof(BITMAP), &bm);
		::SelectObject(compHDC, bg);
		::BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, compHDC, 0, 0, SRCCOPY);

		::DeleteDC(compHDC);

		return true;
	}

	bool EditController::OnKeyDown(WPARAM wParam, LPARAM lParam)
	{
		if ((wParam == VK_RETURN) || (wParam == VK_TAB))
		{
			NMHDR nmh;
			nmh.code = VK_RETURN;
			nmh.idFrom = GetDlgCtrlID(_hwnd);
			nmh.hwndFrom = _hwnd;
			::SendMessage(::GetParent(_hwnd), WM_NOTIFY, nmh.idFrom, (LPARAM)&nmh);			
		}
		return false;
	}

	bool EditController::OnKillFocus(WPARAM wParam, LPARAM lParam)
	{
		::SendMessage(_hwnd, EM_SETSEL, 0, -1);
		::SendMessage(_hwnd, EM_SETSEL, -1, -1);
		if (wParam != NULL)
			::SetFocus((HWND)wParam);
		return true;
	}

	bool EditController::OnLMouseButtonDown(WPARAM wParam, LPARAM lParam)
	{
		::SetFocus(_hwnd);
		//		::SendMessage(_hwnd, EM_SETSEL, 0, -1);
		//		::SendMessage(_hwnd, EM_SETSEL, -1, -1);
		return false;
	};

	bool EditController::OnLMouseDblClick()
	{
		::SendMessage(_hwnd, EM_SETSEL, 0, -1);
		return true;
	}
};