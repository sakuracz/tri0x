#ifndef CUSTOMCONTROLS_H_
#define CUSTOMCONTROLS_H_

#include "libWin\WindowControls.h"

namespace Win
{
	class CustomButton : public ButtonControl
	{
	public:
		void LoadBMPs(const string&);
		bool Draw(const int&, DRAWITEMSTRUCT*);
		~CustomButton();
	private:
		HANDLE bmapPressed = 0;
		HANDLE bmapDepressed = 0;
		HANDLE bmapDisabled = 0;
		HANDLE bmapHover = 0;
	};

	class CustomCombo : public ComboControl
	{
	public:
		friend class ComboController;
		~CustomCombo();
		void Load(const string&, const vector<string>&, const RECT& coords);	//loads bitmaps and inits rects
		void Fill();
		bool Draw(const int&, DRAWITEMSTRUCT*);
		unsigned int GetWidth(){ return idle.right - idle.left; }
		unsigned int GetHeight() { return idle.bottom - idle.top; }
		bool IsSelected() { return isSelected; }
		void Select(unsigned int& sel){ selection = sel; }
		void ToggleSelected();
		void ToggleSelecting();
		pair<unsigned int, unsigned int> GetBasePos(){ return pair<unsigned int, unsigned int>(idle.left, idle.top); }
		pair<unsigned int, unsigned int> GetExpPos() { return pair<unsigned int, unsigned int>(selected.left, selected.top); }
	private:
		bool isSelected = false;
		bool isBeingSelected = false;
		int selection = -1;
		RECT idle, selected, selecting;
		vector<HANDLE> header_bmaps;
		vector<HANDLE> footer_bmaps;
		vector<HANDLE> hover_bmaps;
		vector<HANDLE> idle_bmaps;
		vector<string> items;
		HFONT font;
	};

	class CustomEdit : public EditControl
	{
	public:
		friend class EditController;
		CustomEdit(HWND, int);
		CustomEdit(HWND win = 0);
		void LoadBMPs(const string&);
	private:
		HANDLE bmapBack = NULL;
	};

	class CustomRadio : public SimpleControl
	{
	public:
		friend class RadioController;
		CustomRadio(HWND, int);
		CustomRadio(HWND win = 0);
		void LoadBMPs(const string& name);
		void GetShare(const CustomRadio&);
	private:
		shared_ptr<HANDLE> bmapDis, bmapCheck, bmapIdle, bmapMask;
		bool isChecked = false;
	};
}
#endif