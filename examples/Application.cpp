#include <WinAPIWrapper.h>

#include <iostream>
#include <vector>
#include <memory>
#include <variant>

using namespace Waw;

template <typename... Ts>
using Figures = std::variant<Ts...>;

using container_type = std::vector<
	Figures<Triangle, Rect, Circle>
>;

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	hInst = hInstance;
	Window window(hInst, nCmdShow, WndProc);

	HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_WAW));
	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0)) {
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_COMMAND: {
			int wmId = LOWORD(wParam);
			switch (wmId) {
				case IDM_ABOUT:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, NULL);
					break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
		} break;
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			RECT window_rect = { 0 };
			GetWindowRect(hWnd, &window_rect);
			int32_t width = window_rect.right - window_rect.left;
			int32_t height = window_rect.bottom - window_rect.top;

		    HDC memoryDC = CreateCompatibleDC(hdc);
			HBITMAP bitmap = CreateCompatibleBitmap(hdc, width, height);
			SelectObject(memoryDC, bitmap);

			Triangle tr({ width / 2 - 300, height / 2 - 50 }, { width / 2, height / 2 - 150 }, { width / 2 + 300, height / 2 - 50 }, StandartColors::GREEN);
			Rect rectangle({ width / 2 - 50, height / 2 }, { width / 2 + 50, height / 2 + 100 }, StandartColors::CYAN);
			Circle circle({ width / 2 - 150, height / 2 - 100 }, { width / 2 + 150, height / 2 + 200 }, StandartColors::MAGENTA);
			std::unique_ptr<Line> line(new Line({ width / 2 + 150, height / 2 + 120 }, { width / 2 - 150, height / 2 + 120 }, PenStyle::DOT, 6, StandartColors::GREEN));
			tr.SetFillHatch(HatchTypes::DIAGCROSS);
			tr.SetColor(StandartColors::YELLOW);

			container_type figures = { circle, tr, rectangle };
			for (const auto& figure : figures)
				std::visit([&](auto& fig) { fig.Draw(memoryDC); }, figure);
			line->Draw(memoryDC);

			BitBlt(hdc, 0, 0, width, height, memoryDC, 0, 0, SRCCOPY);

			DeleteObject(bitmap);
			DeleteDC(memoryDC);

			EndPaint(hWnd, &ps);
		} break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}