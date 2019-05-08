/*----------------------------------/
/----------CursesConsole------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_CURSESCONSOLE
#define HALE3D_CURSESCONSOLE

#if defined(_WIN32)
#include "PDCurses\curses.h"
#else
//TODO: include ncurses.
#endif

/* Standard include(s). */
#include <string>
#include <vector>
#include <functional>

namespace Hale3D {
	struct CursesObj;    // Forward declaration.
	struct CursesPad;	 // Forward declaration.
	struct CursesWindow; // Forward declaration.

	struct CursesConsole {
		CursesConsole(int pRows = 40, int pColumns = 120, const std::function<void()>& pOnClose = nullptr);
		~CursesConsole();

		bool updateTerminal;
	
		struct {
			CursesPad* m_Log;
			CursesWindow* m_Input;
		} m_Windows;

		void Update();
		void Clear();
		void Close();

		std::vector<CursesObj*> m_Children;

		/*Static Members*/
		static const unsigned int TAB_SIZE = 4;

	private:
		struct {
			int width = 0;
			int height = 0;
		} _size;

		bool _closing = false;
		std::string _input;
		std::function<void()> _onCloseFn;

		void HandleChar(char pChar);
		void HandleKey(const std::string& pKey);
	};

	struct CursesObj {
		WINDOW* obj = nullptr;
		CursesConsole* parent = nullptr;

		~CursesObj();

		/*Generic*/
		bool IsValid() const;
		
		virtual bool IsPad() const = 0;
		virtual bool IsWindow() const = 0;

		/*Size*/
		void SetSize(int pColumns, int pRows, bool pClear = false, bool pUpdateParent = true);
		int GetColumns() const;
		int GetRows() const;

		/*Scrolling*/
		virtual void SetScrollRow(int pValue) = 0;
		int GetScrollRow() const;

		/*Curses*/
		void Clear();
		void AddChar(const char pChar);
		void DeleteChar();
		int GetChar();
		
		void Move(int pColumn, int pRow, bool pUpdateParent = true);
		virtual void Refresh() = 0;

		void MoveCursor(int pColumn, int pRow);
		int GetCursorColumn() const;
		int GetCursorRow() const;

	protected:
		struct {
			int row = 0;
			int column = 0;
		} _scroll;

	private:
		struct {
			int columns = 0;
			int rows = 0;
		} _size;
	};

	struct CursesPad : public CursesObj {
		CursesPad(int pColumns, int pRows, CursesConsole* pParent, bool pScrolling = true);

		virtual void Refresh();

		virtual bool IsPad() const;
		virtual bool IsWindow() const;

		/*Scrolling*/
		virtual void SetScrollRow(int pValue);
	};

	struct CursesWindow : public CursesObj {
		CursesWindow(int pColumns, int pRows, CursesConsole* pParent, bool pScrolling = true, bool pKeypad = true, bool pNoDelay = true);

		virtual void Refresh();

		virtual bool IsPad() const;
		virtual bool IsWindow() const;

		/*Scrolling*/
		virtual void SetScrollRow(int pValue);
	};
}
#endif
