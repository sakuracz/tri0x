// ClassMaker class definition
// ChildClassMaker class definition

#ifndef WINCLASSMAKER_H_
#define WINCLASSMAKER_H_

#include <windows.h>
#include <iostream>
#include "ClassIcon.h"

namespace Win 
{
	class ClassMaker : public WNDCLASSEX
	{
	public:
		ClassMaker	(WNDPROC WinProcedure, char const * className, HINSTANCE hInst);		
		void Register();
		void SetIcons(int id);
	protected:
		CStdIcon _stdIcon;
		CSmallIcon _smallIcon;
	};

	class ChildClassMaker : public ClassMaker
	{
	public:
		ChildClassMaker(WNDPROC WinProcedure, char const * className, HINSTANCE hInst);
	};
};

#endif