#include "ClassIcon.h"

void CIcon::Load(HINSTANCE res, int id, int dx, int dy, unsigned flag)
{
	_h = reinterpret_cast<HICON>(
		::LoadImage(res, MAKEINTRESOURCE(id), IMAGE_ICON, dx, dy, flag));
	if(_h == 0)
		throw "Icon load image failed";
};

CIcon::~CIcon()
{

};

void CSmallIcon::Load(HINSTANCE res, int id)
{
	CIcon::Load(res, id, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
};

void CStdIcon::Load(HINSTANCE res, int id)
{
	CIcon::Load(res, id, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
};