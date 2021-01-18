#include "Window.h"

using namespace std;

namespace Waw {

	Window* Window::window{ nullptr };
	mutex Window::m;

	Window* Window::GetInstance() {
		lock_guard<mutex> guard(m);
		if (window == nullptr)
			window = new Window();

		return window;
	}

	void Window::SetUpWindow(HINSTANCE hinstance, int nCmdShow, LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM)) {
		Window::Window(hinstance, nCmdShow, WNDPROC);
	}

	Window::Window() {
		GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hStdout, &csbi);
		hWindow = GetConsoleWindow();
	}

	Window::Window(HINSTANCE hInstance, int nCmdShow, LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM)) {
		//GetStdHandle(STD_OUTPUT_HANDLE);
		//GetConsoleScreenBufferInfo(hStdout, &csbi);

		wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WNDPROC;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(107));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = MAKEINTRESOURCEW(109);
		wcex.lpszClassName = L"Waw Window";
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(108));

		RegisterClassExW(&wcex);

		hWindow = CreateWindowW(L"Waw Window", L"Waw Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

		ShowWindow(hWindow, nCmdShow);
	}

}
