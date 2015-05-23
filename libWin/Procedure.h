#ifndef PROCEDURE_H_
#define PROCEDURE_H_

#include <Windows.h>
#include "Window.h"

namespace Win
{
	typedef LRESULT (CALLBACK * ProcPtr)
		(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	LRESULT CALLBACK Proc
		(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	LRESULT CALLBACK childProc
		(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	LRESULT CALLBACK SubProc
		(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	class CreateData : public CREATESTRUCT
	{
    public:
        void * GetCreationData () const { return lpCreateParams; }
        int GetHeight () const { return cy; }
        int GetWidth () const { return cx; }
        int GetX () const { return x; }
        int GetY () const { return y; }
        char const * GetWndName () const { return lpszName; }
	};
};

#endif