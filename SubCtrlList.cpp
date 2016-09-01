﻿#include "SubCtrlList.h"
#include <sstream>
#include <string>

using namespace std;

namespace Win
{
	void ListController::Init(HWND hWnd, ProcPtr prevProc, Controller* prevCont, HWND parent)
	{
		SubController::Init(hWnd, prevProc, prevCont);
		parentHWND = parent;		
	}

	bool ListController::OnEraseBG(HDC hdc)
	{

		return true;
	}

	bool ListController::OnMove(WPARAM wParam, LPARAM lParam)
	{
		DWORD x = LOWORD(lParam);
		DWORD y = HIWORD(lParam);
		stringstream ss;
//		ss << " x: " << x << " y: " << y << endl;
//		::MessageBox(NULL, ss.str().c_str(), "Nope", MB_OK);

		return true;
	}

	bool ListController::OnNCCalcSize(WPARAM wParam, LPARAM lParam)
	{
		if (wParam == TRUE){
			NCCALCSIZE_PARAMS* param = (NCCALCSIZE_PARAMS*)lParam;
			RECT parRect;
			HWND parent = ::GetParent(param->lppos->hwnd);
			::GetClientRect(parent, &parRect);

/*			stringstream ss;
			for (int i = 0; i < 3; i++){
				ss << "Left: " << param->rgrc[i].left << " Right: " << param->rgrc[i].right << " Top: " << param->rgrc[i].top << " Bottom: " << param->rgrc[i].bottom << std::endl;
			}
			
			ss << "Flagi: " << std::hex << param->lppos->flags << std::endl;
			::MessageBox(NULL, ss.str().c_str(), "Nope", MB_OK);	*/

//			param->rgrc[0].left = param->rgrc[1].left = param->rgrc[2].left = parRect.left;
//			param->rgrc[0].top = param->rgrc[1].top = param->rgrc[2].top = parRect.bottom;
//			param->rgrc[0].right = param->rgrc[1].right = param->rgrc[2].right = parRect.right;
//			param->rgrc[0].bottom = param->rgrc[1].bottom = param->rgrc[2].bottom = parRect.top+30+90+1;

/*			param->rgrc[2].left--;
			param->rgrc[2].top--;
			param->rgrc[2].right++;
			param->rgrc[2].bottom++;	*/
			
//			stringstream ss;
//			ss << " cy:" << param->lppos->cx << " cy:" << param->lppos->cy << " x: " << param->lppos->x << " y: " << param->lppos->y << endl;
//			ss << " Insert after: " << param->lppos->hwndInsertAfter << " Flags: " << std::hex << param->lppos->flags << endl;
//			::MessageBox(NULL, ss.str().c_str(), "Nope", MB_OK);

		} else {
			::MessageBox(NULL, "OK", "Nope", MB_OK);
		}

		return true;
	}

	bool ListController::OnWindowPosChanging(WPARAM wParam, LPARAM lParam)
	{
		WINDOWPOS* wndPos = (WINDOWPOS*)lParam;		
		RECT parRect;		
		::GetWindowRect(parentHWND, &parRect);
		wndPos->x = parRect.left-1;
		wndPos->y = parRect.bottom - 5;
		wndPos->cx = 136;
		wndPos->cy = 90;		

//		stringstream ss;
//		ss << " cy:" <<wndPos->cx << " cy:" << wndPos->cy << " x: " << wndPos->x << " y: " << wndPos->y << endl;
//		ss << " Insert after: " << wndPos->hwndInsertAfter << " Flags: " << std::hex << wndPos->flags << endl;
//		::MessageBox(NULL, ss.str().c_str(), "WindowPosChanging()", MB_OK);

		return true;
	}
}