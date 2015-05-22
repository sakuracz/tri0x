#include "ClassChildController.h"

namespace Win
{
	ChildController::ChildController()
		: Controller()
	{};

	void ChildController::InitMinXY(int X, int Y)
	{
		_minX = X;
		_minY = Y;
		return;
	};

	bool ChildController::OnSizing(RECT *pRect)
	{
		int width = pRect->right - pRect->left;
		int height = pRect->bottom - pRect->top;

		if(width <= _minX)
			pRect->right = pRect->left+_minX;
		if(height <= _minY)
			pRect->bottom = pRect->top+_minY;

		return true;
	};
}