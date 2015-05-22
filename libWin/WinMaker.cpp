#include <windows.h>
#include "Window.h"
#include "WinMaker.h"
#include <sstream>


namespace Win
{
	Maker::Maker	(char const * className, HINSTANCE hInst)
		:	_hwnd(0),
			_style(WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN),
			_exStyle(WS_EX_APPWINDOW),
			_className(className),
			_x(CW_USEDEFAULT),
			_y(CW_USEDEFAULT),
			_width(CW_USEDEFAULT),
			_height(CW_USEDEFAULT),
			_hWndParent(0),
			_hMenu(0),
			_data(0),
			_hInst(hInst)
	{};

	void Maker::Create(char const * title)
	{
		_wndName = title;
		_hwnd = ::CreateWindowEx	(
			_exStyle,
			_className,
			_wndName,
			_style,
			_x,
			_y,
			_width,
			_height,
			_hWndParent,
			_hMenu,
			_hInst,
			_data);
		if(_hwnd == 0)
			throw "Window Creation Failed!";
		return;
	};

	void Maker::Show(int cmdShow)
	{
		_hwnd.Show(cmdShow);
		_hwnd.Update();
	}

	ChildMaker::ChildMaker(char const * className, Dow winParent, int ChildId, Controller & controller)
		:Maker(className, winParent.GetInstance()), _id(ChildId)
	{
		_hInst = winParent.GetInstance();
		_exStyle = 0;
		_style = WS_CHILD | WS_VISIBLE | WS_CAPTION| WS_CLIPSIBLINGS | WS_SIZEBOX;				
		_hWndParent = winParent;
		_x = 50;
		_y = 50;
		_width = 300;
		_height = 300;
		_hMenu = (HMENU)ChildId;
		_data = &controller;
	};

	ChildMaker::ChildMaker(char const * className, Dow winParent, int childId)
		: Maker(className, winParent.GetInstance()), _id(childId)
	{
		_hInst = winParent.GetInstance();
		_exStyle = 0;
		_style = WS_CHILD | WS_VISIBLE | WS_CAPTION | WS_CLIPSIBLINGS | WS_SIZEBOX;				
		_hWndParent = winParent;
		_x = 50;
		_y = 50;
		_width = 300;
		_height = 300;
		_hMenu = (HMENU)childId;
		_data = NULL;
	}

	ControlMaker::ControlMaker(char const * className, Dow winParent, int id)
		: ChildMaker(className,  winParent, id)
	{
		_exStyle = WS_EX_CLIENTEDGE;
		_style = WS_CHILD | WS_VISIBLE;
	};

	ButtonMaker::ButtonMaker(HWND winParent, int id)
		: ControlMaker("BUTTON", winParent, id)
	{
		_exStyle = 0;
	};

	ComboMaker::ComboMaker(HWND winParent, int id)
		: ControlMaker(WC_COMBOBOX, winParent, id)
	{
		_style |= CBS_DROPDOWN;
	};

	EditMaker::EditMaker(HWND winParent, int id)
		: ControlMaker("EDIT", winParent, id)
	{};

	ListViewMaker::ListViewMaker(HWND winParent, int id)
		: ControlMaker(WC_LISTVIEW, winParent, id)
	{
		_icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		_icex.dwICC = ICC_LISTVIEW_CLASSES;
		::InitCommonControlsEx(&_icex);

		_style = WS_CHILD | LVS_REPORT | LVS_SINGLESEL;
		_exStyle |= LVS_EX_FULLROWSELECT;
	};

	void StaticMaker::NoBG()
	{
		_exStyle = 0;
	};

	TabMaker::TabMaker(HWND winParent, int id)
		: ControlMaker(WC_TABCONTROL, winParent, id)
	{
		_icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		_icex.dwICC = ICC_TAB_CLASSES | ICC_STANDARD_CLASSES;
		::InitCommonControlsEx(&_icex);

		_style = WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | TCS_MULTILINE;
		_exStyle = 0;

		_tie.mask = TCIF_TEXT | TCIF_IMAGE;
		_tie.iImage = -1;
		_tie.pszText = "chuje";

	};

	void TabMaker::Create(char const* title)
	{
		std::string names[2];
		names[0] = "Settings";
		names[1] = "Movement";
		Maker::Create(title); 
		for(int i = 0; i < 2; i++)
		{
			int j = 2002 + i;
			std::stringstream stream;
			std::string string;

			stream << names[i];
			string = stream.str();

			_tie.pszText = (LPSTR)string.c_str();
			TabCtrl_InsertItem(_hwnd, j, &_tie);
		}
	};

	void TabMaker::CreateTwoTabs(char const* tabOne, char const* tabTwo)
	{
		std::string names[2] = {tabOne, tabTwo};
	//	names[0] = "Settings";
	//	names[1] = "Movement";
		Maker::Create(tabOne); 
		for(int i = 0; i < 2; i++)
		{
			int j = 2002 + i;
			std::stringstream stream;
			std::string string;

			stream << names[i];
			string = stream.str();

			_tie.pszText = (LPSTR)string.c_str();
			TabCtrl_InsertItem(_hwnd, j, &_tie);
		}
		return;
	};

	TreeViewMaker::TreeViewMaker(HWND winParent, int id)
		: ControlMaker(WC_TREEVIEW, winParent, id)
	{
		_exStyle = 0;
		_style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT;
	};
};