//Defines classes:
//Maker => ChildMaker => ControlMaker => EditMaker
//Maker => ChildMaker => ControlMaker => StaticMaker

#ifndef WINMAKER_H_
#define WINMAKER_H_

#include <Windows.h>
#include "Window.h"
#include "ClassController.h"
#include <CommCtrl.h>

namespace Win
{
	class Maker
	{
	public:
		Maker(char const * className, HINSTANCE hInst);		
		void Create(char const * title);	
		void Show(int cmdShow = SW_SHOWNORMAL );
		void SetStyle(DWORD style){_style |= style;}
		operator HWND() {return _hwnd;}
	protected:
		Dow	_hwnd;
	protected:
		HINSTANCE		_hInst;
		char const*		_className;
		char const*		_wndName;
		DWORD			_style;
		DWORD			_exStyle;
		int				_x;
		int				_y;
		int				_width;
		int				_height;
		HWND			_hWndParent;
		HMENU			_hMenu;
		void *			_data;
	};

	class ChildMaker : public Maker
	{
	public:
		ChildMaker(char const * className, Dow winParent, int childId, Controller & controller);		
		ChildMaker(char const * className, Dow winParent, int childId);
		void Create(char const * text = ""){Maker::Create(text);};
		void AddStyle(int style){_style |= style;}
		void AddExStyle(int style){_exStyle |= style;}
	protected:
		int _id;
	};

	class ControlMaker : public ChildMaker
	{
	public:
		ControlMaker(char const *, Dow, int);
	};

	class EditMaker: public ControlMaker
	{
	public:
		EditMaker (HWND, int);
		void MakeReadOnly () { _style |= ES_READONLY; }
		void SetPosSize(int x, int y, int w, int h) {_x = x; _y = y; _width = w; _height = h;}
		void WantReturn () { _style |= ES_WANTRETURN; }
		void MultiLine() {_style |= ES_MULTILINE | ES_AUTOVSCROLL; }
	};

	class StaticMaker : public ControlMaker
	{
	public:
		StaticMaker(HWND winParent, int id) : ControlMaker("STATIC", winParent, id){}		
		void NoBG();	
	};

	class ButtonMaker : public ControlMaker
	{
	public:
		ButtonMaker(HWND, int);		
	};

	class ComboMaker : public ControlMaker
	{
	public:
		ComboMaker(HWND, int);
	};

	class ListViewMaker : public ControlMaker
	{
	public:
		ListViewMaker(HWND, int);
	private:
		INITCOMMONCONTROLSEX _icex;
	};

	class TabMaker : public ControlMaker
	{
	public:
		TabMaker(HWND, int);
		void Create(char const*);
		void CreateTwoTabs(char const *, char const *);
	private:
		INITCOMMONCONTROLSEX _icex;
		TCITEM _tie;
	};

	class TreeViewMaker : public ControlMaker
	{
	public:
		TreeViewMaker(HWND, int);
	};
};

#endif _WinMaker