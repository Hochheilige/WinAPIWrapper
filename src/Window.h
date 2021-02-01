#pragma once

#include <Windows.h>

LRESULT WINAPI WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

namespace Waw {

	class Window {
	public:
		Window(HINSTANCE hInstance, int nCmdShow, const char* wndName);

		Window(HINSTANCE hInstance, int nCmdShow, int widht, int height, const char* wndName);

		void SetWindowSize(int widht, int height);

		inline HWND GetWindow() { return hWindow; }
	private:
		HWND hWindow;
	};

}