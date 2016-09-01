#ifndef SUBCONTROLLERRADIO_H_
#define SUBCONTROLLERRADIO_H_

#include "libWin/ClassControllerSub.h"
#include "CustomControls.h"

namespace Win
{
	class RadioController : public SubController
	{
	public:
		RadioController(CustomRadio&);
		bool OnPaint() override;
		bool OnLMouseButtonUp(WPARAM, LPARAM) override;
	private:
		CustomRadio& radio;
	};
}

#endif
