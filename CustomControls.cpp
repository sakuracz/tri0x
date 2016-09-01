#include "CustomControls.h"
#include <sstream>

using std::stringstream;

namespace Win
{
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
		string disable = "res/" + nameBase + "-dis.bmp";
		string hover = "res/" + nameBase + "-over.bmp";
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

		bmapDisabled = ::LoadImage(NULL, disable.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		bmapHover = ::LoadImage(NULL, hover.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	bool CustomButton::Draw(const int& which, DRAWITEMSTRUCT* pDIS)
	{
		RECT rectItem = pDIS->rcItem;
		HDC hDC = pDIS->hDC;
		HANDLE toDraw = NULL;

		switch (which)
		{
		case 3:
			toDraw = bmapDisabled;
			break;
		case 2:
			toDraw = bmapHover;
			break;
		case 1:
			toDraw = bmapPressed;
			break;
		case 0:
			toDraw = bmapDepressed;
			break;
		}

		if (toDraw != NULL){
			RECT rcImage;
			BITMAP bm;
			LONG cxBitmap, cyBitmap;
			if (GetObject(toDraw, sizeof(bm), &bm)){
				cxBitmap = bm.bmWidth;
				cyBitmap = bm.bmHeight;
			}
			CopyRect(&rcImage, &rectItem);
			LONG image_width = rcImage.right - rcImage.left;
			LONG image_height = rcImage.bottom - rcImage.top;
			rcImage.left = (image_width - cxBitmap) / 2;
			rcImage.top = (image_height - cyBitmap) / 2;
			DrawState(hDC, NULL, NULL, (LPARAM)toDraw, 0, rcImage.left, rcImage.top, rcImage.right - rcImage.left, rcImage.bottom - rcImage.top, DSS_NORMAL | DST_BITMAP);
		}

		//	if (which == 0)
		//		::DrawIconEx(hDC, 0, 0, (HICON)bmapPressed, 0, 0, NULL, NULL, DI_NORMAL);
		//	else
		//		::DrawIconEx(hDC, 0, 0, (HICON)bmapDepressed, 0, 0, NULL, NULL, DI_NORMAL);
		return true;
	}

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
		string default = string("res/" + nameBase + "-idle.bmp");
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

	CustomEdit::CustomEdit(HWND win, int id)
		: EditControl(win, id)
	{
	}

	CustomEdit::CustomEdit(HWND win)
		: EditControl(win)
	{}

	void CustomEdit::LoadBMPs(const string& name)
	{
		stringstream stream;
		string bg = string("res/" + name + ".bmp");
		bmapBack = ::LoadImage(NULL, bg.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (bmapBack == NULL){
			DWORD dw = GetLastError();
			stream << "Got error #: " << dw;
			::MessageBox(NULL, stream.str().c_str(), "Nope1", MB_OK);
		}
	}

	CustomRadio::CustomRadio(HWND winParent, int id)
		: SimpleControl(winParent, id)
	{
	};

	CustomRadio::CustomRadio(HWND win)
		: SimpleControl(win)
	{
	};

	void CustomRadio::GetShare(const CustomRadio& shareObj)
	{
		bmapIdle = shareObj.bmapIdle;
		bmapCheck = shareObj.bmapCheck;
		bmapDis = shareObj.bmapDis;
		bmapMask = shareObj.bmapMask;
	}

	void CustomRadio::LoadBMPs(const string& name)
	{
		string main = string("res/" + name + "-idle.bmp");
		string check = string("res/" + name + "-check.bmp");
		string disable = string("res/" + name + "-dis.bmp");
		string mask = string("res/" + name + "-mask.bmp");

		stringstream stream;

		bmapIdle = shared_ptr<HANDLE>((HANDLE*)::LoadImage(NULL, main.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE), [=](HANDLE handle){::DeleteObject(handle); });
		if (bmapIdle.get() == NULL){
			DWORD dw = GetLastError();
			stream << "Got error #: " << dw;
			::MessageBox(NULL, stream.str().c_str(), "No idle bitmap", MB_OK);
		}
		bmapCheck = shared_ptr<HANDLE>((HANDLE*)::LoadImage(NULL, check.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE), [=](HANDLE handle){::DeleteObject(handle); });
		if (bmapCheck.get() == NULL){
			DWORD dw = GetLastError();
			stream = stringstream();
			stream << "Got error #: " << dw;
			-::MessageBox(NULL, stream.str().c_str(), "No checked bitmap", MB_OK);
		}
		bmapDis = shared_ptr<HANDLE>((HANDLE*)::LoadImage(NULL, disable.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE), [=](HANDLE handle){::DeleteObject(handle); });
		if (bmapDis.get() == NULL){
			DWORD dw = GetLastError();
			stream = stringstream();
			stream << "Got error #: " << dw;
			::MessageBox(NULL, stream.str().c_str(), "No disabled bitmap", MB_OK);
		}
		bmapMask = shared_ptr<HANDLE>((HANDLE*)::LoadImage(NULL, mask.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE), [=](HANDLE handle){::DeleteObject(handle); });
		if (bmapMask.get() == NULL){
			DWORD dw = GetLastError();
			stream = stringstream();
			stream << "Got error #: " << dw;
			::MessageBox(NULL, stream.str().c_str(), "No mask bitmap", MB_OK);
		}
	}
}