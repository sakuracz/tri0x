#include "Procedure.h"
#include "ClassControllerMain.h"
#include "ClassControllerSub.h"

namespace Win
{
	LRESULT CALLBACK Procedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		MainController* pCtrl = Win::GetLong<MainController*>(hwnd);
		switch(message)
		{
		case WM_DESTROY:
			delete pCtrl;
			return 0;
		case WM_CREATE:
			try{
				pCtrl = new MainController(hwnd, reinterpret_cast<CreateData*>(lParam));
				Win::SetLong(hwnd, pCtrl);
				pCtrl->OnCreate(reinterpret_cast<CreateData const*>(lParam));
			} catch(char const *msg) {
				MessageBox(hwnd, msg, "Initialization", MB_OK | MB_ICONEXCLAMATION);
				return -1;
			} catch (...) {
				MessageBox(hwnd, "Unknown Error", "Initialization", MB_OK | MB_ICONEXCLAMATION);
				return -1;
			}
			return 0;
		case WM_NOTIFY:
			if(pCtrl->OnNotify(wParam, lParam))
				return 0;
			break;
		}
		return ::DefWindowProc(hwnd, message, wParam, lParam);
	};

	LRESULT CALLBACK SubProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		SubController* pCtrl = Win::GetLong<SubController*>(hwnd);
		switch(message)
		{
		case WM_LBUTTONUP:
			if(pCtrl->OnLMouseButtonUp())
				return 0;
			break;
		case WM_LBUTTONDBLCLK:
			if(pCtrl->OnLMouseDblClick())
				return 0;
			break;
		case WM_KEYDOWN:
			if (pCtrl->OnKeyDown(wParam, lParam))
				return 0;
			break;
		};
		return pCtrl->CallPrevProc(message, wParam, lParam);
	};

	LRESULT CALLBACK childProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		ChildController* pCtrl = Win::GetLong<ChildController*>(hwnd);
		switch (message)
		{
		case WM_NCCREATE:
		{
			CreateData const *create = reinterpret_cast<CreateData const*>(lParam);
			pCtrl = static_cast<ChildController*>(create->GetCreationData());
			pCtrl->SetWindowHandle(hwnd);
			Win::SetLong<ChildController*>(hwnd, pCtrl);
		}
		break;
		case WM_COMMAND:
			return pCtrl->OnCommand(wParam, lParam);
			break;
		case WM_CREATE:
			if (pCtrl->OnCreate(reinterpret_cast<CreateData const *>(lParam)))
				return 0;
			break;
		case WM_DRAWITEM:
			if (pCtrl->OnDrawItem(lParam))
				return TRUE;
		case WM_ERASEBKGND:
			if (pCtrl->OnEraseBG((HDC)wParam))
				return TRUE;
			break;
		case WM_HOTKEY:
			//				::MessageBoxA(NULL, "LOL", "Dur", MB_OK);
			if (pCtrl->OnHotKey(wParam, lParam))
				return 0;
			break;
		case WM_KILLFOCUS:
			if (pCtrl->OnKillFocus((HWND)wParam))
				return 0;
			break;
		case WM_KEYDOWN:
			if (pCtrl->OnKeyDown(wParam, lParam))
				return 0;
			break;
		case WM_LBUTTONDOWN:
			if (pCtrl->OnLButtonDown(wParam, LOWORD(lParam), HIWORD(lParam)))
				return 0;
			break;
		case WM_SIZE:
			if (pCtrl->OnSize(LOWORD(lParam), HIWORD(lParam), wParam))
				return 0;
			break;
		case WM_NOTIFY:
			if (pCtrl->OnNotify(((LPNMHDR)lParam)->hwndFrom, lParam))
				return 0;
			break;
		case WM_PAINT:
			if (pCtrl->OnPaint())
				return 0;
			break;
		case WM_SETFOCUS:
			if (pCtrl->OnSetFocus((HWND)wParam))
				return 0;
			break;
		case WM_SIZING:
			return (pCtrl->OnSizing((RECT*)lParam));
			break;
		case WM_MOVING:
			return (pCtrl->OnMoving((RECT*)lParam));
			break;
		}
		return ::DefWindowProc(hwnd, message, wParam, lParam);
	};
};