#include "struct.h"

void CustomButton::Load(const string& press, const string& dpress)
{
	bmapPressed = ::LoadImage(NULL, press.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmapDepressed = ::LoadImage(NULL, dpress.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

bool CustomButton::Draw(const int& which, HDC hDC)
{
	if (which == 0)
		::DrawIconEx(hDC, 0, 0, (HICON)bmapPressed, 0, 0, NULL, NULL, DI_NORMAL);
	else
		::DrawIconEx(hDC, 0, 0, (HICON)bmapDepressed, 0, 0, NULL, NULL, DI_NORMAL);
	return true;
}