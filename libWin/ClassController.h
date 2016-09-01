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
		virtual bool OnHotKey(WPARAM, LPARAM) = 0;
		virtual bool OnNotify(HWND, LPARAM) = 0;
		virtual bool OnChar(){return false;}
		virtual bool OnCreate(CreateData const *);	
		virtual bool OnKeyDown(WPARAM, LPARAM){return false;}
		virtual bool OnLMouseButtonUp(WPARAM, LPARAM) = 0;
		virtual bool OnLMouseButtonDown(WPARAM, LPARAM) = 0;
		virtual bool OnLMouseDblClick() = 0;
		virtual bool OnPaint(){return false;}
		virtual bool OnSize(int width, int height, int flag){return false;}
		virtual bool OnSizing(RECT*){return false;}
		virtual bool OnMove(WPARAM, LPARAM) = 0;
		virtual bool OnNCCalcSize(WPARAM, LPARAM) = 0;
		virtual bool OnNCPaint(WPARAM, LPARAM) = 0;
		virtual bool OnWindowPosChanging(WPARAM, LPARAM) = 0;
		virtual HRESULT OnCTLColorEdit(HDC, HWND) = 0;
		virtual HRESULT OnCTLColorStatic(HDC, HWND){return false;}
		virtual HRESULT OnCTLColorBtn(HDC, HWND){return false;}		
		virtual HRESULT OnCTLColorListBox(HDC, HWND) = 0;
		virtual bool OnMeasureItem(WPARAM, LPARAM){ return false; };
		virtual bool OnEraseBG(HDC) = 0;
		virtual bool OnMaxMinInfo(MINMAXINFO*){return false;}		
	protected:
		Dow _hwnd;
		void SetWindowHandle(HWND wind){_hwnd.Init(wind);}
	};
};

#endif