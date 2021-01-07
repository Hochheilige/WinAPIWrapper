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

	Window::Window() {
		GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hStdout, &csbi);
		hWindow = GetConsoleWindow();
	}

}
