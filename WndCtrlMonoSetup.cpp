#include "WndCtrlMonoSetup.h"
#include "libWin\WinMaker.h"

namespace Win{
	MonoWndCtrl::MonoWndCtrl()
	{
		itemIndex = 0;
		_comboOpts = nullptr;
		_btnSelect = nullptr;
	}

	bool MonoWndCtrl::OnNotify(HWND hFrom, LPARAM lParam)
	{

		return true;
	}

	bool MonoWndCtrl::OnSize(int width, int height, int flag)
	{

		return true;
	}

	bool MonoWndCtrl::OnCommand(WPARAM wParam, LPARAM lParam)
	{

		return true;
	}

	bool MonoWndCtrl::OnCreate(CreateData const* create)
	{

		return true;
	}
};