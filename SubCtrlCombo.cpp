#include "SubCtrlCombo.h"
#include <string>
#include <sstream>

using std::stringstream;
using std::string;

namespace Win
{
	ComboController::ComboController(CustomCombo& theCombo) : combo(theCombo), sublist_controller(new ListController)
	{		
	}

	ComboController::~ComboController()
	{
	}

	void ComboController::Invalidate()
	{
		::InvalidateRect(combo.GetHandle(), NULL, TRUE);		//invalidate whole client area
	}
	
	bool ComboController::OnPaint()
	{
		PAINTSTRUCT ps;
		HDC hDC = ::BeginPaint(_hwnd, &ps);

		HDC compHDC = ::CreateCompatibleDC(hDC);
		if (compHDC == NULL)
			::MessageBox(NULL, "::CreateCompatibleDC returned NULL", "Error in CustomCombo::Draw", MB_OK);

		HBITMAP bm;
		if (!combo.isBeingSelected && !combo.isSelected){
			bm = (HBITMAP)combo.header_bmaps[0];
		}
		else if (combo.isBeingSelected){
			bm = (HBITMAP)combo.header_bmaps[2];
		}
		else {
			bm = (HBITMAP)combo.header_bmaps[1];
		}
		::SelectObject(compHDC, bm);
		::BitBlt(hDC, 0, 0, combo.GetWidth(), combo.GetHeight(), compHDC, 0, 0, SRCCOPY);

		if (combo.isSelected){
			bm = (HBITMAP)combo.footer_bmaps[combo.selection];
			::SelectObject(compHDC, bm);
			::BitBlt(hDC, 0, combo.GetHeight(), combo.GetWidth(), combo.GetHeight(), compHDC, 0, 0, SRCCOPY);
		}		

		::DeleteDC(compHDC);
		::EndPaint(_hwnd, &ps);

		return true;
	}

	void ComboController::SubList()
	{
		comboInfo.cbSize = sizeof(COMBOBOXINFO);
		::GetComboBoxInfo(combo.GetHandle(), &comboInfo);

		LONG listProc = ::GetWindowLong(comboInfo.hwndList, GWL_WNDPROC);
		LONG comboProc = ::GetWindowLong(comboInfo.hwndCombo, GWL_WNDPROC);

		RECT listRect;
		listRect.top = combo.selected.top;
		listRect.left = combo.selected.left;
		listRect.right = listRect.left + 136;
		listRect.bottom = listRect.top + combo.items.size() * 30;

		sublist_controller->Init(comboInfo.hwndList, reinterpret_cast<ProcPtr>(listProc), this, combo.GetHandle(), listRect);
		::SetWindowLong(comboInfo.hwndList, GWL_USERDATA, reinterpret_cast<LONG>(sublist_controller.get()));
		::SetWindowLong(comboInfo.hwndList, GWL_WNDPROC, reinterpret_cast<LONG>(SpecialListProc));
	}
}