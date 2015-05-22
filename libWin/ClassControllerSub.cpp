//SubController class implementation

#include "ClassControllerSub.h"

namespace Win
{
	SubController::SubController() : _prevProc(0), _prevController(0)
	{};

	void SubController::Init(HWND win, ProcPtr prevProc, Controller * prevCtrl)
	{
		SetWindowHandle(win);
		_prevProc = prevProc;
		_prevController = prevCtrl;
	};

	LRESULT SubController::CallPrevProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		return ::CallWindowProc(_prevProc, _hwnd, message, wParam, lParam);
	};

	ProcPtr SubController::GetPrevProc()
	{
		return _prevProc;
	};

	Controller* SubController::GetPrevController()
	{
		return _prevController;
	};
};