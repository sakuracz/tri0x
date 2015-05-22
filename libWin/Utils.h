#ifndef UTILS_H_
#define UTILS_H_

#include <Windows.h>

namespace Win
{
	template <class T>
	inline T GetLong(HWND win, int which = GWL_USERDATA)
	{
		return reinterpret_cast<T>(::GetWindowLong(win, which));
	}

	template <class T>
	inline void SetLong(HWND win, T value, int which = GWL_USERDATA)
	{
		::SetWindowLong(win, which, reinterpret_cast<long>(value));
	}
};

#endif