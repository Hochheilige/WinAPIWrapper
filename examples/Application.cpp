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

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR pCmdLine, int nCmdShow) {
	hInst = hInstance;
	Window window(hInst, nCmdShow, "Waw Example Window");

	//HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_WAW));
	MSG msg;
	BOOL result;
	while (result = GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (result == -1)
		return result;
	else
		return msg.wParam;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
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

			Triangle tr(
				{ width / 2 - 300, height / 2 - 50 }, 
				{ width / 2, height / 2 - 150 }, 
				{ width / 2 + 300, height / 2 - 50 }, 
				StandartColors::GREEN
			);

		    tr.SetFillHatch(HatchTypes::DIAGCROSS);
			tr.SetColor(StandartColors::YELLOW);

			Rect rectangle(
				{ width / 2 - 50, height / 2 },
				{ width / 2 + 50, height / 2 + 100 },
				StandartColors::CYAN
			);

			Circle circle(
				{ width / 2 - 150, height / 2 - 100 },
				{ width / 2 + 150, height / 2 + 200 },
				StandartColors::MAGENTA
			);

			std::unique_ptr<Line> line(new Line(
				{ width / 2 + 150, height / 2 + 120 }, 
				{ width / 2 - 150, height / 2 + 120 }, 
				PenStyle::DOT, 6, StandartColors::GREEN
			));

			container_type figures = { circle, tr, rectangle };
			for (const auto& figure : figures)
				std::visit([&](auto& fig) { fig.Draw(memoryDC); }, figure);
			line->Draw(memoryDC);

			BitBlt(hdc, 0, 0, width, height, memoryDC, 0, 0, SRCCOPY);

			DeleteObject(bitmap);
			DeleteDC(memoryDC);

			EndPaint(hWnd, &ps);
		} break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}