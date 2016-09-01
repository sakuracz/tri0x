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
		string press = "res/" + nameBase + "-on.bmp";
		string dpress = "res/" + nameBase + "-off.bmp";
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

	ComboControl::ComboControl(HWND win)
		: SimpleControl(win)
	{		
	};

	ComboControl::ComboControl(HWND winParent, int id)
		: SimpleControl(winParent, id)
	{};

	CustomCombo::~CustomCombo()
	{
		for (auto i = header_bmaps.begin(); i != header_bmaps.end(); i++)
			::DeleteObject(*i);
		for (auto i = footer_bmaps.begin(); i != footer_bmaps.end(); i++)
			::DeleteObject(*i);
		for (auto i = hover_bmaps.begin(); i != hover_bmaps.end(); i++)
			::DeleteObject(*i);
		for (auto i = idle_bmaps.begin(); i != idle_bmaps.end(); i++)
			::DeleteObject(*i);
		::DeleteObject(font);
	}

	void CustomCombo::Load(const string& nameBase, const vector<string>& itemNames, const RECT& coords)
	{				
		idle.top = selecting.top = selected.top = coords.top;
		idle.left = selecting.left = selected.left = coords.left;

		//load header bitmaps:		
		header_bmaps = vector<HANDLE>();
		BITMAP bm;
		string default = string("res/"+nameBase + "-idle.bmp");		
		HANDLE tempBMP = ::LoadImage(NULL, default.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (::GetObject(tempBMP, sizeof(bm), &bm)){
			idle.bottom = idle.top + bm.bmHeight;
			idle.right = idle.left + bm.bmWidth;
			selecting.right = selected.right = idle.right;
			header_bmaps.push_back(tempBMP);
		}
		else {
			::MessageBox(NULL, "GetObject() failed", "CustomControl::Load error", MB_OK | MB_ICONERROR);
		}
		default = string("res/" + nameBase + "-selected.bmp");
		tempBMP = ::LoadImage(NULL, default.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (::GetObject(tempBMP, sizeof(bm), &bm)){
			header_bmaps.push_back(tempBMP);
		}
		else {
			::MessageBox(NULL, "GetObject() failed", "CustomControl::Load error", MB_OK | MB_ICONERROR);
		}	
		default = string("res/" + nameBase + "-selecting.bmp");
		tempBMP = ::LoadImage(NULL, default.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (::GetObject(tempBMP, sizeof(bm), &bm)){
			header_bmaps.push_back(tempBMP);
		}
		else {
			::MessageBox(NULL, "GetObject() failed", "CustomControl::Load error", MB_OK | MB_ICONERROR);
		}

		//load the rest of the bitmaps:
		footer_bmaps = vector<HANDLE>();
		hover_bmaps = vector<HANDLE>();
		idle_bmaps = vector<HANDLE>();
		for (auto i = itemNames.begin(); i != itemNames.end(); i++){
			string idle = string("res/" + nameBase + "-" + *i + "-idle.bmp");
			string hover = string("res/" + nameBase + "-" + *i + "-hover.bmp");
			string item = string("res/" + nameBase + "-" + *i + "-item.bmp");
			footer_bmaps.push_back(::LoadImage(NULL, idle.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
			hover_bmaps.push_back(::LoadImage(NULL, hover.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
			idle_bmaps.push_back(::LoadImage(NULL, item.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		}

		for (auto i = itemNames.begin(); i != itemNames.end(); i++){
			items.push_back(*i);
		}

		selecting.bottom = idle.bottom + items.size()*bm.bmHeight;
		selected.bottom = idle.bottom + bm.bmHeight;

		font = CreateFont(1, 0, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact"));		
		::SendMessage(_h, WM_SETFONT, (WPARAM)font, TRUE);
	};

	bool CustomCombo::Draw(const int& item, DRAWITEMSTRUCT* pDIS)
	{
		RECT rectItem = pDIS->rcItem;
		HDC hDC = pDIS->hDC;
//		HDC hdc = GetDC(_h);

/*		stringstream sss;
		sss << "Top: " << rectItem.top << " Bottom: " << rectItem.bottom << " Left: " << rectItem.left << " Right: " << rectItem.right << std::endl;
		sss << "Item: " << item << " itemId: " << pDIS->itemID << " CtlType: " << std::hex << pDIS->CtlType << " itemState: " << std::hex << pDIS->itemState << std::endl;
		sss << "ItemAction: " << std::hex << pDIS->itemAction << std::endl;
		::MessageBox(NULL, sss.str().c_str(), "H", MB_OK);
*/		
	
		HDC compHDC = ::CreateCompatibleDC(hDC);
		if (compHDC == NULL)
			::MessageBox(NULL, "::CreateCompatibleDC returned NULL", "Error in CustomCombo::Draw", MB_OK);

		if (pDIS->itemID == -1)		//empty item
			return false;

		HBITMAP bm;
		if (pDIS->itemState & ODS_FOCUS)
		{
			bm = (HBITMAP)hover_bmaps[item];
			::SelectObject(compHDC, bm);			
		}			
		else 
		{
			bm = (HBITMAP)idle_bmaps[item];
			::SelectObject(compHDC, bm);			
		}

		::BitBlt(pDIS->hDC, pDIS->rcItem.left, pDIS->rcItem.top, 136, 30, compHDC, 0, 0, SRCCOPY);
		::DeleteDC(compHDC);

		return true;			
	}

	void CustomCombo::Fill()
	{		
		for (unsigned int i = 0; i < items.size(); i++){
			::SendMessage(_h, CB_ADDSTRING, i, (LPARAM)items[i].c_str());
		}
	}

	void CustomCombo::ToggleSelected()
	{		
		if (!isSelected){
			isSelected = true;
		}
	}

	void CustomCombo::ToggleSelecting()
	{
		isBeingSelected = !isBeingSelected;
	}

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