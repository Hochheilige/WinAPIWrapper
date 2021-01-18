#include <WinAPIWrapper.h>

#include "Resource.h"

#include <iostream>
#include <vector>
#include <variant>

using namespace Waw;

HINSTANCE hInst;  

template <typename... Ts>
using poly_T = std::variant<Ts...>;

using container_type = std::vector<
	poly_T<Triangle, Rect, Circle>
>;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	hInst = hInstance;
	Window::SetUpWindow(hInst, nCmdShow, WndProc);


	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));
	MSG msg;

	// Цикл основного сообщения:
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
			// Разобрать выбор в меню:
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

			 
			
			 Triangle tr({ 50, 250 }, { 650, 250 }, { 350, 150 }, StandartColors::GREEN);
			Rect rectangle({ 300, 300 }, { 400, 400 }, StandartColors::CYAN);
			tr.SetFillHatch(HatchTypes::DIAGCROSS);
			tr.SetColor(StandartColors::YELLOW);
			Circle circle({ 200, 200 }, { 500, 500 }, StandartColors::MAGENTA);

			container_type figures = { circle, tr, rectangle };
			for (const auto& figure : figures)
				std::visit([](auto& fig) { fig.Draw(); }, figure);

			Line* line = new Line({ 500, 420 }, { 200, 420 }, PenStyle::DOT, 6, StandartColors::GREEN);
			line->Draw();

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