#include "SubCtrlCombo.h"
#include <string>
#include <sstream>

using std::stringstream;
using std::string;

namespace Win
{
	ComboController::ComboController(CustomCombo& theCombo) : combo(theCombo)
	{		
	}

	void ComboController::Invalidate()
	{
		RECT full = combo.selecting;
		::InvalidateRect(combo._h, &full, TRUE);
	}

	bool ComboController::OnCommand(WPARAM wParam, LPARAM lParam)
	{
		::MessageBox(NULL, "C", "Command", MB_OK);

		return true;
	}
	
	bool ComboController::OnLMouseButtonUp(WPARAM wParam, LPARAM lParam)
	{
//		::MessageBox(NULL, "Primo", "May work", MB_OK);
//		RECT full;
//		full = combo.selecting;
//		combo.ToggleSelecting();
//		::InvalidateRect(combo._h, &full, TRUE);

//		return true;
		return false;
	}

	bool ComboController::OnLMouseButtonDown(WPARAM wParam, LPARAM lParam)
	{
//		::MessageBox(NULL, "Again", "This", MB_OK);
//		RECT full;
//		full = combo.selecting;
//		::InvalidateRect(combo._h, &full, TRUE );
//		return true;
		return false;
	}

	bool ComboController::OnNCCalcSize(WPARAM wParam, LPARAM lParam)
	{
		if (wParam == TRUE)
		{
			NCCALCSIZE_PARAMS* par = (NCCALCSIZE_PARAMS*)lParam;
			stringstream sss;

			if (par->lppos->flags == 0x190c){
				sss << "Wnd X: " << par->lppos->x << " Wnd Y: " << par->lppos->y << " Width: " << par->lppos->cx << " Height: " << par->lppos->cy << std::endl;
				sss << par->rgrc[0].left << " - " << par->rgrc[0].right << " - " << par->rgrc[0].top << " - " << par->rgrc[0].bottom << std::endl;
				sss << par->rgrc[1].left << " - " << par->rgrc[1].right << " - " << par->rgrc[1].top << " - " << par->rgrc[1].bottom << std::endl;
				sss << par->rgrc[2].left << " - " << par->rgrc[2].right << " - " << par->rgrc[2].top << " - " << par->rgrc[2].bottom << std::endl;
				sss << "Flags: " << std::hex << par->lppos->flags << " HWND: " << par->lppos->hwnd << std::endl;

				par->rgrc[0].left = 10;
				par->rgrc[0].right = 146;
				par->rgrc[0].top = 11;
				par->rgrc[0].bottom = 41;
				
				par->lppos->x = 10;
				par->lppos->y = 11;
				par->lppos->cx = 136;
				par->lppos->cy = 30;
			}
			if (par->lppos->flags == 0x191e){
				sss << "Wnd X: " << par->lppos->x << " Wnd Y: " << par->lppos->y << " Width: " << par->lppos->cx << " Height: " << par->lppos->cy << std::endl;
				sss << par->rgrc[0].left << " - " << par->rgrc[0].right << " - " << par->rgrc[0].top << " - " << par->rgrc[0].bottom << std::endl;
				sss << par->rgrc[1].left << " - " << par->rgrc[1].right << " - " << par->rgrc[1].top << " - " << par->rgrc[1].bottom << std::endl;
				sss << par->rgrc[2].left << " - " << par->rgrc[2].right << " - " << par->rgrc[2].top << " - " << par->rgrc[2].bottom << std::endl;
				sss << "Flags: " << std::hex << par->lppos->flags << " HWND: " << par->lppos->hwnd << std::endl;

				par->rgrc[0].left = 10;
				par->rgrc[0].right = 146;
				par->rgrc[0].top = 11;
				par->rgrc[0].bottom = 41;

				par->lppos->x = 10;
				par->lppos->y = 11;
				par->lppos->cx = 136;
				par->lppos->cy = 30;

				par->rgrc[1].left = 10;
				par->rgrc[1].right = 120;
				par->rgrc[1].top = 11;
				par->rgrc[1].bottom = 41;

				par->rgrc[2].left = 10;
				par->rgrc[2].right = 146;
				par->rgrc[2].top = 11;
				par->rgrc[2].bottom = 41;
			}
		}

		return false;
	}

	bool ComboController::OnPaint()
	{
		PAINTSTRUCT ps;
		HDC hDC = ::BeginPaint(_hwnd, &ps);

		HDC compHDC = ::CreateCompatibleDC(hDC);
		if (compHDC == NULL)
		::MessageBox(NULL, "::CreateCompatibleDC returned NULL", "Error in CustomCombo::Draw", MB_OK);

		HBITMAP bm;
		RECT rcItem = { 0, 0, 30, 136 };	//start with the top part		
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
		::BitBlt(hDC, rcItem.left, rcItem.top, 136, 30, compHDC, 0, 0, SRCCOPY);
	
		rcItem.top += 30;
		rcItem.bottom += 30;

		if (combo.isSelected){
			bm = (HBITMAP)combo.footer_bmaps[combo.selection];
			::SelectObject(compHDC, bm);
			::BitBlt(hDC, rcItem.left, rcItem.top, 136, 30, compHDC, 0, 0, SRCCOPY);
		}		
	
		::DeleteDC(compHDC);
//		::EndPaint(_hwnd, &ps);
//		::DeleteDC(hDC);
		return true;
	}
}