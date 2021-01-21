#pragma once

#include <Windows.h>

#include <Resource.h>

namespace Waw {

	class Window {
	public:
		Window(HINSTANCE hInstance, int nCmdShow, LRESULT(CALLBACK* wndProc)(HWND, UINT, WPARAM, LPARAM));

		Window(HINSTANCE hInstance, int nCmdShow, LRESULT(CALLBACK* wndProc)(HWND, UINT, WPARAM, LPARAM), int widht, int height);

		void SetWindowSize(int widht, int height);

		inline HWND GetWindow() { return hWindow; }
	private:
		WNDCLASSEXW wcex;
		HWND hWindow;
	};

}