#include "struct.h"
#include <sstream>

using namespace std;

CustomButton::~CustomButton()
{
	DeleteObject(bmapPressed);
	DeleteObject(bmapDepressed);
}

void CustomButton::Load(const string& press, const string& dpress)
{
	stringstream stream;
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