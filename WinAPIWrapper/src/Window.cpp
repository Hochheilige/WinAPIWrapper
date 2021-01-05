#include "Window.h"

namespace Waw {

	Window::Window() {
		GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hStdout, &csbi);
		hWindow = GetConsoleWindow();
		hDeviceContext = GetDC(hWindow);
	}

	Window::~Window() {
		ReleaseDC(hWindow, hDeviceContext);
	}

}
