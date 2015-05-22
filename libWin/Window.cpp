#include "Window.h"
#include "Procedure.h"
#include "ClassController.h"
#include "ClassControllerSub.h"

namespace Win
{
	void Dow::SubClass(SubController* subCtrl)
	{
		ProcPtr prevProc = GetLong<ProcPtr>(_h, GWL_WNDPROC);
		Controller* prevCtrl = GetLong<Controller*>(_h);

		subCtrl->Init(_h, prevProc, prevCtrl);

		SetLong<Controller*>(_h, subCtrl);
		SetLong<ProcPtr>(_h, SubProc, GWL_WNDPROC);
	};

	void Dow::UnSubClass()
	{
		SubController * pCtrl = GetLong<SubController*>(_h);

		SetLong<ProcPtr>(_h, pCtrl->GetPrevProc(), GWL_WNDPROC);
		SetLong<Controller*>(_h, pCtrl->GetPrevController());
	};
};