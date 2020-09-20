#pragma once

#include <Windows.h>

class Window {
public:
	Window();
	~Window();

	inline HANDLE GetHandle() { return hStdout; }
	inline CONSOLE_SCREEN_BUFFER_INFO GetScreenBufferInfo() { return csbi; }
	inline HWND GetWindow() { return hWindow; }
	inline HDC GetDeviceContext() { return hDeviceContext; }
private:
	HANDLE hStdout;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HWND hWindow;
	HDC hDeviceContext;
};