#include "WndCtrlImg.h"
#include "libWin\WinMaker.h"
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <mgl2/mgl.h>

#define NODATA_					//NODATA - genarate gaussian data; NODATA_ - data read from lock-in

namespace Win
{
	ImgWndController::ImgWndController()
	{
		InitMinXY(640, 480);
		_dataX = NULL;
		_dataY = NULL;
		_size = 0;
		_rangeMinY = 100;
		_rangeMaxY = -100;

		_rangeMinFFT = 0;
		_rangeMaxFFT = 19980363866666.6666666666;
		_fft = false;		

		for(int i = 0; i < 2; i++){
			_btnArray[i] = new ButtonControl(0);
		}
	};

	ImgWndController::~ImgWndController()
	{
		delete []_dataX;
		delete []_dataY;
	};

	bool ImgWndController::OnCommand(WPARAM wParam, LPARAM lParam)
	{
		switch(LOWORD(wParam))
		{
		case 4300:		// 'Save' button			
		if(HIWORD(wParam) == BN_CLICKED)
			{
				OPENFILENAME ofn;
				TCHAR szFile[MAX_PATH];
				
				szFile[0] = '\0';
				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = _hwnd;
				ofn.lpstrFile = szFile;
				ofn.nMaxFile = MAX_PATH;
				ofn.lpstrFilter = "Text file (*.txt)\0*.txt\0Portable network graphics (*.png)\0*.png\0\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;		
				ofn.lpstrTitle = "Save as\0";
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST;
				if(GetSaveFileName(&ofn)==TRUE)
				{
					try
					{
						if(ofn.nFilterIndex == 2){		//png
							std::string fileName(ofn.lpstrFile);
							fileName += ".png";

							mglData data(_dataY, _size);
							mglGraph gr(0, 1280, 800);
	//						gr.Title("Main plot");
							gr.SetRange('x', _rangeMinX, _rangeMaxX);
							gr.SetRange('y', _rangeMinY, _rangeMaxY);
	
							gr.Axis();
	 						gr.Box();
							gr.Plot(data);

							gr.WritePNG(fileName.c_str());
						} else {
							std::string fileName(ofn.lpstrFile);
							fileName += ".txt";
							Serializer out(fileName);
							Serialize(out);
						}
					}
					catch(char *msg)
					{
						std::stringstream sErr;
						sErr << "Error: Save failed: " << msg << std::endl;
						MessageBox(NULL, sErr.str().c_str(), "Fail", MB_OK);
					}
					catch(...)
					{
						std::stringstream sErr;
						sErr << "Error. Save failed." << std::endl;
						MessageBox(NULL, sErr.str().c_str(), "Fail", MB_OK);
					}
				}
				else
				{					
					DWORD dwError = CommDlgExtendedError();
					if(dwError != 0)			//0 = no error
					{
						std::stringstream sErr;
						sErr << "Encountered error: GetOpenFileName() error#: " << dwError;
						MessageBox(NULL, sErr.str().c_str(), "Error", MB_OK | MB_ICONERROR);
					}
				}
			}
			break;
		case 4301:		// "Split button
			_fft = !_fft;
			::InvalidateRect(_hwnd, NULL, TRUE);
			break;
		}		
		return true;
	};

	bool ImgWndController::OnCreate(CreateData const* data)
	{
		RECT rect;
		::SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
		int maxX = rect.right;
		int maxY = rect.bottom;

		::SetWindowPos(_hwnd, NULL, maxX - _minX, maxY - _minY, _minX, _minY, SWP_SHOWWINDOW);

		for(int i = 0; i < 1; i++){
			int j = 4300 + i;
			ButtonMaker butt(_hwnd, j);
			butt.SetStyle(BS_BITMAP);
			butt.Create("");
			butt.Show();
			_btnArray[i]->Init(butt, j);
		};

		for(int i = 1; i < 2; i++){
			int j = 4300 + i;
			ButtonMaker butt(_hwnd, j);
			butt.SetStyle(BS_BITMAP | BS_PUSHLIKE | BS_AUTOCHECKBOX);
			butt.Create("");
			butt.Show();
			_btnArray[i]->Init(butt, j);
		};

		return true;
	};

