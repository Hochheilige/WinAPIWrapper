#pragma once

#include <Windows.h>

namespace Waw {

	class Window {
	public:
		Window(HINSTANCE hInstance, LRESULT (*WinProc)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam));

		bool CreateWawWindow(HINSTANCE hInstance, int nCmdShow, const char* wndName);

		bool CreateWawWindow(HINSTANCE hInstance, int nCmdShow, int width, int height, const char* wndName);

		void SetWindowSize(int width, int height);

		inline HWND GetWindow() { return hWindow; }
	private:
		HWND hWindow;
		WNDCLASSEX wc = { 0 };
		const char* className = "WawWindow";
	};

}