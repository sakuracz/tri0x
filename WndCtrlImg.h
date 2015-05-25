#ifndef CLASSIMGWNDCONTROLLER_
#define CLASSIMGWNDCONTROLLER_

#include "libWin\ClassChildController.h"
#include "libWin\ClassSerializable.h"

namespace Win
{
	class ImgWndController : public ChildController, public Serializable
	{
	public:
		ImgWndController();
		~ImgWndController();
		bool OnCommand(WPARAM, LPARAM);
		bool OnCreate(CreateData const* data);
		bool OnPaint();
		bool OnMoving(RECT*){return true;}
		bool OnSize(int,int,int);
		void UpdateData(double*, double*, int);
		void Serialize(Serializer &)const;
		void DeSerialize(DeSerializer &){};
	private:		//plot details:
		double _rangeMinFFT;
		double _rangeMaxFFT;
		double _rangeMinX;
		double _rangeMaxX;
		double _rangeMinY;
		double _rangeMaxY;
		double *_dataX;
		double *_dataY;
		double _start;
		double _stop;
		int _size;
		bool _fft;
	protected:
		ButtonControl *_btnArray[2];
	};
};

#endif