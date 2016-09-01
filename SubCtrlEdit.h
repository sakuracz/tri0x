#ifndef EDITSUBCONTROLLER_H_
#define EDITSUBCONTROLLER_H_

#include "libWin\ClassControllerSub.h"

namespace Win
{
	class EditController : public SubController
	{
	public:		
		EditController(CustomEdit& edit);
		HRESULT OnCTLColorEdit(HDC, HWND) override;
		HRESULT OnCTLColorStatic(HDC, HWND) override;
		bool OnLMouseButtonDown(WPARAM, LPARAM);
		bool OnKeyDown(WPARAM, LPARAM);		
		bool OnEraseBG(HDC) override;
		bool OnKillFocus(WPARAM, LPARAM) override;
		bool OnLMouseDblClick() override;		
	private:
		CustomEdit& edit;
	};
};

#endif