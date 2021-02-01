#include "Window.h"

using namespace std;

namespace Waw {

	Window::Window(HINSTANCE hInstance, int nCmdShow, const char* wndName) {
		WNDCLASSEX wc = { 0 };
		const auto className = "WawWindow";
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

		hWindow = CreateWindowEx(0, className, 
								 wndName, WS_OVERLAPPEDWINDOW, 
								 100, 100, 800, 600, 
								 nullptr, nullptr, 
								 hInstance, nullptr
		);

		ShowWindow(hWindow, nCmdShow);
	}

	Window::Window(HINSTANCE hInstance, int nCmdShow, int width, int height, const char* wndName) {
		WNDCLASSEX wc = { 0 };
		const auto className = "WawWindow";
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

		hWindow = CreateWindowEx(0, className,
								 wndName, WS_OVERLAPPEDWINDOW,
								 100, 100, width, height,
								 nullptr, nullptr,
								 hInstance, nullptr);

		ShowWindow(hWindow, nCmdShow);
	}

	void Window::SetWindowSize(int widht, int height) {
		SetWindowPos(hWindow, nullptr, 100, 100, widht, height, SWP_SHOWWINDOW);
	}

}
