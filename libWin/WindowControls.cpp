// SimpleControl class implementation
// EditControl class implementation
// StaticControl class implementation
// ButtonControl class implementation
// ListViewControl class implementation
// ComboControl class implementation

#include "WindowControls.h"
#include <string>
#include <sstream>

using std::string;
using std::stringstream;

namespace Win
{
	SimpleControl::SimpleControl(HWND winParent, int id)
		: Dow(::GetDlgItem(winParent, id)), _id(id)
	{};

	SimpleControl::SimpleControl(HWND win = 0)
		: Dow(win), _id(0)
	{};

	void SimpleControl::Init(HWND win, int id)
	{
		_h = win;
		_id = id;
	};

	void SimpleControl::Init(HWND win)
	{
		Dow::Init(win);
		_id = 0;
	};

	bool SimpleControl::IsClicked(int code)
	{
		return code == BN_CLICKED;
	};

	int SimpleControl::GetId() const
	{
		return _id;
	};

	EditControl::EditControl(HWND win, int id)
		: SimpleControl(win, id)
	{};

	EditControl::EditControl(HWND win = 0)
		: SimpleControl(win)
	{};

	void EditControl::Append(char const* buf)
	{
		int len = GetLen();
		Select(len, -1);
		SendMessage(EM_REPLACESEL, 0, reinterpret_cast<LPARAM>(buf));
	};

	void EditControl::Select(int offStart, int offStop)
	{
		SendMessage(EM_SETSEL, (WPARAM) offStart, (LPARAM)offStop);
	};

	void EditControl::SetReadOnly(bool flag)
	{
		SendMessage(EM_SETREADONLY, (WPARAM) (flag ? TRUE : FALSE), 0);
	};

	bool EditControl::IsChanged(int code)
	{
		return code == EN_CHANGE;
	};

	int EditControl::GetLen()
	{
		return SendMessage(WM_GETTEXTLENGTH);
	};

	void EditControl::SetText(char * buf, int)
	{
		SendMessage (WM_SETTEXT, 0, (LPARAM) buf);
	};

	StaticControl::StaticControl(HWND winParent, int id)
		: SimpleControl(winParent, id)
	{};

	StaticControl::StaticControl(HWND win = 0)
		: SimpleControl(win)
	{};

	ButtonControl::ButtonControl(HWND winParent, int id)
		: SimpleControl(winParent, id)
	{};

	ButtonControl::ButtonControl(HWND win)
		: SimpleControl(win)
	{};

	void ButtonControl::SetText(char const* text)
	{
		::SendMessage(_h, WM_SETTEXT, 0, (LPARAM)text);
	};

	ComboControl::ComboControl(HWND win)
		: SimpleControl(win)
	{		
	};

	ComboControl::ComboControl(HWND winParent, int id)
		: SimpleControl(winParent, id)
	{};	

	ListViewControl::ListViewControl(HWND winParent)
		: SimpleControl(winParent)
	{};

	ListViewControl::ListViewControl(HWND winParent, int id)
		: SimpleControl(winParent, id)
	{};

	bool ListViewControl::InsertTwoColumnValues(char const *, char const *)
	{

		return true;
	};

	TabControl::TabControl(HWND winParent, int id)
		: SimpleControl(winParent, id)
	{};

	TabControl::TabControl(HWND winParent = 0)
		: SimpleControl(winParent)
	{};

	TreeViewControl::TreeViewControl(HWND winParent, int id)
		: SimpleControl(winParent, id)
	{};

	TreeViewControl::TreeViewControl(HWND winParent)
		: SimpleControl(winParent)
	{};
}