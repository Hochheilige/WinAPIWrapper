#include "Window.h"

using namespace std;

namespace Waw {

	Window::Window(HINSTANCE hInstance, LRESULT (*WinProc)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)) {
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WinProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = className;
		wc.hIconSm = NULL;

		RegisterClassEx(&wc);
	}

	bool Window::CreateWawWindow(HINSTANCE hInstance, int nCmdShow, const char* wndName) {
		hWindow = CreateWindowEx(0, className,
								 wndName, WS_OVERLAPPEDWINDOW,
								 100, 100, 800, 600,
								 nullptr, nullptr,
								 hInstance, nullptr);

		ShowWindow(hWindow, nCmdShow);
		return IsWindow(hWindow);		
	}

	bool Window::CreateWawWindow(HINSTANCE hInstance, int nCmdShow, int width, int height, const char* wndName) {
		hWindow = CreateWindowEx(0, className,
								 wndName, WS_OVERLAPPEDWINDOW,
								 100, 100, width, height,
								 nullptr, nullptr,
								 hInstance, nullptr);

        ShowWindow(hWindow, nCmdShow);
		return IsWindow(hWindow);
	}

	void Window::SetWindowSize(int width, int height) {
		SetWindowPos(hWindow, nullptr, 100, 100, width, height, SWP_SHOWWINDOW);
	}

}
