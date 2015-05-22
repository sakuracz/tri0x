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
		};
		return pCtrl->CallPrevProc(message, wParam, lParam);
	};
};