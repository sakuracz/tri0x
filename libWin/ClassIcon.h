#ifndef CLASSICON_H_
#define CLASSICON_H_

#include <Windows.h>

class CIcon
{
public:
	CIcon(HINSTANCE res, int id, int dx = 0, int dy = 0, unsigned flag = LR_DEFAULTCOLOR)
	{
		Load(res, id, dx, dy, flag);
	}
	~CIcon();
	operator HICON() const {return _h;}
protected:
	CIcon():_h(0){};
	void Load(HINSTANCE res, int id, int dx = 0, int dy = 0, unsigned flag = LR_DEFAULTCOLOR);
protected:
	HICON _h;
};

class CSmallIcon : public CIcon
{
public:
	CSmallIcon(){};
	CSmallIcon(HINSTANCE res, int id);
	void Load(HINSTANCE res, int id);
};

class CStdIcon : public CIcon
{
public:
	CStdIcon(){};
	CStdIcon(HINSTANCE res, int id);
	void Load(HINSTANCE res, int id);
};

#endif