	bool ImgWndController::OnPaint()
	{
		if(_size > 0){
			double *fft = new double[_size];

			if(_dataY[_size-1] > _rangeMaxY)
				_rangeMaxY = _dataY[_size-1];
			if(_dataY[_size-1] < _rangeMinY)
				_rangeMinY = _dataY[_size-1];	

#ifdef NODATA
			_rangeMinY = 0;
			_rangeMaxY = 1;
			for(int i = 0; i < _size; i++){
				_dataY[i] = exp((i-_size/2)*(i-_size/2)*-0.002);
			}
#endif

			if(_fft){
				gsl_fft_real_wavetable *real;
				gsl_fft_real_workspace *work;
				real = gsl_fft_real_wavetable_alloc(_size);
				work = gsl_fft_real_workspace_alloc(_size);

				memcpy(fft, _dataY, _size*sizeof(double));
				gsl_fft_real_transform(fft, 1, _size, real, work);				

				gsl_fft_real_workspace_free(work);
			}

			for(int i = 0; i < _size; i++)
				fft[i] = 20*log(abs(fft[i]));

			PAINTSTRUCT paint;
			if(::BeginPaint(_hwnd, &paint) == NULL){
				::MessageBox(NULL, "Begin paint failed", "Error", MB_OK);
				::PostQuitMessage(0);
			}
			::GetClientRect(_hwnd, &paint.rcPaint);
			
			unsigned int width, height;
			width = abs(paint.rcPaint.right-paint.rcPaint.left);
			height = abs(paint.rcPaint.bottom - paint.rcPaint.top);

			mglData data(_dataY, _size);
			mglGraph gr(0, width, height);

			if(_fft){
				mglData fftData(fft, _size);
				gr.SubPlot(1, 2, 0);
				gr.SetRange('x', _dataX[0], _dataX[_size-1]);
				gr.SetRange('y', _rangeMinY, _rangeMaxY);
				gr.SetOrigin(_dataX[_size-1], _rangeMaxY);
				gr.Axis();
	 			gr.Box();
				gr.ColumnPlot(1, 0);
				gr.Plot(data);
				gr.ColumnPlot(1, 1);
//				int xMin = 0, xMax = _size-1;
//				while(fft[xMin] == 0)
//					xMin++;
//				while(fft[xMax] == 0)
//					xMax--;
				double interval;
				if(_size == 0 )
					interval = 1;
				else
					interval = (_dataX[1] - _dataX[0])*0.00000019;
				double tStep = 2*interval/299705458;
				double Fs = 299705458/2/interval;
				gr.SetRange('x', 0, Fs);
				gr.SetRange('y', fftData.Minimal(), fftData.Maximal());
				gr.SetOrigin(0, fftData.Minimal());
				gr.Axis();
	 			gr.Box();
				gr.Plot(fftData);
			} else {
				gr.SubPlot(1, 1, 0);
				gr.SetRange('x', _dataX[0], _dataX[_size-1]);
				gr.SetRange('y', _rangeMinY, _rangeMaxY);
				gr.Axis();
	 			gr.Box();
				gr.ColumnPlot(1, 0);
				gr.Plot(data);
			}
/*			gr.SetRange('x', _dataX[0], _dataX[_size-1]);
			gr.SetRange('y', _rangeMinY, _rangeMaxY);
			gr.Axis();
	 		gr.Box();
			gr.Plot(data);

			if(_fft){
				mglData fftData(fft, _size);
				gr.Plot(fftData);
			}
*/
			HDC mDC = ::CreateCompatibleDC(paint.hdc);
//			HBITMAP bMap = ::CreateCompatibleBitmap(paint.hdc, width, height);
			::SetMapMode(mDC, MM_ISOTROPIC);
			::SetWindowExtEx(mDC, 1, 1, NULL);
			::SetViewportExtEx(mDC, 1, -1, NULL);
			::SetViewportOrgEx(mDC, 0, height-1, NULL);

			unsigned long padding = (4 - (( width*3)%4))%4;
			unsigned long imgSize = height*((width*3)+padding);

			BITMAPINFOHEADER bmpInfo = {0};
			bmpInfo.biSize = sizeof(BITMAPINFOHEADER);
			bmpInfo.biBitCount = 32;
			bmpInfo.biClrImportant = 0;		//use all colors
			bmpInfo.biClrUsed = 0;			//colors used as stated in biBitCount
			bmpInfo.biCompression = BI_RGB;	//no compression
			bmpInfo.biHeight = height;
			bmpInfo.biWidth = width;
			bmpInfo.biPlanes = 1;
			bmpInfo.biSizeImage = imgSize;

			BITMAPINFO nfo;		
			nfo.bmiHeader = bmpInfo;			
//			::SetDIBits(paint.hdc, bMap, 0, height, gr.GetRGBA(), 0, DIB_RGB_COLORS);
			
			HBITMAP bMap = ::CreateDIBitmap(paint.hdc, &bmpInfo, CBM_INIT, gr.GetRGBA(), &nfo, DIB_RGB_COLORS);
//			HBITMAP bMap = ::CreateBitmap(width, height, 1, 32, gr.GetRGBA());

			if(mDC == NULL){
				::MessageBox(NULL, "Failed to create compatible DC", "DC fail", MB_OK);
				::PostQuitMessage(0);
			}
			if(bMap == NULL){
				::MessageBox(NULL, "Failed to create bitmap", "Fail", MB_OK);
				::PostQuitMessage(0);
			}

			HGDIOBJ oldObj = ::SelectObject(mDC, bMap);
			if(oldObj == NULL){
				::MessageBox(NULL, "Failed to select", "Object", MB_OK);
				::PostQuitMessage(0);
			}

			XFORM trans = {0};
			trans.eM11 = -1.0;
			trans.eM22 = -1.0;
//			::SetWorldTransform(paint.hdc, &trans);


			if(!::BitBlt(paint.hdc, 0, 0, width, height, mDC, 0, 0, SRCCOPY))
				::MessageBox(NULL, "Failed to copy", "Bits", MB_OK);
	
			::SelectObject(mDC, oldObj);
			::DeleteObject(bMap);
			::EndPaint(_hwnd, &paint);

			delete []fft;

			return true;
		} else 
		{
			return false;
		}
//		::MessageBox(NULL, "Przed", "MB", MB_OK);
		
	}
	
