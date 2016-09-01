#ifndef COMBOSUBCONTROLLER_H_
#define COMBOSUBCONTROLLER_H_

#include <memory>
#include "libWin\ClassControllerSub.h"
#include "SubCtrlList.h"

using std::unique_ptr;

namespace Win
{
	class ComboController : public SubController
	{
	public:
		friend class ListController;
		ComboController(CustomCombo&);
		~ComboController();
		void Invalidate();
		void SubList();
	private:		
		bool OnPaint() override;		
		CustomCombo& combo;
		const unique_ptr<ListController> sublist_controller;
		COMBOBOXINFO comboInfo;
	};
}

#endif