// SimpleControl class definition
// EditControl class definition
// StaticControl class definition
// ButtonControl class definition
// ListViewControl class definition
// ComboControl class definition
// CustomButton class definition
// CustomCombo class definition

#ifndef WINDOWCONTROLS_H_
#define WINDOWCONTROLS_H_

#include "Window.h"
#include <string>
#include <vector>
#include <memory>
#include <utility>

using std::string;
using std::vector;
using std::pair;
using std::make_pair;
using std::shared_ptr;

namespace Win
{
	class SimpleControl : public Dow
	{
	public:
		SimpleControl(HWND, int);
		SimpleControl(HWND);
		void Init(HWND, int);
		void Init(HWND);
		bool IsClicked(int code);
		int GetId() const;
		HWND GetHandle() const {return _h;}
	protected:
		int _id;
	};	

	class EditControl : public SimpleControl
	{
	public:
		EditControl(HWND, int);
		EditControl(HWND);
		void Append(char const*);
		void Select(int, int);
		void SetReadOnly(bool);
		bool IsChanged(int);
		int GetLen();
		void SetText(char *, int);
		string GetText();
		void Select();
		void Clear();
	};
	
	class StaticControl : public SimpleControl
	{
	public: 
		StaticControl(HWND, int);
		StaticControl(HWND);
	};

	class ButtonControl : public SimpleControl
	{
	public:
		ButtonControl(HWND, int);
		ButtonControl(HWND win = 0);
		void SetText(char const *);		
	};
	
	class ComboControl : public SimpleControl
	{
	public:
		ComboControl(HWND, int);
		ComboControl(HWND win = 0);
	};
	
	class ListViewControl : public SimpleControl
	{
	public:
		ListViewControl(HWND, int);
		ListViewControl(HWND);
		bool InsertTwoColumnValues(char const*, char const *);
	};

	class TabControl : public SimpleControl
	{
	public:
		TabControl(HWND, int);
		TabControl(HWND);
	};

	class TreeViewControl : public SimpleControl
	{
	public:
		TreeViewControl(HWND, int);
		TreeViewControl(HWND);
	};
};

#endif