	bool ImgWndController::OnSize(int width, int height, int flags)
	{
		RECT client;
		::GetClientRect(_hwnd, &client);
		int size = 50;
		int b1x = client.right-size, b1y = 0;
		int b2x = b1x, b2y = b1y + size;

		::SetWindowPos(_btnArray[0]->GetHandle(), HWND_TOP, b1x, b1y, size, size, SWP_SHOWWINDOW);
		::SetWindowPos(_btnArray[1]->GetHandle(), HWND_TOP, b2x, b2y, size, size, SWP_SHOWWINDOW);

		
		HBITMAP saveImg = (HBITMAP)::LoadImage(NULL, (LPCTSTR)"save.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_LOADTRANSPARENT);
		HBITMAP splitImg = (HBITMAP)::LoadImage(NULL, (LPCTSTR)"split.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_LOADTRANSPARENT);

		::SendMessage(_btnArray[0]->GetHandle(), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)saveImg);
		::SendMessage(_btnArray[1]->GetHandle(), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)splitImg);

		return true;
	};

	void ImgWndController::Serialize(Serializer & out) const
	{
		for(int i = 0; i < _size; i++)
		{
			out.TwoColDouble(_dataX[i], _dataY[i]);
		}
		return;
	};

	void ImgWndController::UpdateData(double* inDataX, double* inDataY, int size)	
	{
		_dataX = inDataX;
		_dataY = inDataY;
		_size = size;

		_rangeMinX = _dataX[0];
		_rangeMaxX = _dataX[size-1];
		
		::InvalidateRect(_hwnd, NULL, TRUE);
		return;
	};
};