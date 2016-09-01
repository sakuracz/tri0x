#include "struct.h"
#include <sstream>

using namespace std;

void CustomButton::Load(const string& press, const string& dpress)
{
	stringstream stream;
	bmapPressed = ::LoadImage(NULL, press.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//	if (bmapPressed == NULL){
//		stream << "Got error #: " << GetLastError();
//		::MessageBox(NULL, "Nope1", stream.str().c_str(), MB_OK);
//	}
	bmapDepressed = ::LoadImage(NULL, dpress.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (bmapDepressed == NULL){
		DWORD dw = GetLastError();
		stream = stringstream();
		stream << "Got error #: " << dw;
		::MessageBox(NULL, "Nope2", "Nope2", MB_OK);
	}
}

bool CustomButton::Draw(const int& which, HDC hDC)
{
	if (which == 0)
		::DrawIconEx(hDC, 0, 0, (HICON)bmapDepressed, 0, 0, NULL, NULL, DI_NORMAL);
	else
		::DrawIconEx(hDC, 0, 0, (HICON)bmapDepressed, 0, 0, NULL, NULL, DI_NORMAL);
	return true;
}