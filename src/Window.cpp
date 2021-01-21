#include "Window.h"

using namespace std;

namespace Waw {

	Window::Window(HINSTANCE hInstance, int nCmdShow, LRESULT(CALLBACK* wndProc)(HWND, UINT, WPARAM, LPARAM)) {
		HBRUSH winColor = CreateSolidBrush(RGB(0, 0, 0));
		wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = wndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WAW));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = winColor;
		wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WAW);
		wcex.lpszClassName = L"Waw Window";
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		RegisterClassExW(&wcex);

		hWindow = CreateWindowW(L"Waw Window", L"Waw Window", WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

		ShowWindow(hWindow, nCmdShow);
	}

	Window::Window(HINSTANCE hInstance, int nCmdShow, LRESULT (*wndProc)(HWND, UINT, WPARAM, LPARAM), int widht, int height) {
		HBRUSH winColor = CreateSolidBrush(RGB(0, 0, 0));
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = wndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WAW));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = winColor;
		wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WAW);
		wcex.lpszClassName = L"Waw Window";
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		RegisterClassExW(&wcex);

		hWindow = CreateWindowW(L"Waw Window", L"Waw Window", WS_OVERLAPPEDWINDOW, 0, 0, widht, height, nullptr, nullptr, hInstance, nullptr);

		ShowWindow(hWindow, nCmdShow);
	}

	void Window::SetWindowSize(int widht, int height) {
		SetWindowPos(hWindow, nullptr, 0, 0, widht, height, SWP_SHOWWINDOW);
	}

}
