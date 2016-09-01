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

	EditControl::EditControl(HWND winParent, int id)
		: SimpleControl(winParent, id)
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

	void EditControl::SetText(char * buf, int len)
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
	CustomButton::~CustomButton()
	{
		DeleteObject(bmapPressed);
		DeleteObject(bmapDepressed);
	}

	void CustomButton::LoadBMPs(const string& nameBase)
	{
		stringstream stream;
		string press = nameBase + "-on.bmp";
		string dpress = nameBase + "-off.bmp";
		bmapPressed = ::LoadImage(NULL, press.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (bmapPressed == NULL){
			DWORD dw = GetLastError();
			stream << "Got error #: " << dw;
			::MessageBox(NULL, stream.str().c_str(), "Nope1", MB_OK);
		}
		bmapDepressed = ::LoadImage(NULL, dpress.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (bmapDepressed == NULL){
			DWORD dw = GetLastError();
			stream = stringstream();
			stream << "Got error #: " << dw;
			::MessageBox(NULL, stream.str().c_str(), "Nope2", MB_OK);
		}
	}

	bool CustomButton::Draw(const int& which, DRAWITEMSTRUCT* pDIS)
	{
		RECT rectItem = pDIS->rcItem;
		HDC hDC = pDIS->hDC;

		if (which == 0){
			if (bmapPressed != NULL){
				RECT rcImage;
				BITMAP bm;
				LONG cxBitmap, cyBitmap;
				if (GetObject(bmapPressed, sizeof(bm), &bm)){
					cxBitmap = bm.bmWidth;
					cyBitmap = bm.bmHeight;
				}
				CopyRect(&rcImage, &rectItem);
				LONG image_width = rcImage.right - rcImage.left;
				LONG image_height = rcImage.bottom - rcImage.top;
				rcImage.left = (image_width - cxBitmap) / 2;
				rcImage.top = (image_height - cyBitmap) / 2;
				DrawState(hDC, NULL, NULL, (LPARAM)bmapPressed, 0, rcImage.left, rcImage.top, rcImage.right - rcImage.left, rcImage.bottom - rcImage.top, DSS_NORMAL | DST_BITMAP);
			}
		}
		else {
			if (bmapPressed != NULL){
				RECT rcImage;
				BITMAP bm;
				LONG cxBitmap, cyBitmap;
				if (GetObject(bmapPressed, sizeof(bm), &bm)){
					cxBitmap = bm.bmWidth;
					cyBitmap = bm.bmHeight;
				}
				CopyRect(&rcImage, &rectItem);
				LONG image_width = rcImage.right - rcImage.left;
				LONG image_height = rcImage.bottom - rcImage.top;
				rcImage.left = (image_width - cxBitmap) / 2;
				rcImage.top = (image_height - cyBitmap) / 2;
				DrawState(hDC, NULL, NULL, (LPARAM)bmapDepressed, 0, rcImage.left, rcImage.top, rcImage.right - rcImage.left, rcImage.bottom - rcImage.top, DSS_NORMAL | DST_BITMAP);
			}
		}
		//	if (which == 0)
		//		::DrawIconEx(hDC, 0, 0, (HICON)bmapPressed, 0, 0, NULL, NULL, DI_NORMAL);
		//	else
		//		::DrawIconEx(hDC, 0, 0, (HICON)bmapDepressed, 0, 0, NULL, NULL, DI_NORMAL);
		return true;
	}

	void ButtonControl::SetText(char const* text)
	{
		::SendMessage(_h, WM_SETTEXT, 0, (LPARAM)text);
	};

	ComboControl::ComboControl(HWND winParent)
		: SimpleControl(winParent)
	{};

	ComboControl::ComboControl(HWND winParent, int id)
		: SimpleControl(winParent, id)
	{};

	ListViewControl::ListViewControl(HWND winParent)
		: SimpleControl(winParent)
	{};

	ListViewControl::ListViewControl(HWND winParent, int id)
		: SimpleControl(winParent, id)
	{};

	bool ListViewControl::InsertTwoColumnValues(char const *col1, char const *col2)
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