// (Win::)Dow class definition

#ifndef WINDOW_H_
#define WINDOW_H_

#include <windows.h>
#include <cassert>
//#include "ClassController.h"

namespace Win
{
	class SubController;

	template <class T>
	inline T GetLong(HWND hwnd, int which = GWL_USERDATA)
	{
		return reinterpret_cast<T> ( ::GetWindowLong(hwnd, which));
	}
	template <class T>
	inline void SetLong(HWND hwnd, T value, int which = GWL_USERDATA)
	{
		::SetWindowLong(hwnd, which, reinterpret_cast<long>(value));
	}

	class Dow
	{
	public:
		Dow(HWND hwnd)  : _h(hwnd){}
		~Dow(){}
		operator HWND() const	{return _h;}
		void Init(HWND hwnd)	{_h = hwnd;}
		void Show (int cmdShow)
		{			
			::ShowWindow(_h, cmdShow); 			
		};
		void Update()
		{
			::UpdateWindow(_h);
		}
		HINSTANCE GetInstance() const
		{
			return reinterpret_cast<HINSTANCE>(::GetWindowLong(_h, GWL_HINSTANCE));
		}
		HWND GetParent() const
		{
			return ::GetParent(_h);
		}

		LRESULT SendMessage(UINT msg, WPARAM wParam = 0, LPARAM lParam = 0)
		{
			return ::SendMessage(_h, msg, wParam, lParam);
		};
	
		void SubClass(SubController * ctrl);
		void UnSubClass();
	protected:
		HWND _h;
	};
}

#endif
