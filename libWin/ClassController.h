#ifndef CLASSCONTROLLER_H_
#define CLASSCONTROLLER_H_

#include "View.h"
#include <Windows.h>
#include "Procedure.h"
#include "WindowControls.h"
#include <memory>

namespace Win
{
	class Controller
	{
		friend LRESULT CALLBACK Procedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	public:		
		Controller();
		Controller(HWND, CreateData*);
		~Controller();
//		virtual bool OnDestroy(){return false;}
		virtual bool OnCommand(WPARAM, LPARAM){return false;}
		virtual bool OnChar(){return false;}
		virtual bool OnCreate(CreateData const *);	
		virtual bool OnKeyDown(WPARAM, LPARAM){return false;}
		virtual bool OnLMouseButtonUp(){return false;}
		virtual bool OnPaint(){return false;}
		virtual bool OnSize(int width, int height, int flag){return false;}
		virtual bool OnSizing(RECT*){return false;}
		virtual HRESULT OnCTLColorStatic(HDC, HWND){return false;}
		virtual HRESULT OnCTLColorBtn(HDC, HWND){return false;}
		virtual bool OnMaxMinInfo(MINMAXINFO*){return false;}
		virtual bool OnNotify(HWND, LPARAM){return false;}
	protected:
		Dow _hwnd;
		void SetWindowHandle(HWND wind){_hwnd.Init(wind);}
	};
};

#endif