#pragma once

#include <mutex>

#include <Windows.h>

namespace Waw {

	class Window {
	public:
		Window(Window& window) = delete;

		Window& operator=(Window& window) = delete;

		static Window* GetInstance();

		inline HANDLE GetHandle() { return hStdout; }
		inline CONSOLE_SCREEN_BUFFER_INFO GetScreenBufferInfo() { return csbi; }
		inline HWND GetWindow() { return hWindow; }
	private:
		HANDLE hStdout;
		CONSOLE_SCREEN_BUFFER_INFO csbi; // Не знаю нужно ли это
		HWND hWindow;

		static Window* window;
		static std::mutex m;

		Window();
	};

}