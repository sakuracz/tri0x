#include "SubCtrlRadio.h"

namespace Win
{
	RadioController::RadioController(CustomRadio& theRadio) 
		: radio(theRadio)
	{
	};

	bool RadioController::OnLMouseButtonUp(WPARAM wParam, LPARAM lParam)
	{
		radio.isChecked = !radio.isChecked;
		InvalidateRect(radio.GetHandle(), NULL, TRUE);

		return false;
	}

	bool RadioController::OnPaint()
	{
		PAINTSTRUCT ps;
		HDC hDC = ::BeginPaint(_hwnd, &ps);

		HDC compDC = ::CreateCompatibleDC(hDC);
		if (compDC == NULL)
			::MessageBox(NULL, "::CreateCompatibleDC returned NULL", "Error in CustomCombo::Draw", MB_OK);

		HBITMAP bmMask, bmImg;

		if (radio.isChecked){
			bmImg = (HBITMAP)radio.bmapCheck.get();			
		} else {
			bmImg = (HBITMAP)radio.bmapIdle.get();			
		}

		bmMask = (HBITMAP)radio.bmapMask.get();

		::SelectObject(compDC, bmMask);
		::BitBlt(hDC, 0, 0, 22, 22, compDC, 0, 0, SRCAND);

		::SelectObject(compDC, bmImg);
		::BitBlt(hDC, 0, 0, 22, 22, compDC, 0, 0, SRCPAINT);

		::DeleteDC(compDC);
		::EndPaint(_hwnd, &ps);

		return true;
	}
}